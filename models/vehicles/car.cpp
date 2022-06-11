#ifndef CAR_CPP
#define CAR_CPP

#include "car.hpp"
#include "../route.cpp"

// CONSTRUCTORS //
// "Clean" constructor
Car::Car(){
    setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
    setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
    setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
    setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
    setSpeed(DEFAULT_CAR_SPEED);
    setName("");
    setActualPosition(nullptr);
    m_route = nullptr;
    m_route = nullptr;
}
Car::Car(string t_name, Point t_position){
    setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
    setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
    setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
    setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
    setSpeed(DEFAULT_CAR_SPEED);
    setName(t_name);
    setActualPosition(new Point(t_position));
    m_drone = nullptr;
    m_route = new Route(this);
    m_route->appendPoint(getActualPosition());
}


// GETTERS //
Drone* Car::getDrone(){
    return m_drone;
}
Route* Car::getRoute(){
    return m_route;
}

// SETTERS //
void Car::setDrone(Drone* t_drone){
    m_drone = t_drone;
}


#endif
