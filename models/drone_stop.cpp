#ifndef DRONESTOP_CPP
#define DRONESTOP_CPP

#include "drone_stop.hpp"

#include "point.cpp"


// PRIVATE INITIALIZER //
DroneStop::DroneStop(Flight* t_this_flight, Point* t_point){
    m_this_flight = t_this_flight;
    m_point = t_point;
    m_cost = -1;
    m_next = nullptr;
    m_prev = nullptr;
}


// PUBLIC INITIALIZER //
DroneStop* DroneStop::create(Flight* t_flight, Point* t_point){
    return new DroneStop(t_flight, t_point);
}


// GETTERS//
double DroneStop::getCost(){
    return m_cost;
}
bool DroneStop::is_last(){
    return m_next == nullptr;
}
Point* DroneStop::getPoint(){
    return m_point;
}
Flight* DroneStop::getFlight(){
    return m_this_flight;
}


// SETTERS //
void DroneStop::setCost(double t_cost){
    m_cost = t_cost;
}
void DroneStop::setFlight(Flight* t_flight){
    m_this_flight = t_flight;
}


// OPERATIONS //
void DroneStop::removeFromRoute(){
    m_this_flight->removeDroneStop(this);
    if (m_this_flight->is_empty()){
        m_this_flight->removeFromRoute();
        m_this_flight->erase();
    }
}
void DroneStop::erase(){
    delete this;
}


// PRINTING //
string DroneStop::toString(){
    std::stringstream cost;
    cost << std::fixed << std::setprecision(2) << m_cost;
    string str = "Point: " + m_point->toString() + " - Stop cost: " + cost.str();

    return str;
}

#endif