#ifndef VEHICLE_CPP
#define VEHICLE_CPP

class Vehicle {
    private:
        double m_total_storage;
        double m_remaining_storage;
        double m_total_range;
        double m_remaining_range;
        double m_speed;

    protected:
        void setTotalStorage(double t_total_storage){
            m_total_storage = t_total_storage;
        }
        void setTotalRange(double t_total_range){
            m_total_range = t_total_range;
        }
        void setSpeed(double t_speed){
            m_speed = t_speed;
        }
        /* Setters */
        void setRemainingStorage(double t_remaining_storage){
            m_remaining_storage = t_remaining_storage;
        }
        void setRemainingRange(double t_remaining_range){
            m_remaining_range = t_remaining_range;
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

        void deliver(double t_stored_space, double t_distance_travelled){
            m_remaining_storage -= t_stored_space;
            m_remaining_range -= t_distance_travelled;
        }
        void resetStorage(){
            m_remaining_storage = m_total_storage;
        }
        void resetRange(){
            m_remaining_range = m_total_range;
        }
};

#endif
