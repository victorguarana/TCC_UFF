#ifndef MEASURER_CPP
#define MEASURER_CPP

#include "models/vehicles/car.cpp"

class Measurer{
    public:
        static double route_measurer(Car t_car){
            Drone drone = *t_car.getDrone();
            double car_distance = t_car.route_distance() / t_car.getSpeed();
            double drone_distance = drone.route_distance() / drone.getSpeed();
            return car_distance + drone_distance;
        }

        static double chromo_measurer(vector<Chromo> t_chromes, Car t_car){
            Drone drone = *t_car.getDrone();
            Point last_car_point = t_chromes.at(0).getPoint();
            Point last_drone_point = last_car_point;
            double total_value = 0;
            double car_speed = t_car.getSpeed();
            double drone_speed = drone.getSpeed();


            Chromo last_chromo = t_chromes.at(0);
            for (int i = 1; i < t_chromes.size(); i++){
                Chromo actual_chromo = t_chromes.at(i);
                Point actual_point = actual_chromo.getPoint();

                if (actual_chromo.isDeliveredByCar()){
                    total_value += (Point::distanceBetweenPoints(actual_point, last_car_point) / car_speed);
                    if (last_chromo.isDeliveredByDrone()){
                        total_value += (Point::distanceBetweenPoints(actual_point, last_drone_point) / drone_speed);
                    }
                    last_car_point = actual_point;
                }
                if (actual_chromo.isDeliveredByDrone()){
                    total_value += (Point::distanceBetweenPoints(actual_point, last_drone_point) / drone_speed);
                }
                last_drone_point = actual_point;
                last_chromo = actual_chromo;
            }
            return total_value;

        }
};

#endif