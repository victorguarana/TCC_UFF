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
double Route::getTotalCost(){
    return m_total_cost;
}


// SETTER //
void Route::setTotalCost(double t_total_cost){
    m_total_cost = t_total_cost;
}

// OPERATIONS //
void Route::appendCarStop(CarStop* t_p_car_stop){
    if (size == 0){
        m_first_stop = t_p_car_stop;
    }
    else{
        CarStop* p_last_stop = m_last_stop;
        p_last_stop->m_next = t_p_car_stop;
        t_p_car_stop->m_prev = p_last_stop;
    }
    m_last_stop = t_p_car_stop;
    size++;
}
void Route::removeCarStop(CarStop* t_car_stop){
    t_car_stop->eraseUpBottom();
    size--;
}
void Route::calcCosts(){
    m_total_cost = 0;
    double car_speed = m_car->getSpeed();

    CarStop* last_stop = m_first_stop;
    CarStop* actual_stop = last_stop->m_next;
    CarStop* next_stop = actual_stop->m_next;
    double distance_backward, distance_forward;

    while (actual_stop->m_next != nullptr){
        distance_backward = Point::distanceBetweenPoints(*last_stop->getPoint(), *actual_stop->getPoint());
        distance_forward = Point::distanceBetweenPoints(*actual_stop->getPoint(), *next_stop->getPoint());

        actual_stop->setCost(distance_backward + distance_forward);
        m_total_cost += distance_backward / car_speed;

        if (actual_stop->is_takeoff()){
            Flight* p_actual_flight = actual_stop->getTakeoffFlight();
            p_actual_flight->calcCosts();
            m_total_cost += p_actual_flight->getTotalCost();
        }

        last_stop = actual_stop;
        actual_stop = last_stop->m_next;
        next_stop = actual_stop->m_next;
    }
    m_total_cost += distance_forward / car_speed;
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

    std::stringstream total_cost;
    total_cost << std::fixed << std::setprecision(2) << m_total_cost;
    cout << "Route Total Cost: " << total_cost.str() << endl;
}

#endif