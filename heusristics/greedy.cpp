#ifndef GREEDY_CPP
#define GREEDY_CPP

#include "../models/point.cpp"
#include "../models/map.cpp"
#include "../models/vehicles/car.cpp"
#include "../models/route.cpp"

class Greedy{
    private:
    // TODO: Use pointers
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
    static Route single_car_greedy(Map t_map, Car* t_car, Point* t_initial_position){
        // TODO: Validate if all clients are reachable from any deposit (reachable -> can start from any deposit and to any other?)

        Point* p_actual_position = t_initial_position;
        Route route(t_car);
        route.addPoint(p_actual_position);
        while (!t_map.clients.empty()){
            // OPTIMIZATION: Use the remainig car range when setting the nearest client?

            PointReturn nearest_client_return = find_nearest_point(t_map.clients, *p_actual_position);
            Point nearest_client = nearest_client_return.point;
            int nearest_client_index = nearest_client_return.index;
            double nearest_client_distance = nearest_client_return.distance;

            if (validate_next_client(*p_actual_position, nearest_client, t_map.deposits, *t_car)){
                p_actual_position = &nearest_client;

                t_map.clients.erase(t_map.clients.begin() + nearest_client_index);
                t_car->deliver(nearest_client.getPackage(), nearest_client_distance);
                route.addPoint(&nearest_client);
            }
            else {
                Point nearest_deposit = find_nearest_point(t_map.deposits, *p_actual_position).point;
                p_actual_position = &nearest_deposit;
                t_car->resetAttributes();
                route.addPoint(&nearest_deposit);

            }
        }

        // Add deposit at the end of the route
        Point nearest_deposit = find_nearest_point(t_map.deposits, *p_actual_position).point;
        t_initial_position = &nearest_deposit;
        t_car->resetAttributes();
        route.addPoint(p_actual_position);

        return route;
    }

    // static void add_drone_flight(Car& t_car){
    //         vector<Point> old_car_route = t_car.getRoute();
    //         Drone* drone = t_car.getDrone();

    //         Point actual_point, last_point = old_car_route.at(0);
    //         for(int i = 1; i < old_car_route.size(); i++){
    //             actual_point = old_car_route.at(i);
    //             if (actual_point.is_client()){
    //                 double package = actual_point.getPackage();
    //                 double distance_delivery = Point::distanceBetweenPoints(actual_point, last_point);
    //                 double distance_back = Point::distanceBetweenPoints(last_point, old_car_route.at(i+1));
    //                 double total_distance = distance_delivery + distance_back;

    //                 if (drone->canDeliver(total_distance, package)){
    //                     drone->deliver(package, distance_delivery);
    //                     if (!drone->isFlying()){
    //                         drone->takeOff(last_point, i-1);
    //                     }
    //                     drone->addPointToFlight(actual_point);

    //                     t_car.removePointFromRoute(i);
    //                     old_car_route.erase(old_car_route.begin() + i);
    //                     i--;
    //                 }
    //                 else{
    //                     if (drone->isFlying()){
    //                         drone->land(actual_point);
    //                     }
    //                 }
    //             }
    //             else{
    //                 if (drone->isFlying()){
    //                     drone->land(actual_point);
    //                 }
    //             }
    //             last_point = actual_point;
    //         }
    //     }
};

#endif
