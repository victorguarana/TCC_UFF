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
    Car* m_car;
    CarStop* m_first_stop;
    CarStop* m_last_stop;

    // "DATABASE" //
    vector<Point> m_points;
    vector<CarStop> m_car_stops;
    vector<DroneStop> m_drone_stops;
    vector<Flight> m_flights;

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

    // DATABASE OPERATIONS //
    Point* createPoint(Point);
    CarStop* createCarStop(Point*);
    DroneStop* createDroneStop(Flight*, Point*);
    Flight* createFlight(CarStop*, Drone*);

    // PRINTING //
    void print();
};

#endif