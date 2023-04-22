#ifndef ILS_CPP
#define ILS_CPP

#include <string>
#include <iostream>

#include "../models/car_stop.hpp"
#include "../models/drone_stop.hpp"
#include "../models/route.hpp"
#include "../models/flight.hpp"
#include "../models/point.cpp"

using namespace std;

class Ils{
    private:
    struct Stops{
        CarStop* p_car_stop;
        DroneStop* p_drone_stop;
    };

    static CarStop* findWorstCarStop(Route* t_route){
        CarStop* p_actual_car_stop = t_route->getFirstStop();
        CarStop* p_worst_car_stop = nullptr;
        double actual_car_cost, worst_car_cost=-1;

        while(p_actual_car_stop != nullptr){
            actual_car_cost = p_actual_car_stop->getCost();

            // Define CarStop cost
            if (p_actual_car_stop->getPoint()->isClient()){
                if (actual_car_cost > worst_car_cost){
                    worst_car_cost = actual_car_cost;
                    p_worst_car_stop = p_actual_car_stop;
                }
            }

            p_actual_car_stop = p_actual_car_stop->m_next;
        }

        return p_worst_car_stop;
    }

    static DroneStop* findWorstDroneStop(Route* t_route){
        CarStop* p_actual_car_stop = t_route->getFirstStop();
        DroneStop* p_actual_drone_stop, *p_worst_drone_stop = nullptr;
        double actual_drone_cost, worst_drone_cost=-1;

        while(p_actual_car_stop != nullptr){
            //Define DroneStop cost
            if(p_actual_car_stop->isTakeoff()){
                vector<Flight*> flights = p_actual_car_stop->getTakeoffFlights();
                for(int i = 0; i < flights.size(); i++){
                    p_actual_drone_stop = findWorstDroneStopInFlight(flights.at(i));
                    actual_drone_cost = p_actual_drone_stop->getCost();
                    if(actual_drone_cost > worst_drone_cost){
                        worst_drone_cost = actual_drone_cost;
                        p_worst_drone_stop = p_actual_drone_stop;
                    }
                }
                
            }

            p_actual_car_stop = p_actual_car_stop->m_next;
        }
    
        return p_worst_drone_stop;
    }

    static DroneStop* findSecondWorstDroneStop(Route* t_route, DroneStop* t_worst_drone_stop){
        Drone* p_drone = t_worst_drone_stop->getFlight()->getDrone();

        CarStop* p_actual_car_stop = t_route->getFirstStop();
        DroneStop* p_actual_drone_stop, *p_worst_drone_stop = nullptr;
        double actual_drone_cost, worst_drone_cost=-1;

        while(p_actual_car_stop != nullptr){
            //Define DroneStop cost
            if(p_actual_car_stop->isTakeoff()){
                vector<Flight*> flights = p_actual_car_stop->getTakeoffFlights();
                for(int i = 0; i < flights.size(); i++){
                    // Ignore flights that belongs to the drone that has the worst stop
                    if(p_drone == flights.at(i)->getDrone())
                        continue;

                    p_actual_drone_stop = findWorstDroneStopInFlight(flights.at(i));
                    actual_drone_cost = p_actual_drone_stop->getCost();
                    if(actual_drone_cost > worst_drone_cost){
                        worst_drone_cost = actual_drone_cost;
                        p_worst_drone_stop = p_actual_drone_stop;
                    }
                }
                
            }

            p_actual_car_stop = p_actual_car_stop->m_next;
        }
    
        return p_worst_drone_stop;
    }

