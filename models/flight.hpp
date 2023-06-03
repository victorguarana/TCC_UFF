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
    Drone* getDrone();


    // SETTERS //
    void setTakeoffStop(CarStop*);
    void setLandingStop(CarStop*);
    void setTotalCost(double);


    // LINKED LIST FUNCTIONS //
    void appendDroneStopFirst(DroneStop*);
    void appendDroneStopLast(DroneStop*);
    void insertDroneStop(DroneStop*, DroneStop*);
    void removeDroneStop(DroneStop*);


    // OTHER FUNCTIONS //
    void calcCosts();
    bool isEmpty();
    void removeFromRoute();
    void erase();
    void attachFlight(Flight*);
    // Spit the flight in one or more valid flights
    void splitToValidFlights();
    bool isValid();

    Flight* duplicate(CarStop*, CarStop*);

    // PRINTING //
    void print(int);
    string toStringFile();
};

#endif