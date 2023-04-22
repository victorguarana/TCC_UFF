#ifndef CARSTOP_HPP
#define CARSTOP_HPP

#include <string>
#include <vector>

using namespace std;

class Point;
class Flight;
class Point;
class Route;

class CarStop {
    private:
    // DATA //
    Point* m_point;
    vector<Flight*> m_takeoff_flights;
    vector<Flight*> m_return_flights;
    double m_cost;
    Route* m_this_route;

    // PRIVATE INITIALIZER //
    CarStop(Route*, Point*);


    public:
    // LINKED LIST //
    CarStop* m_next;
    CarStop* m_prev;


    // PUBLIC INITIALIZER //
    static CarStop* create(Route*, Point*);


    // GETTERS//
    Point* getPoint();
    Route* getRoute();
    double getCost();
    bool isTakeoff();
    bool isReturn();
    bool isFirst();
    bool isLast();
    vector<Flight*> getTakeoffFlights();
    vector<Flight*> getReturnFlights();


    // SETTERS //
    void setCost(double);
    void addTakeoffFlight(Flight*);
    void addReturnFlight(Flight*);
    void removeTakeoff(Flight*);
    void removeReturn(Flight*);


    // OPERATIONS //
    void removeFromRoute();
    void erase();


    // PRINTING //
    string toString();
};

#endif