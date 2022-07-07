#ifndef GREEDY_CPP
#define GREEDY_CPP

#include "../models/point.cpp"
#include "../models/map.cpp"
#include "../models/vehicles/car.cpp"
#include "../models/vehicles/drone.cpp"
#include "../models/route.cpp"

class Greedy{
    private:
    struct PointReturn{
        Point point;
        double distance;
        int index;
    };
    struct DroneStats{
        Drone* drone;
        Flight* actual_flight;
        int rejected_deliveries;
    };

    // Returns the nearest point, distance and index
    static PointReturn find_nearest_point(Point* t_actual_position, vector<Point>* t_points){
        Point nearest_point = t_points->at(0);
        int nearest_index = 0;
        double shortest_distance = Point::distanceBetweenPoints(*t_actual_position, nearest_point);

        // OPTIMIZATION: USE LOOP WITH POINTERS ? 
        for(int i = 1; i < t_points->size(); i++){
            Point new_point = t_points->at(i);
            double new_distance = Point::distanceBetweenPoints(*t_actual_position, new_point);

            if (shortest_distance > new_distance){
                shortest_distance = new_distance;
                nearest_point = new_point;
                nearest_index = i;
            }
        }
        PointReturn point_return = { nearest_point, shortest_distance, nearest_index };
        return point_return;
    }

    static bool validate_next_client(Point* t_actual_position, Point t_nearest_client, vector<Point> t_deposits, Car* t_car){
        // Fuel validation
        double actual_to_nearest_point_distance = Point::distanceBetweenPoints(*t_actual_position, t_nearest_client);

        PointReturn nearest_client_to_nearest_deposit_return = find_nearest_point(&t_nearest_client, &t_deposits);
        double nearest_client_to_deposit_distance = nearest_client_to_nearest_deposit_return.distance;
        double total_range = actual_to_nearest_point_distance + nearest_client_to_deposit_distance;

        return t_car->canDeliver(total_range, t_nearest_client.getPackage());
    }

    // Get all drones that are flying and can't land in the other next point
    static vector<DroneStats> getDronesToLand(Point* t_nearest_client, vector<DroneStats> t_drones_flying){
        vector<DroneStats> drones_to_land;
        for(int i = 0; i < t_drones_flying.size(); i++){
            Drone* p_drone = t_drones_flying.at(i).drone;
            Flight* p_flight = t_drones_flying.at(i).actual_flight;
            int rejected_deliveries = t_drones_flying.at(i).rejected_deliveries;
            Point* p_actual_position = p_drone->getActualPosition();
            double distance = Point::distanceBetweenPoints(*t_nearest_client, *p_actual_position);
            if(p_drone->getRemainingRange() < distance || rejected_deliveries > 2 || p_drone->getRemainingStorage() == 0)
                drones_to_land.push_back({p_drone, p_flight, 0});
        }
        return drones_to_land;
    }

    public:

    static void multiple_car_greedy(Map t_map, vector<Car*> t_car_fleet, Point t_initial_position){
        int fleet_size = t_car_fleet.size();
        int car_index = 0;

        while (!t_map.clients.empty()){
            Car* p_actual_car = t_car_fleet.at(car_index);
            Point* p_actual_position = p_actual_car->getActualPosition();

            // OPTIMIZATION: Use the remainig car range when setting the nearest client?
            PointReturn nearest_client_return = find_nearest_point(p_actual_position, &t_map.clients);
            Point nearest_client = nearest_client_return.point;
            int nearest_client_index = nearest_client_return.index;
            double nearest_client_distance = nearest_client_return.distance;

            // Decide next point
            Point* p_next_point;
            if (validate_next_client(p_actual_position, nearest_client, t_map.deposits, p_actual_car)){
                t_map.clients.erase(t_map.clients.begin() + nearest_client_index);
                p_next_point = Point::create(nearest_client);
            }
            else {
                Point nearest_deposit = find_nearest_point(p_actual_position, &t_map.deposits).point;
                p_next_point = Point::create(nearest_deposit);
            }

            Point* p_point = Point::create(t_initial_position);


            // Create car stop and append it to route
            p_actual_car->getRoute()->appendPoint(p_next_point);
            p_actual_car->deliver(p_next_point);

            // Get next car in line
            car_index++;
            if (car_index >= fleet_size){
                car_index = 0;
            }
        }

        // Append initial point to all routes
        for(int i = 0; i < t_car_fleet.size(); i++){
            Point* p_actual_position = t_car_fleet.at(i)->getActualPosition();
            Point nearest_deposit = find_nearest_point(p_actual_position, &t_map.deposits).point;

            Point* p_point = Point::create(nearest_deposit);
            t_car_fleet.at(i)->getRoute()->appendPoint(p_point);
        }
    }


