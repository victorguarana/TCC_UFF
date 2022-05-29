#ifndef FLIGHT_CPP
#define FLIGHT_CPP


#include "car_stop.cpp"
#include "drone_stop.cpp"
#include "vehicles/drone.cpp"
// #include "point.cpp"

class Flight {
    private:
    // POINTERS TO MAIN ROUTE //
    CarStop* m_begin;
    CarStop* m_end;

    // DATA
    DroneStop* m_first_point;
    Drone* m_drone;

    public:
    int size;

    // INITIALIZER //
    Flight(CarStop* t_begin, Drone* t_drone){
        m_begin = t_begin;
        m_end = nullptr;
        m_first_point = nullptr;
        m_drone = t_drone;
        size = 0;

    }

    // GETTERS //
    // Point* getInitialPoint(){
    //     return m_begin->getPoint();
    // }
    // Point* getFinalPoint(){
    //     return m_end->getPoint();
    // }

    // SETTER //
    void setFirstStop(DroneStop* m_stop){
        m_first_point = m_stop;
    }

    // OPERATIONS //
    void erase(){
        m_begin->removeTakeoff();
        m_end->removeReturn();
        delete this;
    }

};

#endif