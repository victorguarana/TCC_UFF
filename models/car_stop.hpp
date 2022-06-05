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
    Point* m_point;
    Flight* m_takeoff_flight;
    Flight* m_return_flight;
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
    double getCost();
    bool is_takeoff();
    bool is_return();
    bool is_first();
    bool is_last();
    Flight* getTakeoffFlight();
    Flight* getReturnFlight();


    // SETTERS //
    void calcCosts(double);
    void setTakeoffFlight(Flight*);
    void setReturnFlight(Flight*);
    void removeTakeoff();
    void removeReturn();


    // OPERATIONS //
    void eraseUpBottom();
    void eraseBottomUp();


    // PRINTING //
    string toString();
};

#endif