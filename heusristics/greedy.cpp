#ifndef GREEDY_CPP
#define GREEDY_CPP

#include "../models/point.cpp"
#include "../models/map.cpp"
#include "../models/vehicles/car.cpp"
#include "../models/route.cpp"

class Greedy{
    private:
    // TODO: Use pointers ?
    struct PointReturn{
        Point point;
        double distance;
        int index;
    };

    /**
        Finds the nearest unvisited client to the actual position, allways considering that the car can go back to any deposit
        @param t_points vector of points to be searched
        @param t_actual_position drivers actual position (usually is the same as the last client)
    */
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
        PointReturn point_return;
        point_return.point = nearest_point;
        point_return.distance = shortest_distance;
        point_return.index = nearest_index;
        return point_return;
    }

    //  TODO: Change this function to an car function
    static bool validate_next_client(Point t_actual_position, Point t_nearest_client, vector<Point> t_deposits, Car t_car){
        // Storage validation
        if (t_car.getRemainingStorage() < t_nearest_client.getPackage()) 
            return false;

        // Fuel validation
        double actual_to_nearest_point_distance = Point::distanceBetweenPoints(t_actual_position, t_nearest_client);

        PointReturn nearest_client_to_nearest_deposit_return = find_nearest_point(&t_nearest_client, &t_deposits);
        double nearest_client_to_deposit_distance = nearest_client_to_nearest_deposit_return.distance;
        double total_range = actual_to_nearest_point_distance + nearest_client_to_deposit_distance;

        return total_range <= t_car.getRemainingRange();
    }

    public: 
    /**
        Implements a greedy algorithm to get an good route only using a single car
        @param t_map map struct to define the environment
        @param t_initial_position starting point of the car
        @param t_car car to be used in the route
    */
    static Route single_car_greedy(Map t_map, Car* t_car, Point t_initial_position){
        // TODO: Validate if all clients are reachable from any deposit (reachable -> can start from any deposit and to any other?)

        Point actual_position = t_initial_position;
        Route route(t_car);
        route.addPoint(actual_position);
        while (!t_map.clients.empty()){
            // OPTIMIZATION: Use the remainig car range when setting the nearest client?
            PointReturn nearest_client_return = find_nearest_point(&actual_position, &t_map.clients);
            Point nearest_client = nearest_client_return.point;
            int nearest_client_index = nearest_client_return.index;
            double nearest_client_distance = nearest_client_return.distance;

            if (validate_next_client(actual_position, nearest_client, t_map.deposits, *t_car)){
                actual_position = nearest_client;
                t_map.clients.erase(t_map.clients.begin() + nearest_client_index);
                t_car->deliver(nearest_client.getPackage(), nearest_client_distance);
                route.addPoint(actual_position);
            }
            else {
                Point nearest_deposit = find_nearest_point(&actual_position, &t_map.deposits).point;
                actual_position = nearest_deposit;
                t_car->resetAttributes();
                route.addPoint(nearest_deposit);
            }
        }

        // Add deposit at the end of the route
        Point nearest_deposit = find_nearest_point(&t_initial_position, &t_map.deposits).point;
        t_car->resetAttributes();
        route.addPoint(nearest_deposit);

        return route;
    }

    static void add_drone_flight(Route& route){
        Car* p_car = route.getCar();
        Drone* p_drone = p_car->getDrone();

        CarStop* p_last_car_stop = route.getFirstStop();
        CarStop* p_actual_car_stop = p_last_car_stop->m_next;
        CarStop* p_next_car_stop = p_actual_car_stop->m_next;
        Flight* p_actual_flight = nullptr;

        while (p_next_car_stop != nullptr){
            Point last_point = p_last_car_stop->getPoint();
            Point actual_point = p_actual_car_stop->getPoint();
            Point next_point = p_next_car_stop->getPoint();

            if (actual_point.is_client()){
                double package = actual_point.getPackage();
                double distance_delivery = Point::distanceBetweenPoints(last_point, actual_point);
                double distance_back = Point::distanceBetweenPoints(actual_point, next_point);
                double total_distance = distance_delivery + distance_back;

                if (p_drone->canDeliver(total_distance, package)){
                    if (!p_drone->isFlying()){
                        p_drone->takeOff();
                        // TODO: Refactor startFlight to set takeoff point
                        p_actual_flight = route.createFlight(p_last_car_stop, p_drone);
                        p_actual_car_stop->setTakeoffFlight(p_actual_flight);
                    }
                    DroneStop* new_drone_stop = route.createDroneStop(p_actual_flight, actual_point);
                    p_actual_flight->addStop(new_drone_stop);

                    p_drone->deliver(distance_delivery, package);

                    route.removeCarStop(p_actual_car_stop);
                }
                else{
                    if (p_drone->isFlying()){
                        p_drone->land();
                        // TODO: ADD returning carstop to flight
                        p_actual_car_stop->setReturnFlight(p_actual_flight);
                    }
                }
            }
            else{
                if (p_drone->isFlying()){
                    p_drone->land();
                    // TODO: ADD returning carstop to flight
                    p_actual_car_stop->setReturnFlight(p_actual_flight);
                }
            }

            p_last_car_stop = p_actual_car_stop;
            p_actual_car_stop = p_next_car_stop;
            p_next_car_stop = p_actual_car_stop->m_next;
        }
    }
};

#endif
