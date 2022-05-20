#ifndef DRONE_CPP
#define DRONE_CPP

#include "vehicle.cpp"

class Drone : public Vehicle {
    private:

        //Constants for each vehicle type
        const double m_total_range = 100;
        const double m_total_storage = 10;
        
        // Specific Members for this vehiche type
        int m_battery_cicles;

    public:
        /* Constructors */
        // "Clean" constructor
        Drone(){
            setTotalRange(m_total_range);
            setRemainingRange(m_total_range);
            setTotalStorage(m_total_storage);
            setRemainingStorage(m_total_storage);
        }

        Drone(double t_remaining_range, double t_remaining_storage){
            setTotalRange(m_total_range);
            setRemainingRange(t_remaining_range);
            setTotalStorage(m_total_storage);
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
