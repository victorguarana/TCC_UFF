#ifndef ROUTE_CPP
#define ROUTE_CPP

#include "vehicles/car.cpp"
#include "car_stop.cpp"

// TODO: fix vehicles models
// After this, adapt greedy to use this structure
// After this, implement ils 
class Route {
    private:
    Car* m_car;
    CarStop* m_first_stop;
    CarStop* m_last_stop;

    public:
    int size;

    // INITIALIZER //
    Route(Car* t_car){
        m_car = t_car;
        m_first_stop = nullptr;
        m_last_stop = nullptr;
        size = 0;
    }

    // SETTER //
    void setFirstStop(CarStop* m_stop){
        m_first_stop = m_stop;
        size++;
    }
    void setLastStop(CarStop* m_stop){
        m_last_stop->m_next = m_stop;
        m_stop->m_prev = m_last_stop;
        m_last_stop = m_stop;
        size++;
    }
    void addPoint(Point* t_point){
        CarStop stop(this, t_point);
        if (size > 0){
            setLastStop(&stop);
        }
        else{
            setFirstStop(&stop);
        }

    }
};

#endif