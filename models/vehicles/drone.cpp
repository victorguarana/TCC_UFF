#ifndef DRONE_CPP
#define DRONE_CPP

#include "drone.hpp"

Drone::Drone(){
    setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
    setRemainingRange(DEFAULT_DRONE_TOTAL_RANGE);
    setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
    setRemainingStorage(DEFAULT_DRONE_TOTAL_STORAGE);
    setSpeed(DEFAULT_DRONE_SPEED);
    setName("");
    m_flying = false;
}

Drone::Drone(string t_name){
    setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
    setRemainingRange(DEFAULT_DRONE_TOTAL_RANGE);
    setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
    setRemainingStorage(DEFAULT_DRONE_TOTAL_STORAGE);
    setSpeed(DEFAULT_DRONE_SPEED);
    setName(t_name);
    m_flying = false;
}

bool Drone::isFlying(){
    return m_flying;
}
void Drone::takeOff(Point* t_point){
    m_flying = true;
    setActualPosition(t_point);
}
void Drone::land(){
    m_flying = false;
    resetAttributes();
}

void Drone::deliver(Point* t_point){
    Point* last_position = getActualPosition();

    if(last_position != nullptr){
        double remaining_storage = getRemainingStorage() - t_point->getPackage();
        double remaining_range = getRemainingRange() - Point::distanceBetweenPoints(*t_point, *t_point);
        setRemainingStorage(remaining_storage);
        setRemainingRange(remaining_range);
    }
    setActualPosition(t_point);
}

double Drone::defaultStorage(){
    return DEFAULT_DRONE_TOTAL_STORAGE;
}

#endif
