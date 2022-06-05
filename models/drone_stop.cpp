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
bool DroneStop::is_first(){
    return m_prev == nullptr;
}
bool DroneStop::is_last(){
    return m_next == nullptr;
}
Point* DroneStop::getPoint(){
    return m_point;
}


// SETTERS //
void DroneStop::calcCosts(double t_cost){
    m_cost = t_cost;
}


// OPERATIONS //
void DroneStop::eraseUpBottom(){
    if(m_point != nullptr)
        m_point->erase();

    delete this;
}
void DroneStop::eraseBottomUp(){
    if(m_point != nullptr)
        m_point->erase();

    if (m_next != nullptr)
        m_next->m_prev = m_prev;
    if (m_prev != nullptr)
        m_prev->m_next = m_next;

    m_this_flight->eraseBottomUp();

    delete this;
}


// PRINTING //
string DroneStop::toString(){
    std::stringstream cost;
    cost << std::fixed << std::setprecision(2) << m_cost;
    string str = "Point: " + m_point->toString() + " - Total cost: " + cost.str();
    return str;
}

#endif