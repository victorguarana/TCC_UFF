#ifndef DRONE_CPP
#define DRONE_CPP

#include "vehicle.cpp"
#include <vector>
#include "../point.cpp"

#define DEFAULT_DRONE_TOTAL_RANGE 100
#define DEFAULT_DRONE_TOTAL_STORAGE 10
#define DEFAULT_DRONE_SPEED 25

struct Flight{
    Point initial_point;
    Point returning_point;
    vector<Point> route;
};

class Drone : public Vehicle {
    private:
        // Specific Members for this vehiche type
        vector<Flight> m_flights;
        bool m_flying;

    public:
        /* Constructors */
        // "Clean" constructor
        Drone(){
            setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
            setRemainingRange(DEFAULT_DRONE_TOTAL_RANGE);
            setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setSpeed(DEFAULT_DRONE_SPEED);
        }

        Drone(double t_remaining_range, double t_remaining_storage){
            setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
            setRemainingRange(t_remaining_range);
            setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setRemainingStorage(t_remaining_storage);
            setSpeed(DEFAULT_DRONE_SPEED);
        }

    public:
        bool canDeliver(double t_distance, double t_package){
            return (t_package <= getRemainingStorage() && t_distance <= getRemainingRange());
        }
        bool isFlying(){
            return m_flying;
        }
        void takeOff(Point t_takeoff_point){
            m_flying = true;
            Flight flight;
            flight.initial_point = t_takeoff_point;
            flight.route.push_back(t_takeoff_point);
            m_flights.push_back(flight);
        }
        void land(Point t_land_point){
            Flight flight = m_flights.at(m_flights.size()-1);
            flight.route.push_back(t_land_point);
            flight.returning_point = t_land_point;
            resetRange();
            resetStorage();
            m_flying = false;
        }

        void addPointToFlight(Point t_point){
            Flight flight = m_flights.at(m_flights.size()-1);
            flight.route.push_back(t_point);
        }

        double route_distance(){
            double total_distance = 0;
            for(int i = 0; i < m_flights.size(); i++){
                Flight flight = m_flights.at(i);
                for(int j = 0; i < flight.route.size()-1; i++){
                    total_distance += Point::distanceBetweenPoints(flight.route.at(i), flight.route.at(i+1));
                }
            }
            return total_distance;
        }

};

#endif
