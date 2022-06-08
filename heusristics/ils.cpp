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
        CarStop* last_stop = t_route->getFirstStop();
        CarStop* actual_stop = last_stop->m_next;
        CarStop* best_insertion_position = nullptr;
        double actual_cost = 0, best_cost = -1;

        while(actual_stop->m_next != nullptr){

            t_route->insertCarStop(actual_stop, t_new_car_stop);
            t_route->calcCosts();
            actual_cost = t_route->getTotalCost();
            if (best_cost == -1 || actual_cost < best_cost){
                best_cost = actual_cost;
                best_insertion_position = last_stop;
            }
            t_route->removeCarStop(t_new_car_stop);

            last_stop = actual_stop;
            actual_stop = last_stop->m_next;
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
            if (p_actual_car_stop->is_takeoff()){
                p_drone->takeOff();
                Flight* p_actual_flight = p_actual_car_stop->getTakeoffFlight();
                DroneStop* p_actual_drone_stop = p_actual_flight->getFirstStop();
                actual_cost = p_actual_flight->getTotalCost();

                // TODO: Try to insert before the first stop
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

            else if (p_actual_car_stop->is_return() || !p_drone->isFlying()){
                p_drone->takeOff();
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
                p_new_flight->eraseBottomUp();

            }

            p_actual_car_stop = p_actual_car_stop->m_next;
        }

        if (best_stop_insertion_position != nullptr){
            Flight* p_best_flight = best_stop_insertion_position->getFlight();
            p_best_flight->insertDroneStop(best_stop_insertion_position, t_new_drone_stop);
        }
        else if(best_flight_insertion_position != nullptr){
            Flight* p_new_flight = Flight::create(best_flight_insertion_position, p_drone);
            p_new_flight->appendDroneStopFirst(t_new_drone_stop);
            p_new_flight->setLandingStop(best_flight_insertion_position->m_next);
        }
    }

    public:

    static void printWorstsStops(Route* t_route){
        Stops stops = findWorstStops(t_route);
        cout << "Worst Car Stop: " + stops.p_car_stop->toString() << endl;
        cout << "Worst Drone Stop: " + stops.p_drone_stop->toString() << endl;
    }


    // TODO: Adicionar opção de dividir voo do drone na metade (Transformar DroneStop->CarStop)
    static void swapWorstsStops(Route* t_route){
        Stops stops = findWorstStops(t_route);

        //cout << "Removed Car Stop: " + carstop.toString() << endl;
        //cout << "Removed Drone Stop: " + dronestop.toString() << endl;
    
        CarStop* remove_car_stop = stops.p_car_stop;
        DroneStop* remove_drone_stop = stops.p_drone_stop;
        CarStop* new_car_stop = CarStop::create(t_route, remove_drone_stop->getPoint());
        DroneStop* new_drone_stop = DroneStop::create(nullptr, remove_car_stop->getPoint());

        remove_drone_stop->eraseBottomUp();
        remove_car_stop->eraseBottomUp();

        addCarStopToRoute(t_route, new_car_stop);
        addDroneStopToRoute(t_route, new_drone_stop);

    }
};

#endif
