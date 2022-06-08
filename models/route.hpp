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
    void removeCarStop(CarStop*, bool=false);


    // OTHER FUNCTIONS //
    void calcCosts();

    // PRINTING //
    void print();
};

#endif