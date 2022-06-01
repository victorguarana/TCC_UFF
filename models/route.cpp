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

// SETTER //
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

// OPERATIONS //
void Route::removeCarStop(CarStop* t_car_stop){
    CarStop* next_car_stop = t_car_stop->m_next;
    CarStop* prev_car_stop = t_car_stop->m_prev;
    next_car_stop->m_prev = prev_car_stop;
    prev_car_stop->m_next = next_car_stop;
    size--;
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