    static Stops findWorstStops(Route* t_route){
        CarStop* p_actual_car_stop = t_route->getFirstStop();
        CarStop* p_worst_car_stop = nullptr;
        DroneStop* p_actual_drone_stop, *p_worst_drone_stop = nullptr;
        double actual_car_cost, actual_drone_cost, worst_drone_cost=-1, worst_car_cost=-1;

        while(p_actual_car_stop != nullptr){
            actual_car_cost = p_actual_car_stop->getCost();

            // Define CarStop cost
            if (p_actual_car_stop->getPoint()->isClient()){
                if (actual_car_cost > worst_car_cost){
                    worst_car_cost = actual_car_cost;
                    p_worst_car_stop = p_actual_car_stop;
                }
            }

            //Define DroneStop cost
            if(p_actual_car_stop->isTakeoff()){
                vector<Flight*> flights = p_actual_car_stop->getTakeoffFlights();
                for(int i = 0; i < flights.size(); i++){
                    p_actual_drone_stop = findWorstDroneStopInFlight(flights.at(i));
                    actual_drone_cost = p_actual_drone_stop->getCost();
                    // Avoid to select a stop that cant be delivered by a drone
                    if (p_actual_car_stop->getPoint()->getPackage() <= Drone::defaultStorage())
                        if(actual_drone_cost > worst_drone_cost){
                            worst_drone_cost = actual_drone_cost;
                            p_worst_drone_stop = p_actual_drone_stop;
                        }
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

    // TODO: Check if carStop can be added to split any flight?
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
                if(t_route->isValid()){
                    best_cost = actual_cost;
                    best_insertion_position = actual_stop;
                }
            }
            t_route->removeCarStop(t_new_car_stop);

            actual_stop = actual_stop->m_next;
        }

        if(best_insertion_position != nullptr)
            t_route->insertCarStop(best_insertion_position, t_new_car_stop);
        else
            cout << "# WARNING!\nCould not find any new insertion position for the worst Drone Stop." << endl;
    }

    static void addDroneStopToRoute(Route* t_route, DroneStop* t_new_drone_stop){
        //Drone* p_drone = t_route->getCar()->getDrone();
        Car* p_car = t_route->getCar();
        CarStop* p_actual_car_stop = t_route->getFirstStop();

        Drone* best_drone_to_insert = nullptr;
        DroneStop* best_stop_insertion_position = nullptr;
        CarStop* best_flight_insertion_position = nullptr;
        Flight* best_flight_to_insert = nullptr;
        double actual_cost = 0, best_cost_diff = -1, new_cost = 0;

        // Getting best insertion point
        while(p_actual_car_stop->m_next != nullptr){

            // Trying to position new drone stop in all flights
            if (p_actual_car_stop->isTakeoff()){
                //p_drone->takeOff(p_actual_car_stop->getPoint());

                vector<Flight*> flights = p_actual_car_stop->getTakeoffFlights();
                for(int i = 0; i < flights.size(); i++){
                    Flight* p_actual_flight = flights.at(i);
                    DroneStop* p_actual_drone_stop = p_actual_flight->getFirstStop();
                    actual_cost = p_actual_flight->getTotalCost();

                    // Trying to insert in the first position
                    p_actual_flight->appendDroneStopFirst(t_new_drone_stop);
                    p_actual_flight->calcCosts();
                    new_cost = p_actual_flight->getTotalCost();
                    if (best_cost_diff == -1 || (new_cost - actual_cost) < best_cost_diff){
                        if(t_route->isValid()){
                            best_cost_diff = new_cost - actual_cost;
                            best_stop_insertion_position = nullptr;
                            best_flight_insertion_position = p_actual_car_stop;
                            best_flight_to_insert = p_actual_flight;
                        }
                    }
                    p_actual_flight->removeDroneStop(t_new_drone_stop);

                    // Trying to insert in all others positions
                    while(p_actual_drone_stop != nullptr){
                        p_actual_flight->insertDroneStop(p_actual_drone_stop, t_new_drone_stop);
                        p_actual_flight->calcCosts();
                        new_cost = p_actual_flight->getTotalCost();
                        if (best_cost_diff == -1 || (new_cost - actual_cost) < best_cost_diff){
                            if(t_route->isValid()){
                                best_cost_diff = new_cost - actual_cost;
                                best_stop_insertion_position = p_actual_drone_stop;
                                best_flight_insertion_position = nullptr;
                                best_flight_to_insert = p_actual_flight;
                            }
                        }
                        p_actual_flight->removeDroneStop(t_new_drone_stop);

                        p_actual_drone_stop = p_actual_drone_stop->m_next;
                    }
                }
            }

            // Trying to create new flight to position the new drone stop
            else if (p_actual_car_stop->isReturn()){
                vector<Flight*> flights = p_actual_car_stop->getReturnFlights();
                for(int i = 0; i < flights.size(); i++){
                    flights.at(i)->getDrone()->land();
                }

                // Get a docked drone
                Drone* p_drone = nullptr;
                for(int i = 0; i < p_car->getDrones().size(); i++){
                    p_drone = p_car->getDrones().at(i);
                    if(!p_drone->isFlying())
                        break;
                }


                //p_drone->takeOff(p_actual_car_stop->getPoint());
                Flight* p_new_flight = Flight::create(p_actual_car_stop, p_drone);
                p_new_flight->appendDroneStopFirst(t_new_drone_stop);
                p_new_flight->setLandingStop(p_actual_car_stop->m_next);
                p_new_flight->calcCosts();
                actual_cost = p_new_flight->getTotalCost();
                if (best_cost_diff == -1 || actual_cost < best_cost_diff){
                    if(t_route->isValid()){
                        best_cost_diff = actual_cost;
                        best_flight_insertion_position = p_actual_car_stop;
                        best_stop_insertion_position = nullptr;
                        best_flight_to_insert = nullptr;
                        best_drone_to_insert = p_drone;
                    }
                }
                p_new_flight->removeFromRoute();
                p_new_flight->erase();
            }

            p_actual_car_stop = p_actual_car_stop->m_next;
        }

        // Inserting in best position (if not null)
        if (best_stop_insertion_position != nullptr){
            Flight* p_best_flight = best_stop_insertion_position->getFlight();
            p_best_flight->insertDroneStop(best_stop_insertion_position, t_new_drone_stop);
        }
        else if(best_flight_insertion_position != nullptr){
            // Insert in first position of an existing flight
            if (best_flight_to_insert != nullptr){
                best_flight_to_insert->appendDroneStopFirst(t_new_drone_stop);
            }
            // Create a new flight
            else{
                Flight* p_new_flight = Flight::create(best_flight_insertion_position, best_drone_to_insert);
                p_new_flight->appendDroneStopFirst(t_new_drone_stop);
                p_new_flight->setLandingStop(best_flight_insertion_position->m_next);
                best_flight_insertion_position->addTakeoffFlight(p_new_flight);
            }
        }
        else {
            cout << "# WARNING!\nCould not find any new insertion position for the worst Car Stop." << endl;
        }
    }

    static void printWorstsStops(Stops t_stops){
        cout << "Worst Car Stop: " + t_stops.p_car_stop->toString() << endl;
        cout << "Worst Drone Stop: " + t_stops.p_drone_stop->toString() << endl;
    }

    public:


    static void shiftWorstDroneToCarStop(Route* t_route){
        DroneStop* remove_drone_stop = findWorstDroneStop(t_route);

        cout << "Worst Drone Stop: " + remove_drone_stop->toString() << endl;

        CarStop* new_car_stop = CarStop::create(t_route, remove_drone_stop->getPoint());

        Flight* p_drone_stop_flight = remove_drone_stop->getFlight();
        remove_drone_stop->removeFromRoute();
        remove_drone_stop->erase();
        if (p_drone_stop_flight->isEmpty()){
            p_drone_stop_flight->removeFromRoute();
            p_drone_stop_flight->erase();
        }

        addCarStopToRoute(t_route, new_car_stop);
    }

    static void shiftWorstCarToDroneStop(Route* t_route){
        CarStop* remove_car_stop = findWorstCarStop(t_route);

        cout << "Worst Car Stop: " + remove_car_stop->toString() << endl;

        DroneStop* new_drone_stop = DroneStop::create(nullptr, remove_car_stop->getPoint());

        remove_car_stop->removeFromRoute();
        remove_car_stop->erase();

        addDroneStopToRoute(t_route, new_drone_stop);

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
        if (p_drone_stop_flight->isEmpty()){
            p_drone_stop_flight->removeFromRoute();
            p_drone_stop_flight->erase();
        }

        remove_car_stop->removeFromRoute();
        remove_car_stop->erase();

        addCarStopToRoute(t_route, new_car_stop);
        addDroneStopToRoute(t_route, new_drone_stop);

    }

    static void swapWorstsDroneStops(Route* t_route){
        DroneStop* p_worst_drone_stop_1 = findWorstDroneStop(t_route);
        DroneStop* p_worst_drone_stop_2 = findSecondWorstDroneStop(t_route, p_worst_drone_stop_1);

        cout << "Worst Drone Stop: " + p_worst_drone_stop_1->toString() << endl;
        cout << "Second Worst Drone Stop: " + p_worst_drone_stop_2->toString() << endl;

        DroneStop* p_new_drone_stop_1 = DroneStop::create(nullptr, p_worst_drone_stop_2->getPoint());
        DroneStop* p_new_drone_stop_2 = DroneStop::create(nullptr, p_worst_drone_stop_1->getPoint());


        Flight* p_drone_stop_flight = p_worst_drone_stop_1->getFlight();
        p_worst_drone_stop_1->removeFromRoute();
        p_worst_drone_stop_1->erase();
        if (p_drone_stop_flight->isEmpty()){
            p_drone_stop_flight->removeFromRoute();
            p_drone_stop_flight->erase();
        }

        p_drone_stop_flight = p_worst_drone_stop_2->getFlight();
        p_worst_drone_stop_2->removeFromRoute();
        p_worst_drone_stop_2->erase();
        if (p_drone_stop_flight->isEmpty()){
            p_drone_stop_flight->removeFromRoute();
            p_drone_stop_flight->erase();
        }


        addDroneStopToRoute(t_route, p_new_drone_stop_1);
        addDroneStopToRoute(t_route, p_new_drone_stop_2);

    }

    // This swap is not used anymore
    /*
    static void swapWorstsCarStops(Route* t_route1, Route* t_route2){
        CarStop* p_worst_car_stop_1 = findWorstCarStop(t_route1);
        CarStop* p_worst_car_stop_2 = findWorstCarStop(t_route2);

        cout << "Worst Car Stop 1: " + p_worst_car_stop_1->toString() << endl;
        cout << "Worst Car Stop 2: " + p_worst_car_stop_2->toString() << endl;

        CarStop* p_new_car_stop_1 = CarStop::create(t_route1, p_worst_car_stop_2->getPoint());
        CarStop* p_new_car_stop_2 = CarStop::create(t_route2, p_worst_car_stop_1->getPoint());

        p_worst_car_stop_1->removeFromRoute();
        p_worst_car_stop_1->erase();
        p_worst_car_stop_2->removeFromRoute();
        p_worst_car_stop_2->erase();

        addCarStopToRoute(t_route1, p_new_car_stop_1);
        addCarStopToRoute(t_route2, p_new_car_stop_2);

    }
    */
};

#endif
