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
        Point* m_actual_position;

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
        void setActualPosition(Point* t_position){
            m_actual_position = t_position;
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
        Point* getActualPosition(){
            return m_actual_position;
        }

        void deliver(Point* t_point){
            if (m_actual_position == nullptr){
                m_actual_position = t_point;
                return;
            }

            if (t_point->is_client()){
                m_remaining_storage -= t_point->getPackage();
                m_remaining_range -= Point::distanceBetweenPoints(*m_actual_position, *t_point);;
            }
            else if (t_point->is_deposit()){
                this->resetAttributes();
            }
            this->setActualPosition(t_point);
        }
        void resetAttributes(){
            m_remaining_storage = m_total_storage;
            m_remaining_range = m_total_range;
        }
};

#endif
