#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include<iostream>

class CarStop;
class DroneStop;
class Drone;

using namespace std;

class Flight {
    private:
    // DATA //
    DroneStop* m_first_point;
    Drone* m_drone;
    // Pointers to main route
    CarStop* m_begin;
    CarStop* m_end;

    // PUBLIC INITIALIZER //
    Flight(CarStop*, Drone*);

    public:
    int size;

    // PRIVATE INITIALIZER //
    static Flight* create(CarStop*, Drone*);

    // SETTER //
    void setFirstStop(DroneStop*);
    void addStop(DroneStop*);

    // PRINTING //
    void print(int);
};

#endif