#ifndef ROUTE_CPP
#define ROUTE_CPP

#include <iostream>
#include <vector>

#include "route.hpp"

#include "vehicles/car.cpp"
#include "point.cpp"
#include "car_stop.cpp"
#include "drone_stop.cpp"
#include "flight.cpp"

using namespace std;


void Route::setFirstStop(CarStop* m_stop){
    if (size > 0){
        m_first_stop->m_prev = m_stop;
        m_stop->m_next = m_first_stop;
    }
    else{
        m_last_stop = m_stop;
    }
    m_first_stop = m_stop;
}
void Route::setLastStop(CarStop* m_stop){
    CarStop* actual_car_stop = m_first_stop;
    while(actual_car_stop->m_next != nullptr){
        actual_car_stop = actual_car_stop->m_next;
    }
    actual_car_stop->m_next = m_stop;
    m_stop->m_prev = actual_car_stop;
}

// INITIALIZER //
Route::Route(Car* t_car){
    m_car = t_car;
    m_first_stop = nullptr;
    m_last_stop = nullptr;
    size = 0;
}

// GETTER //
CarStop* Route::getFirstStop(){
    return m_first_stop;
}
CarStop* Route::getLastStop(){
    return m_last_stop;
}
Car* Route::getCar(){
    return m_car;
}

// SETTER //
void Route::addPoint(Point t_point){
    m_car_stops.push_back(CarStop(this, t_point));
    CarStop* p_car_stop = &m_car_stops.at(size);
    if (size == 0){
        setFirstStop(p_car_stop);
    }
    else{
        setLastStop(p_car_stop);
    }
    size++;
}

// OPERATIONS //
void Route::removeCarStop(CarStop* t_car_stop){
    CarStop* next_car_stop = t_car_stop->m_next;
    CarStop* prev_car_stop = t_car_stop->m_prev;
    next_car_stop->m_prev = prev_car_stop;
    prev_car_stop->m_next = next_car_stop;
    size--;
}

// DATABASE OPERATIONS //
DroneStop* Route::createDroneStop(Flight* t_flight, Point t_point){
    m_drone_stops.push_back(DroneStop(t_flight, t_point));
    int last_index = m_drone_stops.size()-1;
    DroneStop* p_actual_drone_stop = &m_drone_stops.at(last_index);
    return p_actual_drone_stop;
}

Flight* Route::createFlight(CarStop* t_car_stop, Drone* t_p_drone){
    m_flights.push_back(Flight(t_car_stop, t_p_drone));
    int last_index = m_flights.size()-1;
    Flight* p_actual_flight = &m_flights.at(last_index);

    return p_actual_flight;
}

// PRINTING //
void Route::print(){
    if (size < 1)
        return;

    int index = 1;
    CarStop* actual_stop = m_first_stop;
    while (actual_stop != nullptr){
        cout << "STOP #" << to_string(index) << " -> " << actual_stop->toString() << endl;

        if (actual_stop->is_takeoff()){
            actual_stop->getTakeoffFlight()->print(index);
        }
        actual_stop = actual_stop->m_next;
        index++;
    }
}

#endif