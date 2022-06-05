#ifndef CARSTOP_CPP
#define CARSTOP_CPP

#include "car_stop.hpp"

#include "point.cpp"
#include "flight.cpp"

// TODO: Utilzar uma classe Stop para agrupar todos métodos iguais
// Future: When implementing multiple drones, use vectors to represent flights and return and takeoff (?)
// PRIVATE INITIALIZER //
CarStop::CarStop(Route* t_route, Point* t_point){
    m_this_route = t_route;
    m_point = t_point;
    m_takeoff_flight = nullptr;
    m_return_flight = nullptr;
    m_cost = -1;
    m_next = nullptr;
    m_prev = nullptr;
}


// PUBLIC INITIALIZER //
CarStop* CarStop::create(Route* t_route, Point* t_point){
    return new CarStop(t_route, t_point);
}


// GETTERS//
double CarStop::getCost(){
    return m_cost;
}
Point* CarStop::getPoint(){
    return m_point;
}
bool CarStop::is_takeoff(){
    return m_takeoff_flight != nullptr;
}
bool CarStop::is_return(){
    return m_return_flight != nullptr;
}
bool CarStop::is_first(){
    return m_prev == nullptr;
}
bool CarStop::is_last(){
    return m_next == nullptr;
}
Flight* CarStop::getTakeoffFlight(){
    return m_takeoff_flight;
}
Flight* CarStop::getReturnFlight(){
    return m_return_flight;
}


// SETTERS //
void CarStop::setCost(double t_cost){
    m_cost = t_cost;
}
void CarStop::setTakeoffFlight(Flight* t_flight){
    m_takeoff_flight = t_flight;
}
void CarStop::setReturnFlight(Flight* t_flight){
    m_return_flight = t_flight;
}

void CarStop::removeTakeoff(){
    m_takeoff_flight = nullptr;
}
void CarStop::removeReturn(){
    m_return_flight = nullptr;
}


// OPERATIONS //
void CarStop::eraseUpBottom(){
    if (m_next != nullptr)
        m_next->m_prev = m_prev;
    if (m_prev != nullptr)
        m_prev->m_next = m_next;
    if(m_point != nullptr)
        m_point->erase();
    if(m_takeoff_flight != nullptr)
        m_takeoff_flight->eraseUpBottom();
    if(m_return_flight != nullptr)
        m_return_flight->eraseUpBottom();

    delete this;
}


// PRINTING //
string CarStop::toString(){
    std::stringstream cost;
    cost << std::fixed << std::setprecision(2) << m_cost;
    string str = "Point: " + m_point->toString() + " - Total cost: " + cost.str();
    return str;
}

#endif