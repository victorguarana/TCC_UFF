#ifndef ROUTE_CPP
#define ROUTE_CPP

#include <vector>

#include "vehicles/car.cpp"
#include "car_stop.cpp"

// TODO: fix vehicles models
// After this, adapt greedy to use this structure
// After this, implement ils 
class Route {
    private:
    Car* m_car;
    CarStop* m_first_stop;

    public:
    int size;

    // INITIALIZER //
    Route(Car* t_car){
        m_car = t_car;
        m_first_stop = nullptr;
        size = 0;
    }

    // SETTER //
    void setFirstStop(CarStop* m_stop){
        m_first_stop = m_stop;
        size++;
    }
};

#endif