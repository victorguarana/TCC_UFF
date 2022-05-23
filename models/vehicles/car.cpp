#ifndef CAR_CPP
#define CAR_CPP

#include "vehicle.cpp"
#include "drone.cpp"
#include "../point.cpp"
#include "../chromosome.cpp"

#define DEFAULT_CAR_TOTAL_RANGE 500
#define DEFAULT_CAR_TOTAL_STORAGE 1000
#define DEFAULT_CAR_SPEED 10

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
            setSpeed(DEFAULT_CAR_SPEED);
        }

        Car(Drone drone){
            setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
            setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
            setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setSpeed(DEFAULT_CAR_SPEED);
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

        double route_distance(){
            double total_distance = 0;
            for(int i = 0; i < m_route.size()-1 ; i++){
                total_distance += Point::distanceBetweenPoints(m_route.at(i), m_route.at(i+1));
            }
            return total_distance;
        }

        vector<Chromo> toChromos(){
            vector<Chromo> chromos;
            for(int i = 1; i < m_route.size()-1; i++){
                Point actual_point = m_route.at(i);
                Chromo chromo(actual_point);
                chromos.push_back(chromo);
                m_drone.appendFlightChromos(chromos, actual_point);
            }
            return chromos;
        }
};

#endif
