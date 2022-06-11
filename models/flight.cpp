#ifndef FLIGHT_CPP
#define FLIGHT_CPP

#include<iostream>

#include "flight.hpp"

#include "drone_stop.cpp"
#include "vehicles/drone.cpp"

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


// SETTERS //
void Flight::setTotalCost(double t_total_cost){
    m_total_cost = t_total_cost;
}
void Flight::setTakeoffStop(CarStop* t_car_stop){
    m_takeoff = t_car_stop;
    t_car_stop->setTakeoffFlight(this);
}
void Flight::setLandingStop(CarStop* t_car_stop){
    m_landing = t_car_stop;
    t_car_stop->setReturnFlight(this);
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
// Remove from route (To erase this instance, set erase = true)
void Flight::removeDroneStop(DroneStop* t_remove_stop, bool erase){
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

    if(erase)
        t_remove_stop->eraseUpBottom();
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
void Flight::eraseUpBottom(){
    if(m_first_stop != nullptr){
        DroneStop* actual_stop = m_first_stop;
        while (actual_stop != nullptr){
            actual_stop = actual_stop->m_next;
            actual_stop->m_prev->eraseUpBottom();
        }
        actual_stop->eraseUpBottom();
    }
    if(m_last_stop != nullptr)
        m_last_stop->eraseUpBottom();

    delete this;
}
void Flight::eraseBottomUp(){
    if (m_last_stop == nullptr && m_first_stop == nullptr){
        if(m_takeoff != nullptr)
            m_takeoff->removeTakeoff();
        if(m_landing != nullptr)
            m_landing->removeReturn();

        delete this;
    }
}
void Flight::attachFlight(Flight* t_flight){
    m_landing = t_flight->getLandingStop();

    // Get last drone stop
    DroneStop* p_last_stop = m_first_stop;
    while(p_last_stop->m_next != nullptr)
        p_last_stop = p_last_stop->m_next;


    DroneStop* p_actual_stop = t_flight->getFirstStop();
    while(p_actual_stop != nullptr){
        p_last_stop->m_next = p_actual_stop;
        p_actual_stop->m_prev = p_last_stop;

        p_last_stop = p_actual_stop;
        p_actual_stop = p_actual_stop->m_next;
    }

    delete t_flight;
}



// PRINTING //
void Flight::print(int index){
    DroneStop* p_actual_stop = m_first_stop;
    int index2 = 1;
    while(p_actual_stop != nullptr){
        cout << " |- STOP #" << to_string(index)<< "." << to_string(index2) << " -> " << p_actual_stop->toString() << endl; 
        p_actual_stop = p_actual_stop->m_next;
        index2++;
    }
}

#endif