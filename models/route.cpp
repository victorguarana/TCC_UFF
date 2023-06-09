#ifndef ROUTE_CPP
#define ROUTE_CPP

#include <iostream>
#include <vector>

#include "route.hpp"

#include "vehicles/vehicle.hpp"
#include "vehicles/car.hpp"
#include "vehicles/drone.hpp"
#include "point.hpp"
#include "car_stop.hpp"
// #include "drone_stop.cpp"
#include "flight.hpp"

using namespace std;


// INITIALIZER //
Route::Route(Car* t_car){
    m_car = t_car;
    m_first_stop = nullptr;
    m_last_stop = nullptr;
}


// GETTER //
CarStop* Route::getFirstStop(){
    return m_first_stop;
}
CarStop* Route::getLastStop(){
    return m_last_stop;
}
Car* Route::getCar(){
    return m_car;
}
double Route::getTotalCost(){
    return m_total_cost;
}


// SETTER //
void Route::setTotalCost(double t_total_cost){
    m_total_cost = t_total_cost;
}


// LINKED LIST FUNCTIONS //
// Add to first position
void Route::appendCarStopFront(CarStop* t_car_stop){
    if (m_last_stop == nullptr){
        m_last_stop = t_car_stop;
    }
    else{
        CarStop* p_first_stop = m_first_stop;
        p_first_stop->m_prev = t_car_stop;
        t_car_stop->m_next = p_first_stop;
    }
    m_first_stop = t_car_stop;
}
// Add to last position
void Route::appendCarStopBack(CarStop* t_car_stop){
    if (m_first_stop == nullptr){
        m_first_stop = t_car_stop;
    }
    else{
        CarStop* p_last_stop = m_last_stop;
        p_last_stop->m_next = t_car_stop;
        t_car_stop->m_prev = p_last_stop;
    }
    m_last_stop = t_car_stop;
}
// Insert Car Stop after an existing stop
void Route::insertCarStop(CarStop* t_previous_stop, CarStop* t_new_stop){
    if (m_last_stop == t_previous_stop)
        m_last_stop = t_new_stop;

    CarStop* p_next_stop = t_previous_stop->m_next;
    if (p_next_stop != nullptr)
        p_next_stop->m_prev = t_new_stop;

    t_previous_stop->m_next = t_new_stop;

    t_new_stop->m_next = p_next_stop;
    t_new_stop->m_prev = t_previous_stop;
}
void Route::removeCarStop(CarStop* t_remove_stop){
    CarStop* t_prev = t_remove_stop->m_prev;
    CarStop* t_next = t_remove_stop->m_next;

    if(m_first_stop == t_remove_stop){
        m_first_stop = t_remove_stop->m_next;
    }
    if(m_last_stop == t_remove_stop){
        m_last_stop = t_remove_stop->m_prev;
    }

    if(t_prev != nullptr)
        t_prev->m_next = t_next;
    if(t_next != nullptr)
        t_next->m_prev = t_prev;
}


// OTHER FUNCTIONS //
double Route::calcFlightDelay(Flight* t_flight, double t_actual_delay){
    double drone_speed = t_flight->getDrone()->getSpeed();
    double car_speed = t_flight->getLandingStop()->getRoute()->getCar()->getSpeed();
    double drone_time = t_flight->getTotalCost();
    double car_time = 0, zero = 0;
    CarStop* p_actual_car_stop = t_flight->getTakeoffStop();
    CarStop* p_last_car_stop = t_flight->getTakeoffStop();

    while(p_actual_car_stop != p_last_car_stop){
        car_time += Point::distanceBetweenPoints(*p_actual_car_stop->getPoint(), *p_actual_car_stop->m_next->getPoint());
        p_actual_car_stop = p_actual_car_stop->m_next;
    }

    return std::max(zero, drone_time-(car_time+t_actual_delay));
}

