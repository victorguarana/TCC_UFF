#ifndef GREEDY_CPP
#define GREEDY_CPP

#include "../models/point.cpp"
#include "../models/client.cpp"
#include "../models/map.cpp"
#include "../models/vehicles/car.cpp"

class Greedy{
    private:
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
        static PointReturn find_nearest_point(vector<Point> t_points, Point t_actual_position){
            Point nearest_point = t_points.at(0);
            int nearest_index = 0;
            double shortest_distance = Point::distanceBetweenPoints(t_actual_position, nearest_point);

            for(int i = 1; i < t_points.size(); i++){
                Point new_point = t_points.at(i);
                double new_distance = Point::distanceBetweenPoints(t_actual_position, new_point);

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

        static bool validate_next_client(Point t_actual_position, Point t_nearest_client, vector<Point> t_deposits, Car t_car){
            // Storage validation
            if (t_car.getRemainingStorage() < t_nearest_client.getPackage()) 
                return false;

            // Fuel validation
            double actual_to_nearest_point_distance = Point::distanceBetweenPoints(t_actual_position, t_nearest_client);

            PointReturn nearest_client_to_nearest_deposit_return = find_nearest_point(t_deposits, t_nearest_client);
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
        static void single_car_greedy(Car& t_car, Map t_map, Point t_initial_position){
            // TODO: Validate if all clients are reachable from any deposit (reachable -> can start from any deposit and to any other?)
            while (!t_map.clients.empty()){
                // OPTIMIZATION: Use the remainig car range when setting the nearest client?

                PointReturn nearest_client_return = find_nearest_point(t_map.clients, t_initial_position);
                Point nearest_client = nearest_client_return.point;
                int nearest_client_index = nearest_client_return.index;
                double nearest_client_distance = nearest_client_return.distance;

                if (validate_next_client(t_initial_position, nearest_client, t_map.deposits, t_car)){
                    t_initial_position = nearest_client;
                    t_car.addPointToRoute(nearest_client);
                    t_map.clients.erase(t_map.clients.begin() + nearest_client_index);
                    t_car.move(nearest_client_distance);
                    t_car.store(nearest_client.getPackage());
                }
                else {
                    Point nearest_deposit = find_nearest_point(t_map.deposits, t_initial_position).point;
                    t_initial_position = nearest_deposit;
                    t_car.addPointToRoute(nearest_deposit);
                    t_car.resetRange();
                    t_car.resetStorage();
                }
            }

            // Add deposit at the end of the route
            Point nearest_deposit = find_nearest_point(t_map.deposits, t_initial_position).point;
            t_initial_position = nearest_deposit;
            t_car.addPointToRoute(nearest_deposit);
            t_car.resetRange();
            t_car.resetStorage();
        }

        static void add_drone_flight(Car& t_car){
            vector<Point> car_route = t_car.getRoute();
            Drone* drone = t_car.getDrone();

            Point next_point, actual_point = car_route.at(0);
            Flight actual_flight;
            for(int i = 1; i < car_route.size()-1; i++){
                next_point = car_route.at(i);
                if (next_point.is_client()){
                    double package = next_point.getPackage();
                    double distance_delivery = Point::distanceBetweenPoints(next_point, actual_point);
                    double distance_back = Point::distanceBetweenPoints(actual_point, car_route.at(i+1));
                    double total_distance = distance_delivery + distance_back;

                    if (drone->canDeliver(total_distance, package)){
                        drone->move(distance_delivery);
                        drone->store(package);
                        if (!drone->isFlying()){
                            drone->takeOff(actual_point);
                        }
                        drone->addPointToFlight(next_point);
                        car_route.erase(car_route.begin() + i);
                    }
                    else{
                        if (drone->isFlying()){
                            drone->land(next_point);
                            drone->resetRange();
                            drone->resetStorage();
                        }
                    }
                }
                actual_point = next_point;
            }
            t_car.setRoute(car_route);
        }
};

#endif
