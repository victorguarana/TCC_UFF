#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <iostream>
#include <vector>

class Car;
class Drone;
class Point;
class CarStop;
class DroneStop;
class Flight;

using namespace std;

class Route {
    private:
    // DATA //
    Car* m_car;
    CarStop* m_first_stop;
    CarStop* m_last_stop;
    double m_total_cost;
    struct ActiveFlights{
        Flight* flight;
        double ground_delay_time;
    };


    private:
    // OTHER FUNCTIONS //
    double calcFlightDelay(Flight*, double);

    public:
    // INITIALIZER //
    Route(Car*);

    // GETTER //
    CarStop* getFirstStop();
    CarStop* getLastStop();
    Car* getCar();
    double getTotalCost();

    // SETTER //
    void setTotalCost(double);

    // LINKED LIST FUNCTIONS //
    void appendCarStopFront(CarStop*);
    void appendCarStopBack(CarStop*);
    void insertCarStop(CarStop*, CarStop*);
    void removeCarStop(CarStop*);


    // OTHER FUNCTIONS //
    void calcCosts();
    void appendPoint(Point*);
    bool isValid();
    Route* duplicate();

    void completeErase();

    // PRINTING //
    void print();
};

#endif