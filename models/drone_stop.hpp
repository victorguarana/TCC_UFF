#ifndef DRONESTOP_HPP
#define DRONESTOP_HPP

#include<string>

using namespace std;

class Point;
class Flight;

class DroneStop {
    private:
    // DATA //
    Point* m_point;
    double m_cost;
    // Flight that this stop belongs
    Flight* m_this_flight;

    // PRIVATE INITIALIZER //
    DroneStop(Flight*, Point*);

    public:
    // LINKED LIST //
    DroneStop* m_next;
    DroneStop* m_prev;

    // PUBLIC INITIALIZER //
    static DroneStop* create(Flight*, Point*);

    // GETTERS//
    bool is_first();
    bool is_last();

    // PRINTING //
    string toString();

};

#endif