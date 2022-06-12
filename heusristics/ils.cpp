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

    static void addCarStopToRoute(Route* t_route, CarStop* t_new_car_stop){
        // Do not consider drone route in this method
        CarStop* actual_stop = t_route->getFirstStop();
        CarStop* best_insertion_position = nullptr;
        double actual_cost = 0, best_cost = -1;

        while(actual_stop->m_next != nullptr){

            t_route->insertCarStop(actual_stop, t_new_car_stop);
            t_route->calcCosts();
            actual_cost = t_route->getTotalCost();
            if (best_cost == -1 || actual_cost < best_cost){
                best_cost = actual_cost;
                best_insertion_position = actual_stop;
            }
            t_route->removeCarStop(t_new_car_stop);

            actual_stop = actual_stop->m_next;
        }
    t_route->insertCarStop(best_insertion_position, t_new_car_stop);
    }

    static void addDroneStopToRoute(Route* t_route, DroneStop* t_new_drone_stop){
        Drone* p_drone = t_route->getCar()->getDrone();

        CarStop* p_actual_car_stop = t_route->getFirstStop();
        DroneStop* best_stop_insertion_position = nullptr;
        CarStop* best_flight_insertion_position = nullptr;
        double actual_cost = 0, best_cost_diff = -1, new_cost = 0;

        while(p_actual_car_stop->m_next != nullptr){

            // Trying to position new drone stop in this flight
            if (p_actual_car_stop->is_takeoff()){
                p_drone->takeOff(p_actual_car_stop->getPoint());
                Flight* p_actual_flight = p_actual_car_stop->getTakeoffFlight();
                DroneStop* p_actual_drone_stop = p_actual_flight->getFirstStop();
                actual_cost = p_actual_flight->getTotalCost();

                // Trying to insert in the first position
                p_actual_flight->appendDroneStopFirst(t_new_drone_stop);
                p_actual_flight->calcCosts();
                new_cost = p_actual_flight->getTotalCost();
                if (best_cost_diff == -1 || (new_cost - actual_cost) < best_cost_diff){
                    best_cost_diff = new_cost - actual_cost;
                    best_stop_insertion_position = nullptr;
                    best_flight_insertion_position = p_actual_car_stop;
                }
                p_actual_flight->removeDroneStop(t_new_drone_stop);

                // Trying to insert in all others positions
                while(p_actual_drone_stop != nullptr){
                    p_actual_flight->insertDroneStop(p_actual_drone_stop, t_new_drone_stop);
                    p_actual_flight->calcCosts();
                    new_cost = p_actual_flight->getTotalCost();
                    if (best_cost_diff == -1 || (new_cost - actual_cost) < best_cost_diff){
                        best_cost_diff = new_cost - actual_cost;
                        best_stop_insertion_position = p_actual_drone_stop;
                        best_flight_insertion_position = nullptr;
                    }
                    p_actual_flight->removeDroneStop(t_new_drone_stop);

                    p_actual_drone_stop = p_actual_drone_stop->m_next;
                }
            }

            // Trying to create new flight to position the new drone stop
            else if (p_actual_car_stop->is_return() || !p_drone->isFlying()){
                p_drone->takeOff(p_actual_car_stop->getPoint());
                Flight* p_new_flight = Flight::create(p_actual_car_stop, p_drone);
                p_new_flight->appendDroneStopFirst(t_new_drone_stop);
                p_new_flight->setLandingStop(p_actual_car_stop->m_next);
                p_new_flight->calcCosts();
                actual_cost = p_new_flight->getTotalCost();
                if (best_cost_diff == 1 || actual_cost < best_cost_diff){
                    best_cost_diff = actual_cost;
                    best_flight_insertion_position = p_actual_car_stop;
                    best_stop_insertion_position = nullptr;
                }
                p_new_flight->removeFromRoute();
                p_new_flight->erase();
            }

            p_actual_car_stop = p_actual_car_stop->m_next;
        }

        if (best_stop_insertion_position != nullptr){
            Flight* p_best_flight = best_stop_insertion_position->getFlight();
            p_best_flight->insertDroneStop(best_stop_insertion_position, t_new_drone_stop);
        }
        else if(best_flight_insertion_position != nullptr){
            if (best_flight_insertion_position->is_takeoff()){
                Flight* p_best_flight = best_flight_insertion_position->getTakeoffFlight();
                p_best_flight->appendDroneStopFirst(t_new_drone_stop);
            }
            else{
                Flight* p_new_flight = Flight::create(best_flight_insertion_position, p_drone);
                p_new_flight->appendDroneStopFirst(t_new_drone_stop);
                p_new_flight->setLandingStop(best_flight_insertion_position->m_next);
            }
        }
    }

    public:

    static void printWorstsStops(Stops t_stops){
        cout << "Worst Car Stop: " + t_stops.p_car_stop->toString() << endl;
        cout << "Worst Drone Stop: " + t_stops.p_drone_stop->toString() << endl;
    }


    static void swapWorstsStops(Route* t_route){
        Stops stops = findWorstStops(t_route);
        printWorstsStops(stops);

        CarStop* remove_car_stop = stops.p_car_stop;
        DroneStop* remove_drone_stop = stops.p_drone_stop;
        CarStop* new_car_stop = CarStop::create(t_route, remove_drone_stop->getPoint());
        DroneStop* new_drone_stop = DroneStop::create(nullptr, remove_car_stop->getPoint());

        Flight* p_drone_stop_flight = remove_drone_stop->getFlight();
        remove_drone_stop->removeFromRoute();
        remove_drone_stop->erase();
        if (p_drone_stop_flight->is_empty()){
            p_drone_stop_flight->removeFromRoute();
            p_drone_stop_flight->erase();
        }

        remove_car_stop->removeFromRoute();
        remove_car_stop->erase();

        addCarStopToRoute(t_route, new_car_stop);
        addDroneStopToRoute(t_route, new_drone_stop);

    }
};

#endif
