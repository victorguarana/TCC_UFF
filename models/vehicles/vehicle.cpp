#ifndef VEHICLE_CPP
#define VEHICLE_CPP

#include <string>

#include "vehicle.hpp"

using namespace std;

void Vehicle::setTotalStorage(double t_total_storage){
    m_total_storage = t_total_storage;
}
void Vehicle::setTotalRange(double t_total_range){
    m_total_range = t_total_range;
}
void Vehicle::setSpeed(double t_speed){
    m_speed = t_speed;
}
void Vehicle::setRemainingStorage(double t_remaining_storage){
    m_remaining_storage = t_remaining_storage;
}
void Vehicle::setRemainingRange(double t_remaining_range){
    m_remaining_range = t_remaining_range;
}
void Vehicle::setName(string t_name){
    m_name = t_name;
}
void Vehicle::setActualPosition(Point* t_position){
    m_actual_position = t_position;
}

/* Getters */
double Vehicle::getRemainingStorage(){
    return m_remaining_storage;
}
double Vehicle::getRemainingRange(){
    return m_remaining_range;
}
double Vehicle::getSpeed(){
    return m_speed;
}
string Vehicle::getName(){
    return m_name;
}
Point* Vehicle::getActualPosition(){
    return m_actual_position;
}
void Vehicle::resetAttributes(){
    m_remaining_storage = m_total_storage;
    m_remaining_range = m_total_range;
}

// Operations //
bool Vehicle::canDeliver(double t_distance, double t_package){
    return (t_package <= m_remaining_storage && t_distance <= m_remaining_range);
}

#endif
