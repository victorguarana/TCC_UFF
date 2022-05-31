#ifndef DRONESTOP_CPP
#define DRONESTOP_CPP

#include "drone_stop.hpp"

#include "point.cpp"
//#include "vehicles/drone.cpp"
//#include "flight.cpp"

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

// OPERATIONS//
// void erase(){
//     if (is_first() && is_last()){
//         m_this_flight->erase();
//         delete this;
//     }
//     else {
//         if (is_last()){
//             m_prev->m_next=nullptr;
//         }
//         else if (is_first()){
//             m_this_flight->setFirstStop(m_next);
//         }
//         else {
//             m_prev->m_next=m_next;
//             m_next->m_prev=m_prev;
//         }
//         m_this_flight->size--;
//         delete this;
//     }
// }

// PRINTING //
string DroneStop::toString(){
    string str = "Point: " + m_point.toString() + " - Total cost: ...";
    return str;
}

#endif