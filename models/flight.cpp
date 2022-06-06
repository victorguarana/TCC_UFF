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


// SETTER //
void Flight::setTotalCost(double t_total_cost){
    m_total_cost = t_total_cost;
}

// SETTER //
void Flight::setTakeoffStop(CarStop* t_car_stop){
    m_takeoff = t_car_stop;
}
void Flight::setLandingStop(CarStop* t_car_stop){
    m_landing = t_car_stop;
}

void Flight::appendDroneStop(DroneStop* t_drone_stop){
    if (m_first_stop == nullptr){
        m_first_stop = t_drone_stop;
    }
    else {
        m_last_stop->m_next = t_drone_stop;
        t_drone_stop->m_prev = m_last_stop;
    }
    m_last_stop = t_drone_stop;
}


// OPERATIONS //
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
    if(m_takeoff != nullptr)
        m_takeoff->setTakeoffFlight(nullptr);
    if(m_landing != nullptr)
        m_landing->setReturnFlight(nullptr);

    delete this;
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