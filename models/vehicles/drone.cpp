#ifndef DRONE_CPP
#define DRONE_CPP

#include "vehicle.cpp"
#include <vector>
#include "../point.cpp"

#define DEFAULT_DRONE_TOTAL_RANGE 100
#define DEFAULT_DRONE_TOTAL_STORAGE 10

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
        }

        Drone(double t_remaining_range, double t_remaining_storage){
            setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
            setRemainingRange(t_remaining_range);
            setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setRemainingStorage(t_remaining_storage);
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
            m_flights.push_back(flight);
        }
        void land(Point t_land_point){
            Flight flight = m_flights.at(m_flights.size()-1);
            flight.returning_point = t_land_point;
            m_flying = false;
        }

        void addPointToFlight(Point t_point){
            Flight flight = m_flights.at(m_flights.size()-1);
            flight.route.push_back(t_point);
        }
};

#endif
