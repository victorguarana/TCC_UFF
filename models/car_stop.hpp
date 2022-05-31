#ifndef CARSTOP_HPP
#define CARSTOP_HPP

#include <string>

using namespace std;

class Point;
class Flight;
class Point;
class Route;

class CarStop {
    private:
    // DATA //
    Point m_point;
    Flight* m_takeoff_flight;
    Flight* m_return_flight;
    double m_cost;

    Route* m_this_route;

    public:
    // LINKED LIST //
    CarStop* m_next;
    CarStop* m_prev;

    // INITIALIZER //
    CarStop(Route*, Point);

    // GETTERS//
    Point getPoint();
    bool is_takeoff();
    bool is_return();
    bool is_first();
    bool is_last();
    Flight* getTakeoffFlight();
    Flight* getReturnFlight();

    // SETTERS //
    void setTakeoffFlight(Flight*);
    void setReturnFlight(Flight*);
    void removeTakeoff();
    void removeReturn();

    // PRINTING //
    string toString();
};

#endif