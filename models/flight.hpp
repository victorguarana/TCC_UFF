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
    DroneStop* m_first_stop;
    DroneStop* m_last_stop;
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

    // GETTERS //
    DroneStop* getFirstStop();

    // SETTER //
    void setTakeoffStop(CarStop*);
    void setReturnStop(CarStop*);
    void appendDroneStop(DroneStop*);

    // OPERATION //
    void setCosts();

    // PRINTING //
    void print(int);
};

#endif