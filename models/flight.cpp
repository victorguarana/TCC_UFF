#ifndef FLIGHT_CPP
#define FLIGHT_CPP

#include<iostream>

#include "flight.hpp"

#include "car_stop.hpp"
#include "drone_stop.hpp"
#include "point.hpp"
#include "route.hpp"
#include "vehicles/car.hpp"
#include "vehicles/drone.hpp"

using namespace std;


// PRIVATE INITIALIZER //
Flight::Flight(CarStop* t_begin, Drone* t_drone){
    m_takeoff = t_begin;
    m_landing = nullptr;
    m_first_stop = nullptr;
    m_last_stop = nullptr;
    m_drone = t_drone;
}


// PUBLIC INITIALIZER //
Flight* Flight::create(CarStop* t_begin, Drone* t_drone){
    return new Flight(t_begin, t_drone);
}


// GETTERS //
DroneStop* Flight::getFirstStop(){
    return m_first_stop;
}
double Flight::getTotalCost(){
    return m_total_cost;
}
CarStop* Flight::getTakeoffStop(){
    return m_takeoff;
}
CarStop* Flight::getLandingStop(){
    return m_landing;
}
Drone* Flight::getDrone(){
    return m_drone;
}


// SETTERS //
void Flight::setTotalCost(double t_total_cost){
    m_total_cost = t_total_cost;
}
void Flight::setTakeoffStop(CarStop* t_car_stop){
    m_takeoff = t_car_stop;
    t_car_stop->addTakeoffFlight(this);
}
void Flight::setLandingStop(CarStop* t_car_stop){
    m_landing = t_car_stop;
    t_car_stop->addReturnFlight(this);
}


// LINKED LIST FUNCTIONS //
// Add to first position
void Flight::appendDroneStopFirst(DroneStop* t_drone_stop){
    if (m_last_stop == nullptr){
        m_last_stop = t_drone_stop;
    }
    else{
        DroneStop* p_first_stop = m_first_stop;
        p_first_stop->m_prev = t_drone_stop;
        t_drone_stop->m_next = p_first_stop;
    }
    m_first_stop = t_drone_stop;
    t_drone_stop->setFlight(this);
}
// Add to last position
void Flight::appendDroneStopLast(DroneStop* t_drone_stop){
    if (m_first_stop == nullptr){
        m_first_stop = t_drone_stop;
    }
    else{
        DroneStop* p_last_stop = m_last_stop;
        p_last_stop->m_next = t_drone_stop;
        t_drone_stop->m_prev = p_last_stop;
    }
    m_last_stop = t_drone_stop;
    t_drone_stop->setFlight(this);
}
// Insert Car Stop after an existing stop
void Flight::insertDroneStop(DroneStop* t_previous_stop, DroneStop* t_new_stop){
    DroneStop* p_next_stop = t_previous_stop->m_next;
    if (p_next_stop != nullptr)
        p_next_stop->m_prev = t_new_stop;

    t_previous_stop->m_next = t_new_stop;

    t_new_stop->m_next = p_next_stop;
    t_new_stop->m_prev = t_previous_stop;
    t_new_stop->setFlight(this);
}
void Flight::removeDroneStop(DroneStop* t_remove_stop){
    DroneStop* t_prev = t_remove_stop->m_prev;
    DroneStop* t_next = t_remove_stop->m_next;

    if(m_first_stop == t_remove_stop){
        m_first_stop = t_remove_stop->m_next;
    }
    if(m_last_stop == t_remove_stop){
        m_last_stop = t_remove_stop->m_prev;
    }

    t_remove_stop->m_next = nullptr;
    t_remove_stop->m_prev = nullptr;

    if(t_prev != nullptr)
        t_prev->m_next = t_next;
    if(t_next != nullptr)
        t_next->m_prev = t_prev;    
}


