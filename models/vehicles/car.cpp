#ifndef CAR_CPP
#define CAR_CPP

#include "vehicle.cpp"
#include "drone.cpp"
#include "../point.cpp"

#define DEFAULT_CAR_TOTAL_RANGE 500
#define DEFAULT_CAR_TOTAL_STORAGE 1000

class Car : public Vehicle {
    private:
        Drone m_drone;
        vector<Point> m_route;

    public:
        // Constructors
        // "Clean" constructor
        Car(){
            setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
            setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
            setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
        }

        Car(Drone drone){
            setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
            setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
            setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
            m_drone = drone;
        }

        Drone* getDrone(){
            return &m_drone;
        }
        vector<Point> getRoute(){
            return m_route;
        }

        void setRoute(vector<Point> t_route){
            m_route = t_route;
        }

        // TODO: When add point to route, use functions move and store in backend
        // To do this, need to add m_actual_point to car?
        void addPointToRoute(Point t_point){
            m_route.push_back(t_point);
        }
        void removePointFromRoute(int t_index){
            m_route.erase(m_route.begin() + t_index);
        }

};

#endif
