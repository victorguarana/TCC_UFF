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
};

#endif