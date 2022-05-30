#ifndef ROUTE_CPP
#define ROUTE_CPP

#include <iostream>
#include <vector>

#include "vehicles/car.cpp"
#include "car_stop.cpp"

using namespace std;

class Route {
    private:
    Car* m_car;
    CarStop* m_first_stop;
    CarStop* m_last_stop;

    // Just to store the stops without losing to garbage
    vector<CarStop> m_car_stops;

    void setFirstStop(CarStop* m_stop){
        if (size > 0){
            m_first_stop->m_prev = m_stop;
            m_stop->m_next = m_first_stop;
        }
        else{
            m_last_stop = m_stop;
        }
        m_first_stop = m_stop;
    }
    void setLastStop(CarStop* m_stop){
        CarStop* actual_car_stop = m_first_stop;
        while(actual_car_stop->m_next != nullptr){
            actual_car_stop = actual_car_stop->m_next;
        }
        actual_car_stop->m_next = m_stop;
        m_stop->m_prev = actual_car_stop;
    }
    public:
    int size;

    // INITIALIZER //
    Route(Car* t_car){
        m_car = t_car;
        m_first_stop = nullptr;
        m_last_stop = nullptr;
        size = 0;
    }

    // GETTER //
    CarStop* getFirstStop(){
        return m_first_stop;
    }
    CarStop* getLastStop(){
        return m_last_stop;
    }

    // SETTER //
    void addPoint(Point t_point){
        m_car_stops.push_back(CarStop(t_point));
        CarStop* p_car_stop = &m_car_stops.at(size);
        // CarStop* p_stop = &stop;
        if (size == 0){
            setFirstStop(p_car_stop);
        }
        else{
            setLastStop(p_car_stop);
        }
        size++;
    }

    // PRINTING //
    void print(){
        if (size < 1)
            return;

        int index = 1;
        CarStop* actual_stop = m_first_stop;
        while (actual_stop != nullptr){
            cout << "STOP #" << to_string(index) << " -> " << actual_stop->toString() << endl;
            actual_stop = actual_stop->m_next;
            index++;
        }
    }
};

#endif