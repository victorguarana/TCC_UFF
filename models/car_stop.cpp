#ifndef CARSTOP_CPP
#define CARSTOP_CPP

#include <string>

#include "point.cpp"
#include "flight.cpp"
// #include "route.cpp"

using namespace std;

// Future: When implementing multiple drones, use vectors to represent flights and return and takeoff (?)
class CarStop {
    private:
    // DATA //
    Point m_point;
    Flight* m_takeoff_flight;
    Flight* m_return_flight;
    double m_cost;

    // Route that this stop belongs
    // Route* m_this_route;

    public:
    // LINKED LIST //
    CarStop* m_next;
    CarStop* m_prev;

    // INITIALIZER //
    CarStop(){
        // m_point = t_point;
        m_takeoff_flight = nullptr;
        m_return_flight = nullptr;
        m_cost = -1;
        // m_this_route = t_route;
        m_next = nullptr;
        m_prev = nullptr;
    }
    CarStop(Point t_point){
        m_point = t_point;
        m_takeoff_flight = nullptr;
        m_return_flight = nullptr;
        m_cost = -1;
        m_next = nullptr;
        m_prev = nullptr;
    }

    // GETTERS//
    Point getPoint(){
        return m_point;
    }
    bool is_takeoff(){
        return m_takeoff_flight != nullptr;
    }
    bool is_return(){
        return m_return_flight != nullptr;
    }
    bool is_first(){
        return m_prev == nullptr;
    }
    bool is_last(){
        return m_next == nullptr;
    }

    // OPERATIONS //
    // void erase(){
    //     if (is_first() && is_last()){
    //         delete m_this_route;
    //         delete this;
    //     }
    //     else {
    //         if (is_last()){
    //             m_prev->m_next=nullptr;
    //         }
    //         else if (is_first()){
    //             m_this_route->setFirstStop(m_next);
    //         }
    //         else {
    //             m_prev->m_next=m_next;
    //             m_next->m_prev=m_prev;
    //         }
    //         m_this_route->size--;
    //         delete this;
    //     }
    // }
    
    void removeTakeoff(){
        m_takeoff_flight = nullptr;
    }
    void removeReturn(){
        m_return_flight = nullptr;
    }

    // PRINTING //
    string toString(){
        string str = "Point: " + m_point.toString() + " - Total cost: ...";
        return str;
    }
};

#endif