#ifndef ILS_CPP
#define ILS_CPP

#include <string>
#include <iostream>

#include "../models/car_stop.hpp"
#include "../models/drone_stop.hpp"
#include "../models/route.hpp"
#include "../models/flight.hpp"
#include "../models/point.cpp"
//#include "../models/point.cpp"

using namespace std;

class Ils{
    private:
    struct Stops{
        CarStop* p_car_stop;
        DroneStop* p_drone_stop;
    };

    static Stops findWorstStops(Route* t_route){
        CarStop* p_actual_car_stop = t_route->getFirstStop();
        CarStop* p_worst_car_stop = p_actual_car_stop;
        DroneStop* p_actual_drone_stop, *p_worst_drone_stop;
        double actual_car_cost, actual_drone_cost, worst_drone_cost=-1, worst_car_cost=-1;

        while(p_actual_car_stop != nullptr){
            actual_car_cost = p_actual_car_stop->getCost();

            // Define CarStop cost
            if (p_actual_car_stop->getPoint()->is_client()){
                if (actual_car_cost > worst_car_cost){
                    worst_car_cost = actual_car_cost;
                    p_worst_car_stop = p_actual_car_stop;
                }
            }

            //Define DroneStop cost
            if(p_actual_car_stop->is_takeoff()){
                p_actual_drone_stop = findWorstDroneStopInFlight(p_actual_car_stop->getTakeoffFlight());
                actual_drone_cost = p_actual_drone_stop->getCost();
                if(actual_drone_cost > worst_drone_cost){
                    worst_drone_cost = actual_drone_cost;
                    p_worst_drone_stop = p_actual_drone_stop;
                }
            }

            p_actual_car_stop = p_actual_car_stop->m_next;
        }
    
    Stops stops = { p_worst_car_stop, p_worst_drone_stop };

    return stops;
    }

    static DroneStop* findWorstDroneStopInFlight(Flight* t_flight){
        DroneStop* p_actual_stop = t_flight->getFirstStop();
        DroneStop* p_worst_stop = p_actual_stop;
        double actual_cost, worst_cost = -1;

        while (p_actual_stop != nullptr){
            actual_cost = p_actual_stop->getCost();
            if (actual_cost > worst_cost){
                worst_cost = actual_cost;
                p_worst_stop = p_actual_stop;
            }

            p_actual_stop = p_actual_stop->m_next;
        }

        return p_worst_stop;
    }

    public:

    static void printWorstsStops(Route* t_route){
        Stops stops = findWorstStops(t_route);
        cout << "Worst Car Stop: " + stops.p_car_stop->toString() << endl;
        cout << "Worst Drone Stop: " + stops.p_drone_stop->toString() << endl;
    }
};

#endif
