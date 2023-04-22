#ifndef CAR_CPP
#define CAR_CPP

#include "car.hpp"
#include "../point.hpp"
#include "../route.hpp"

// CONSTRUCTORS //
// "Clean" constructor
Car::Car(){
    setSpeed(DEFAULT_CAR_SPEED);
    setName("");
    setActualPosition(nullptr);
    m_route = nullptr;
    m_route = nullptr;
}
Car::Car(string t_name, Point t_position){
    setSpeed(DEFAULT_CAR_SPEED);
    setName(t_name);
    setActualPosition(new Point(t_position));
    m_route = new Route(this);
    m_route->appendPoint(getActualPosition());
}


// GETTERS //
vector<Drone*> Car::getDrones(){
    return m_drone;
}
Route* Car::getRoute(){
    return m_route;
}

// SETTERS //
void Car::addDrone(Drone* t_drone){
    m_drone.push_back(t_drone);
}


// OPERATIONS //
bool Car::canDeliver(double t_required_distance, double t_required_storage){
    return true;
}
void Car::deliver(Point* t_point){
    setActualPosition(t_point);
}
bool Car::canSupport(double t_used_storage){
    return true;
}
void Car::support(double t_used_storage){
}

#endif
