#ifndef CARSTOP_CPP
#define CARSTOP_CPP

#include "car_stop.hpp"

#include "route.hpp"
#include "point.hpp"
#include "flight.hpp"

// Future: When implementing multiple drones, use vectors to represent flights and return and takeoff (?)
// PRIVATE INITIALIZER //
CarStop::CarStop(Route* t_route, Point* t_point){
    m_this_route = t_route;
    m_point = t_point;
    m_cost = 0;
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
Route* CarStop::getRoute(){
    return m_this_route;
}
bool CarStop::is_takeoff(){
    return !m_takeoff_flights.empty();
}
bool CarStop::is_return(){
    return !m_return_flights.empty();
}
bool CarStop::is_first(){
    return m_prev == nullptr;
}
bool CarStop::is_last(){
    return m_next == nullptr;
}
vector<Flight*> CarStop::getTakeoffFlights(){
    return m_takeoff_flights;
}
vector<Flight*> CarStop::getReturnFlights(){
    return m_return_flights;
}


// SETTERS //
void CarStop::setCost(double t_cost){
    m_cost = t_cost;
}
void CarStop::addTakeoffFlight(Flight* t_flight){
    m_takeoff_flights.push_back(t_flight);
}
void CarStop::addReturnFlight(Flight* t_flight){
    m_return_flights.push_back(t_flight);
}

void CarStop::removeTakeoff(Flight* t_flight){
    for(int i = 0; i < m_takeoff_flights.size(); i++){
        if (t_flight == m_takeoff_flights.at(i)){
            m_takeoff_flights.erase(m_takeoff_flights.begin() + i);
            return;
        }
    }
}
void CarStop::removeReturn(Flight* t_flight){
        for(int i = 0; i < m_return_flights.size(); i++){
        if (t_flight == m_return_flights.at(i)){
            m_return_flights.erase(m_return_flights.begin() + i);
            return;
        }
    }
}


// OPERATIONS //
void CarStop::removeFromRoute(){

// DOUBT: Será que não posso assumir que não é possivel remover carstops que tem flight landind ou taking off?

    // When a drone return and takeoff at this stop
    for(int i = 0; i < m_return_flights.size(); i++){
        Flight* p_flight = m_return_flights.at(i);

        for(int j = 0; j < m_takeoff_flights.size(); j++){
            if (p_flight->getDrone() == m_takeoff_flights.at(j)->getDrone()){
                p_flight->attachFlight(m_takeoff_flights.at(j));

                if (!p_flight->isValid())
                    p_flight->splitToValidFlights();

                m_takeoff_flights.erase(m_takeoff_flights.begin() + j);
                m_return_flights.erase(m_return_flights.begin() + i);
                i--; 
            }
        }
    }

    // TODO: This changes can invalidate the route?
    for(int i = 0; i < m_return_flights.size(); i++){
        Flight* p_flight = m_return_flights.at(i);
        if(m_next != nullptr)
            p_flight->setLandingStop(m_next);
        else 
            p_flight->setLandingStop(m_prev);
    }

    for(int i = 0; i < m_takeoff_flights.size(); i++){
        Flight* p_flight = m_takeoff_flights.at(i);
        if(m_prev != nullptr)
            p_flight->setTakeoffStop(m_prev);
        else 
            p_flight->setTakeoffStop(m_next);
    }

    m_this_route->removeCarStop(this);
}
void CarStop::erase(){
    delete this;
}


// PRINTING //
string CarStop::toString(){
    std::stringstream cost;
    cost << std::fixed << std::setprecision(2) << m_cost;
    string str = "Point: " + m_point->toString() + " - Stop cost: " + cost.str();
    return str;
}

#endif