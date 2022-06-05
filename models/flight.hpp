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
    CarStop* m_takeoff;
    CarStop* m_landing;
    double m_total_cost;

    // PRIVATE INITIALIZER //
    Flight(CarStop*, Drone*);


    public:
    // PUBLIC INITIALIZER //
    static Flight* create(CarStop*, Drone*);


    // GETTERS //
    DroneStop* getFirstStop();
    double getTotalCost();
    CarStop* getTakeoffStop();
    CarStop* getLandingStop();


    // SETTER //
    void setTakeoffStop(CarStop*);
    void setLandingStop(CarStop*);
    void appendDroneStop(DroneStop*);
    void setTotalCost(double);


    // OPERATIONS //
    void calcCosts();
    void eraseUpBottom();
    void eraseBottomUp();
    void attachFlight(Flight*);

    // PRINTING //
    void print(int);
};

#endif