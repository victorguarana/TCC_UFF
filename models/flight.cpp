#ifndef FLIGHT_CPP
#define FLIGHT_CPP

#include<iostream>

#include "flight.hpp"

#include "drone_stop.cpp"
#include "vehicles/drone.cpp"

using namespace std;

// PRIVATE INITIALIZER //
Flight::Flight(CarStop* t_begin, Drone* t_drone){
    m_begin = t_begin;
    m_end = nullptr;
    m_first_stop = nullptr;
    m_last_stop = nullptr;
    m_drone = t_drone;
    size = 0;
}

// PUBLIC INITIALIZER //
Flight* Flight::create(CarStop* t_begin, Drone* t_drone){
    return new Flight(t_begin, t_drone);
}

// SETTER //
void Flight::setTakeoffStop(CarStop* t_car_stop){
    m_begin = t_car_stop;
}
void Flight::setReturnStop(CarStop* t_car_stop){
    m_end = t_car_stop;
}

void Flight::appendDroneStop(DroneStop* t_drone_stop){
    if (size == 0){
        m_first_stop = t_drone_stop;
    }
    else {
        m_last_stop->m_next = t_drone_stop;
        t_drone_stop->m_prev = m_last_stop;
    }
    m_last_stop = t_drone_stop;
    size++;
}

// OPERATION //
void Flight::setCosts(){
    Point* p_last_point = m_begin->getPoint();
    Point* p_actual_point = m_first_stop->getPoint();
    Point* p_next_point;
    DroneStop* p_actual_stop = m_first_stop;
    double distance_backward, distance_forward;

    while (p_actual_stop->m_next != nullptr){
        p_next_point = p_actual_stop->m_next->getPoint();

        distance_backward = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
        distance_forward = Point::distanceBetweenPoints(*p_actual_point, *p_next_point);

        p_actual_stop->setCost(distance_backward + distance_forward);

        p_actual_stop = p_actual_stop->m_next;
        p_last_point = p_actual_point;
        p_actual_point = p_next_point;
    }

    p_next_point = m_end->getPoint();
    distance_backward = Point::distanceBetweenPoints(*p_last_point, *p_actual_point);
    distance_forward = Point::distanceBetweenPoints(*p_actual_point, *p_next_point);
    p_actual_stop->setCost(distance_backward + distance_forward);
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