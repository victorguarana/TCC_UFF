#ifndef DRONE_CPP
#define DRONE_CPP

#include "vehicle.cpp"

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
        void takeOff(){
            m_flying = true;
        }
        void land(){
            m_flying = true;
        }

        void addFlight(Flight t_flight){
            m_flights.push_back(t_flight);
        }

};

#endif
