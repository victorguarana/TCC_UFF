#ifndef DRONESTOP_CPP
#define DRONESTOP_CPP

#include "drone_stop.hpp"

#include "flight.hpp"
#include "point.hpp"
#include "car_stop.hpp"

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
bool DroneStop::isFirst(){
    return m_prev == nullptr;
}
bool DroneStop::isLast(){
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
    if (m_this_flight->isEmpty()){
        m_this_flight->removeFromRoute();
        m_this_flight->erase();
    }
}
void DroneStop::erase(){
    delete this;
}

DroneStop* DroneStop::duplicate(Flight* t_flight){
    DroneStop* new_dronestop = new DroneStop(t_flight, m_point);
    new_dronestop->m_cost = m_cost;

    if(m_next != nullptr){
        new_dronestop->m_next = m_next->duplicate(t_flight);
        new_dronestop->m_next->m_prev = new_dronestop;
    }
    return new_dronestop;
}


// PRINTING //
string DroneStop::toString(){
    std::stringstream cost;
    cost << std::fixed << std::setprecision(2) << m_cost;
    string str = "Point: " + m_point->toString() + " - Stop cost: " + cost.str();
    return str;
}

string DroneStop::toStringFile(){
    std::stringstream str;
    str << "D;" + m_point->toStringFile() + ';';
    if (this->m_next != nullptr){
        str << m_next->m_point->toStringFile() + '\n';
    }
    else{
        str << m_this_flight->getLandingStop()->getPoint()->toStringFile() + '\n';
    }
    return str.str();
}

#endif