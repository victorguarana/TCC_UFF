#ifndef DRONESTOP_CPP
#define DRONESTOP_CPP

#include "drone_stop.hpp"

#include "point.cpp"

DroneStop::DroneStop(Flight* t_this_flight, Point t_point){
    m_this_flight = t_this_flight;
    m_point = t_point;
    m_cost = -1;
    m_next = nullptr;
    m_prev = nullptr;
}

// GETTERS//
bool DroneStop::is_first(){
    return m_prev == nullptr;
}
bool DroneStop::is_last(){
    return m_next == nullptr;
}

// PRINTING //
string DroneStop::toString(){
    string str = "Point: " + m_point.toString() + " - Total cost: ...";
    return str;
}

#endif