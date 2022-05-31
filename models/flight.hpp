#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include<iostream>

class CarStop;
class DroneStop;
class Drone;

using namespace std;

class Flight {
    private:
    // POINTERS TO MAIN ROUTE //
    CarStop* m_begin;
    CarStop* m_end;

    // DATA //
    DroneStop* m_first_point;
    Drone* m_drone;

    public:
    int size;

    Flight(CarStop*, Drone*);

    // SETTER //
    void setFirstStop(DroneStop*);

    void addStop(DroneStop*);

    // PRINTING //
    void print(int);
};

#endif