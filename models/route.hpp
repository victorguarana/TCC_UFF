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

    public:
    int size;

    // INITIALIZER //
    Route(Car*);

    // GETTER //
    CarStop* getFirstStop();
    CarStop* getLastStop();
    Car* getCar();

    // SETTER //
    void addPoint(Point);

    // OPERATIONS //
    void removeCarStop(CarStop*);

    // PRINTING //
    void print();
};

#endif