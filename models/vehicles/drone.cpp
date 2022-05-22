#ifndef DRONE_CPP
#define DRONE_CPP

#include "vehicle.cpp"

#define DEFAULT_DRONE_TOTAL_RANGE 100
#define DEFAULT_DRONE_TOTAL_STORAGE 10

class Drone : public Vehicle {
    private:
        // Specific Members for this vehiche type
        int m_battery_cicles;

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

        // Getters
        int getBatteryClicles(){
            return m_battery_cicles;
        }

        // Setters
        void setBatteryCicles(int t_battery_life){
            m_battery_cicles = t_battery_life;
        }
};

#endif
