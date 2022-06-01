#ifndef VEHICLE_CPP
#define VEHICLE_CPP

#include <string>

using namespace std;

class Vehicle {
    private:
        double m_total_storage;
        double m_remaining_storage;
        double m_total_range;
        double m_remaining_range;
        double m_speed;
        string m_name;

    protected:
        /* Setters */
        void setTotalStorage(double t_total_storage){
            m_total_storage = t_total_storage;
        }
        void setTotalRange(double t_total_range){
            m_total_range = t_total_range;
        }
        void setSpeed(double t_speed){
            m_speed = t_speed;
        }
        void setRemainingStorage(double t_remaining_storage){
            m_remaining_storage = t_remaining_storage;
        }
        void setRemainingRange(double t_remaining_range){
            m_remaining_range = t_remaining_range;
        }
        void setName(string t_name){
            m_name = t_name;
        }

    public:
        /* Getters */
        double getRemainingStorage(){
            return m_remaining_storage;
        }
        double getRemainingRange(){
            return m_remaining_range;
        }
        double getSpeed(){
            return m_speed;
        }
        string getName(){
            return m_name;
        }

        void deliver(Point t_point, double t_distance_travelled){
            if (t_point.is_client()){
                m_remaining_storage -= t_point.getPackage();
                m_remaining_range -= t_distance_travelled;
            }
            else if (t_point.is_deposit()){
                this->resetAttributes();
            }
        }
        void resetAttributes(){
            m_remaining_storage = m_total_storage;
            m_remaining_range = m_total_range;
        }
};

#endif