    static void add_drone_flight(Route* t_route){
        Car* p_car = t_route->getCar();
        vector<Drone*> drones = p_car->getDrones();
        vector<Drone*> drones_docked = drones;
        vector<DroneStats> drones_flying;

        CarStop* p_last_car_stop = t_route->getFirstStop();
        CarStop* p_actual_car_stop = p_last_car_stop->m_next;
        CarStop* p_next_car_stop;
        Point *p_last_point, *p_actual_point, *p_next_point;

        Flight* p_actual_flight = nullptr;

        while (p_actual_car_stop != nullptr){
            p_next_car_stop = p_actual_car_stop->m_next;

            p_last_point = p_last_car_stop->getPoint();
            p_actual_point = p_actual_car_stop->getPoint();

            if (p_actual_point->is_client()){
                p_next_point = p_next_car_stop->getPoint();

                // Do not need to validate car storage
                // Get Drones that need to land in next point
                vector<DroneStats> drones_to_land;
                if (p_next_car_stop->m_next != nullptr)
                    drones_to_land = getDronesToLand(p_next_car_stop->m_next->getPoint(), drones_flying);

                if (drones_to_land.empty()){
                    double package = p_actual_point->getPackage();
                    double distance_delivery = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
                    double distance_back = Point::distanceBetweenPoints(*p_actual_point, *p_next_point);
                    double total_distance = distance_delivery + distance_back;
                    Drone* p_drone = nullptr;

                    if (!drones_docked.empty()){
                        // Get docked drone to deliver next client
                        p_drone = drones_docked.at(0);

                        if (p_drone->canDeliver(total_distance, package)){
                            drones_docked.erase(drones_docked.begin());


                            p_drone->takeOff(p_last_car_stop->getPoint());
                            p_actual_flight = Flight::create(p_last_car_stop, p_drone);
                            p_last_car_stop->addTakeoffFlight(p_actual_flight);

                            Point* p_point = p_actual_car_stop->getPoint();
                            DroneStop* new_drone_stop = DroneStop::create(p_actual_flight, p_point);
                            p_actual_flight->appendDroneStopLast(new_drone_stop);

                            p_drone->deliver(p_actual_point);

                            t_route->removeCarStop(p_actual_car_stop);
                            p_actual_car_stop->erase();
                            p_actual_car_stop = nullptr;

                            drones_flying.push_back({p_drone, p_actual_flight, 0});
                        }
                    }
                    else{
                        // Get a flying drone that can deliver
                        Flight* p_flight = nullptr;
                        for (int i = 0; i < drones_flying.size(); i++){
                            Drone* p_actual_drone = drones_flying.at(i).drone;
                            if (p_actual_drone->canDeliver(total_distance, package)){
                                // TODO: Change this for optimization?
                                drones_flying.at(i).rejected_deliveries = 0;

                                if(p_drone == nullptr){
                                    p_drone = p_actual_drone;
                                    p_flight = drones_flying.at(i).actual_flight;

                                    // Move to last position to respect priority
                                    drones_flying.erase(drones_flying.begin() + i);
                                    drones_flying.push_back({p_drone, p_flight, 0});
                                }
                            }
                            else{
                                drones_flying.at(i).rejected_deliveries = drones_flying.at(i).rejected_deliveries++;
                            }
                        }

                        if (p_drone != nullptr){
                            p_drone->takeOff(p_last_car_stop->getPoint());

                            Point* p_point = p_actual_car_stop->getPoint();
                            DroneStop* new_drone_stop = DroneStop::create(p_flight, p_point);
                            p_flight->appendDroneStopLast(new_drone_stop);

                            p_drone->deliver(p_actual_point);

                            t_route->removeCarStop(p_actual_car_stop);
                            p_actual_car_stop->erase();
                            p_actual_car_stop = nullptr;
                        }
                    }
                }
                else{
                    // Land all drones
                    for(int i = 0; i < drones_to_land.size(); i++){
                        Drone* p_drone = drones_to_land.at(i).drone;
                        p_drone->land();
                        drones_docked.push_back(p_drone);

                        Flight* p_actual_flight = drones_to_land.at(i).actual_flight;
                        //p_actual_car_stop->addReturnFlight(p_actual_flight);
                        p_actual_flight->setLandingStop(p_actual_car_stop);

                        for(int j = 0; j < drones_flying.size(); j++)
                            if(drones_flying.at(j).drone == p_drone){
                                drones_flying.erase(drones_flying.begin() + j);
                                break;
                            }
                    }
                }
            }
            else{
                for(int i = 0; i < drones_flying.size(); i++){
                    Drone* p_drone = drones_flying.at(i).drone;
                    p_drone->land();
                    drones_docked.push_back(p_drone);

                    Flight* p_actual_flight = drones_flying.at(i).actual_flight;
                    //p_actual_car_stop->addReturnFlight(p_actual_flight);
                    p_actual_flight->setLandingStop(p_actual_car_stop);
                }
                drones_flying.clear();
            }

            if (p_actual_car_stop != nullptr)
                p_last_car_stop = p_actual_car_stop;
            p_actual_car_stop = p_next_car_stop;
        }
    }


};

#endif