void Route::calcCosts(){
    m_total_cost = 0;
    double car_speed = m_car->getSpeed();

    CarStop* last_stop = m_first_stop;
    CarStop* actual_stop = last_stop->m_next;
    CarStop* next_stop = actual_stop->m_next;
    double distance_backward, distance_forward, flight_cost;

    vector<ActiveFlights> active_flights;

    if (m_first_stop->isTakeoff()){
        vector<Flight*> takeoff_flights = m_first_stop->getTakeoffFlights();
        for(int i = 0; i < takeoff_flights.size(); i++){
            Flight* p_actual_flight = takeoff_flights.at(i);
            p_actual_flight->calcCosts();
            ActiveFlights af;
            af.flight = p_actual_flight;
            af.ground_delay_time = 0;
            active_flights.push_back(af);
        }
    }

    while (actual_stop->m_next != nullptr){
        distance_backward = Point::distanceBetweenPoints(*last_stop->getPoint(), *actual_stop->getPoint());
        distance_forward = Point::distanceBetweenPoints(*actual_stop->getPoint(), *next_stop->getPoint());

        actual_stop->setCost(distance_backward + distance_forward);
        m_total_cost += distance_backward / car_speed;

        if (actual_stop->isTakeoff()){
            vector<Flight*> takeoff_flights = actual_stop->getTakeoffFlights();
            for(int i = 0; i < takeoff_flights.size(); i++){
                Flight* p_actual_flight = takeoff_flights.at(i);
                p_actual_flight->calcCosts();
                active_flights.push_back({p_actual_flight, 0});
            }
        }
        // Add return flight wait time
        if(actual_stop->isReturn()){
            vector<Flight*> return_flights = actual_stop->getReturnFlights();
            for(int i = 0; i < return_flights.size(); i++){
                Flight* p_return_flight = return_flights.at(i);
                double ground_delay, zero = 0;

                // Get flight ground delay
                for(int j = 0; j < active_flights.size(); j++){
                    if(active_flights.at(j).flight == p_return_flight){
                        ground_delay = active_flights.at(j).ground_delay_time;
                        active_flights.erase(active_flights.begin() + j);
                        break;
                    }
                }

                double flight_delay = calcFlightDelay(return_flights.at(i), ground_delay);

                // Add flight ground delay for other active flights
                for(int j = 0; j < active_flights.size(); j++){
                    active_flights.at(j).ground_delay_time = active_flights.at(j).ground_delay_time + flight_delay;
                }

                m_total_cost += flight_delay;
            }
        }

        last_stop = actual_stop;
        actual_stop = last_stop->m_next;
        next_stop = actual_stop->m_next;
    }
    m_total_cost += distance_forward / car_speed;
}
void Route::appendPoint(Point* t_point){
    CarStop* p_new_stop = CarStop::create(this, t_point);
    appendCarStopBack(p_new_stop);
}
bool Route::isValid(){
    CarStop* actual_stop = m_first_stop;
    Car* actual_car = m_car;

    // Move car to first position in route
    actual_car->deliver(actual_stop->getPoint());

    double actual_distance_required;
    double actual_storage_required;

    while(actual_stop != m_last_stop){

        actual_distance_required = Point::distanceBetweenPoints(*actual_stop->getPoint(), *actual_stop->m_next->getPoint());
        actual_storage_required = actual_stop->getPoint()->getPackage();
        if (!actual_car->canDeliver(actual_distance_required, actual_storage_required))
            return false;

        actual_car->deliver(actual_stop->getPoint());
        if(actual_stop->isTakeoff()){
            vector<Flight*> takeoff_flights = actual_stop->getTakeoffFlights();
            for(int i = 0; i < takeoff_flights.size(); i++){
                if (!takeoff_flights.at(i)->isValid())
                    return false;
            }
        }

        actual_stop = actual_stop->m_next;
    }

    return true;
}

// Copy an Route and return a pointer to the new one
Route* Route::duplicate(){
    Route* new_route = new Route(m_car);
    new_route->m_total_cost = m_total_cost;

    if (m_first_stop != nullptr){
        new_route->m_first_stop = m_first_stop->duplicate(new_route);

        new_route->m_last_stop = new_route->m_first_stop;
        while(new_route->m_last_stop->m_next != nullptr)
            new_route->m_last_stop = new_route->m_last_stop->m_next;
    }
    
    return new_route;
}

void Route::erase(){
    while(m_first_stop != nullptr){
        m_first_stop->erase();
        m_first_stop = m_first_stop->m_next;
    }
    delete this;
}


// PRINTING //
void Route::print(){
    if (m_first_stop == nullptr)
        return;

    cout << "Route of: " + m_car->getName() << endl;

    int index = 1;
    CarStop* actual_stop = m_first_stop;
    while (actual_stop != nullptr){
        cout << "STOP #" << to_string(index) << " -> " << actual_stop->toString() << endl;

        if (actual_stop->isTakeoff()){
            vector<Flight*> takeoff_flights = actual_stop->getTakeoffFlights();
            for(int i = 0; i < takeoff_flights.size(); i++)
                takeoff_flights.at(i)->print(index);
        }
        actual_stop = actual_stop->m_next;
        index++;
    }

    std::stringstream total_cost;
    total_cost << std::fixed << std::setprecision(2) << m_total_cost;
    cout << "Route Total Cost: " << total_cost.str() << endl;
}

#endif