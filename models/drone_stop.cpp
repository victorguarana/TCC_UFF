#ifndef DRONESTOP_CPP
#define DRONESTOP_CPP

#include "point.cpp"
#include "vehicles/drone.cpp"
// #include "flight.cpp"


class DroneStop {
    private:
    // DATA //
    Point* m_point;
    double m_cost;

    // Flight that this stop belongs
    // Flight* m_this_flight;

    public:
    // LINKED LIST //
    DroneStop* m_next;
    DroneStop* m_prev;

    // INITIALIZER //
    // DroneStop(Flight* t_flight, Point* t_point){
    //     m_point = t_point;
    //     m_cost = -1;
    //     m_this_flight = t_flight;
    //     m_next = nullptr;
    //     m_prev = nullptr;
    // }
    DroneStop(Point* t_point){
        m_point = t_point;
        m_cost = -1;
        m_next = nullptr;
        m_prev = nullptr;
    }

    // GETTERS//
    bool is_first(){
        return m_prev == nullptr;
    }
    bool is_last(){
        return m_next == nullptr;
    }

    // OPERATIONS//
    // void erase(){
    //     if (is_first() && is_last()){
    //         m_this_flight->erase();
    //         delete this;
    //     }
    //     else {
    //         if (is_last()){
    //             m_prev->m_next=nullptr;
    //         }
    //         else if (is_first()){
    //             m_this_flight->setFirstStop(m_next);
    //         }
    //         else {
    //             m_prev->m_next=m_next;
    //             m_next->m_prev=m_prev;
    //         }
    //         m_this_flight->size--;
    //         delete this;
    //     }
    // }

};

#endif