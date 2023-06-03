#ifndef POSITION_CPP
#define POSITION_CPP

#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <list>

#include "point.hpp"
#include "car_stop.hpp"
#include "drone_stop.hpp"

using namespace std;

Point::Point(){
    m_latitude = 0;
    m_longitude = 0;
    m_name = "";
}


Point::Point(string t_name, double t_latitude, double t_longitude, double t_package){
    m_name = t_name;
    m_latitude = t_latitude;
    m_longitude = t_longitude;
    m_package = t_package;
    m_type = Client;
}

// Initializer for deposit (Used in map and main)
Point::Point(string t_name, double t_latitude, double t_longitude){
    m_name = t_name;
    m_latitude = t_latitude;
    m_longitude = t_longitude;
    m_package = -1;
    m_type = Deposit;
}

// Initializer with memory allocation and returning pointer
Point* Point::create(Point t_point){
    return new Point(t_point);
}


// GETTERS //
bool Point::isDeposit(){
    return m_type == Deposit;
}
bool Point::isClient(){
    return m_type == Client;
}

double Point::getPackage(){
    return m_package;
}

string Point::getName(){
    return m_name;
}

Point* Point::getFirstNearestNeigbor(){
    return m_nearest_points[0];
}
Point* Point::getSecondNearestNeigbor(){
    return m_nearest_points[1];
}
CarStop* Point::getCarStop(){
    return m_car_stop;
}
DroneStop* Point::getDroneStop(){
    return m_drone_stop;
}


// SETTERS //
void Point::setFirstNearestNeigbor(Point *neighbor){
    m_nearest_points[0] = neighbor;
}
void Point::setSecondNearestNeigbor(Point *neighbor){
    m_nearest_points[1] = neighbor;
}
void Point::setCarStop(CarStop* t_car_stop){
    m_car_stop = t_car_stop;
}
void Point::setDroneStop(DroneStop* t_drone_stop){
    m_drone_stop = t_drone_stop;
}


// STRINGFY //
string Point::toString(){
    std::stringstream latitude, longitude, package;
    latitude << std::fixed << std::setprecision(2) << m_latitude;
    longitude << std::fixed << std::setprecision(2) << m_longitude;
    package << std::fixed << std::setprecision(2) << m_package;

    string str = m_name + " (Pos: " + latitude.str() +  " : " + longitude.str() + ")";
    if (isClient())
        str += " Pacote: " + package.str();

    return str;
}
string Point::toStringFile(){
    std::stringstream latitude, longitude;
    latitude << std::fixed << std::setprecision(2) << m_latitude;
    longitude << std::fixed << std::setprecision(2) << m_longitude;

    string str = m_name + ";" + latitude.str() +  ";" + longitude.str();

    return str;
}

// OPERATIONS //
bool Point::equal(Point t_point){
    if (m_latitude == t_point.m_latitude && m_longitude == t_point.m_longitude && m_name == t_point.m_name && m_package == t_point.m_package && m_type  == t_point.m_type)
        return true;
    return false;
}
void Point::erase(){
    delete this;
}
double Point::distanceBetweenPoints(Point t_p1, Point t_p2){
    return sqrt( ((t_p1.m_latitude - t_p2.m_latitude)*(t_p1.m_latitude - t_p2.m_latitude)) + ((t_p1.m_longitude - t_p2.m_longitude)*(t_p1.m_longitude - t_p2.m_longitude)) * 1.0);
}

#endif
