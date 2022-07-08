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
    return (getRemainingStorage() >= t_required_storage && getRemainingRange() >= t_required_distance);
}
void Car::deliver(Point* t_point){
    Point* last_position = getActualPosition();

    if(last_position != nullptr){
        if (t_point->is_client()){
            double remaining_storage = getRemainingStorage() - t_point->getPackage();
            double remaining_range = getRemainingRange() - Point::distanceBetweenPoints(*t_point, *t_point);
            setRemainingStorage(remaining_storage);
            setRemainingRange(remaining_range);
        }
        else if (t_point->is_deposit()){
            resetAttributes();
        }
    }

    setActualPosition(t_point);
}
bool Car::canSupport(double t_used_storage){
    return t_used_storage <= getRemainingStorage();
}

#endif
