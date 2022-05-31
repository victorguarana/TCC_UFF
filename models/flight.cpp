#ifndef FLIGHT_CPP
#define FLIGHT_CPP

#include<iostream>

#include "flight.hpp"

// #include "car_stop.cpp"
#include "drone_stop.cpp"
#include "vehicles/drone.cpp"
// #include "point.cpp"

using namespace std;

// INITIALIZER //
// Flight(CarStop* t_begin, Drone* t_drone){
//     m_begin = t_begin;
//     m_end = nullptr;
//     m_first_point = nullptr;
//     m_drone = t_drone;
//     size = 0;

// }
Flight::Flight(CarStop* t_begin, Drone* t_drone){
    m_begin = t_begin;
    m_end = nullptr;
    m_first_point = nullptr;
    m_drone = t_drone;
    size = 0;
}

// GETTERS //
// Point* getInitialPoint(){
//     return m_begin->getPoint();
// }
// Point* getFinalPoint(){
//     return m_end->getPoint();
// }

// SETTER //
void Flight::setFirstStop(DroneStop* t_stop){
    m_first_point = t_stop;
}

// Add point to route
/*
void addPoint(Route* t_route, Point t_point){
    DroneStop* p_drone_stop = t_route->createDroneStop(t_point);
    addStop(p_drone_stop);
}
*/

// Add stop to route
// TODO: Add pointer to last drone stop;
void Flight::addStop(DroneStop* t_drone_stop){
    if(m_first_point == nullptr){
        m_first_point = t_drone_stop;
    }
    else {
        DroneStop* p_actual_stop = m_first_point;
        while(p_actual_stop->m_next != nullptr){
            p_actual_stop = p_actual_stop->m_next;
        }
        p_actual_stop->m_next = t_drone_stop;
    }
}

// OPERATIONS //
// void erase(){
//     m_begin->removeTakeoff();
//     m_end->removeReturn();
//     delete this;
// }


// PRINTING //
void Flight::print(int index){
    DroneStop* p_actual_stop = m_first_point;
    int index2 = 1;
    while(p_actual_stop != nullptr){
        cout << "  STOP #" << to_string(index)<< "." << to_string(index2) << " -> " << p_actual_stop->toString() << endl; 
        p_actual_stop = p_actual_stop->m_next;
        index2++;
    }
}

#endif