// OTHER FUNCTIONS //
void Flight::calcCosts(){
    m_total_cost = 0;
    double drone_speed = m_drone->getSpeed();

    Point* p_last_point = m_takeoff->getPoint();
    Point* p_actual_point = m_first_stop->getPoint();
    Point* p_next_point;
    DroneStop* p_actual_stop = m_first_stop;
    double distance_backward, distance_forward;

    while (p_actual_stop->m_next != nullptr){
        p_next_point = p_actual_stop->m_next->getPoint();

        distance_backward = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
        distance_forward = Point::distanceBetweenPoints(*p_actual_point, *p_next_point);

        p_actual_stop->setCost(distance_backward + distance_forward);
        m_total_cost += distance_backward / drone_speed;

        p_actual_stop = p_actual_stop->m_next;
        p_last_point = p_actual_point;
        p_actual_point = p_next_point;
    }

    p_next_point = m_landing->getPoint();
    distance_backward = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
    distance_forward = Point::distanceBetweenPoints(*p_actual_point, *p_next_point);
    m_total_cost += (distance_backward + distance_forward) / drone_speed;

    p_actual_stop->setCost(distance_backward + distance_forward);
}
bool Flight::isEmpty(){
    return m_last_stop == nullptr && m_first_stop == nullptr;
}
void Flight::removeFromRoute(){
    if (m_last_stop == nullptr && m_first_stop == nullptr){
        if(m_takeoff != nullptr)
            m_takeoff->removeTakeoff(this);
        if(m_landing != nullptr)
            m_landing->removeReturn(this);
    }
}
void Flight::erase(){
    delete this;
}
void Flight::attachFlight(Flight* t_flight){
    m_landing = t_flight->getLandingStop();

    // Get last drone stop
    DroneStop* p_last_stop = m_last_stop;

    DroneStop* p_actual_stop = t_flight->getFirstStop();
    while(p_actual_stop != nullptr){
        p_last_stop->m_next = p_actual_stop;
        p_actual_stop->m_prev = p_last_stop;

        p_last_stop = p_actual_stop;
        p_actual_stop = p_actual_stop->m_next;

    }
    m_last_stop = p_last_stop;

    delete t_flight;
}
void Flight::splitToValidFlights(){
    Point* p_last_point = m_takeoff->getPoint();
    Route* p_route = m_takeoff->getRoute();
    DroneStop* p_actual_stop = m_first_stop;

    // Used inside loop
    double actual_distance_required, actual_storage_required;
    Point* p_actual_point = p_actual_stop->getPoint();

    // Find breakpoint
    m_drone->takeOff(p_actual_point);
    while(m_drone->isFlying()){

        actual_distance_required = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
        actual_storage_required = p_actual_point->getPackage();

        if(m_drone->canDeliver(actual_distance_required, actual_storage_required)){
            m_drone->deliver(p_actual_point);

            p_last_point = p_actual_point;
            p_actual_stop = p_actual_stop->m_next;
            p_actual_point = p_actual_stop->getPoint();
        }
        else{
            m_drone->land();
        }
    }
    
    // Remove actual stop from flight route
    m_last_stop = p_actual_stop->m_prev;
    m_last_stop->m_next = nullptr;
    p_actual_stop->m_prev = nullptr;

    CarStop* p_new_car_stop = CarStop::create(p_route, p_actual_point);
    // Adicionar car stop to route
    p_route->insertCarStop(m_takeoff, p_new_car_stop);

    // Case when breaking stop is the last stop
    if(p_actual_stop->m_next == nullptr){
        m_landing->removeReturn(this);
        m_landing = p_new_car_stop;
        p_new_car_stop->addReturnFlight(this);

        // delete p_actual_stop;
    }
    else{
        // Create new car stop and new flight
        Flight* p_new_flight = Flight::create(p_new_car_stop, m_drone);

        // Set Landing stops
        p_new_flight->setLandingStop(m_landing);
        m_landing->addReturnFlight(p_new_flight);
        m_landing = p_new_car_stop;
        p_new_car_stop->addReturnFlight(this);

        p_actual_stop = p_actual_stop->m_next;
        delete p_actual_stop->m_prev;

        // Move remaining drone stops to new flight
        while(p_actual_stop != nullptr){
            p_new_flight->appendDroneStopLast(p_actual_stop);
            p_actual_stop = p_actual_stop->m_next;
        }

        // Recurion until the new flight is valid
        if(!p_new_flight->isValid()){
            p_new_flight->splitToValidFlights();
        }
    }
}
bool Flight::isValid(){
    Point* p_last_point = m_takeoff->getPoint();
    DroneStop* p_actual_stop = m_first_stop;
    Car* p_car = m_takeoff->getRoute()->getCar();

    m_drone->takeOff(m_takeoff->getPoint());

    Point* p_actual_point = nullptr;
    double actual_distance_required, actual_storage_required;

    while (p_actual_stop != nullptr){
        p_actual_point = p_actual_stop->getPoint();

        actual_distance_required = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
        actual_storage_required = p_actual_point->getPackage();

        if(!m_drone->canDeliver(actual_distance_required, actual_storage_required) || !p_car->canSupport(actual_storage_required)){
            m_drone->land();
            return false;
        }

        m_drone->deliver(p_actual_point);

        p_last_point = p_actual_point;
        p_actual_stop = p_actual_stop->m_next;
    }

    // Check if drone can reach the landing position
    p_last_point = m_last_stop->getPoint();
    p_actual_point = m_landing->getPoint();

    actual_distance_required = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
    if(!m_drone->canDeliver(actual_distance_required, 0))
        return false;


    m_drone->land();
    return true;
}

Flight* Flight::duplicate(CarStop* t_takeoff, CarStop* t_landing){
    Flight* new_flight = new Flight(t_takeoff, m_drone);
    new_flight->m_landing = t_landing;
    if(m_first_stop != nullptr){
        new_flight->m_first_stop = m_first_stop->duplicate(new_flight);
        new_flight->m_first_stop->setFlight(new_flight);
    }
    return new Flight(*this);
}


// PRINTING //
void Flight::print(int index){
    DroneStop* p_actual_stop = m_first_stop;
    int index2 = 1;
    cout << " |- Flight of: " << m_drone->getName() << endl;
    cout << " |- |- Take off -> " << m_takeoff->getPoint()->getName() << endl;

    while(p_actual_stop != nullptr){
        cout << " |- |-- STOP #" << to_string(index)<< "." << to_string(index2) << " -> " << p_actual_stop->toString() << endl; 
        p_actual_stop = p_actual_stop->m_next;
        index2++;
    }
    cout << " |- |- Return -> " << m_landing->getPoint()->getName() << " - Total Flight Cost: " << to_string(m_total_cost) << endl;
    cout << " |- |- Total Flight Cost: " << to_string(m_total_cost) << endl;

}

#endif