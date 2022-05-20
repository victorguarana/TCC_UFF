#ifndef CAR_CPP
#define CAR_CPP

#include "vehicle.cpp"

class Car : public Vehicle {
    private:

        //Constants for each vehicle type
        const double m_total_range = 1000;
        const double m_total_storage = 500;
        
    public:
        /* Constructors */
        // "Clean" constructor
        Car(){
            setTotalRange(m_total_range);
            setRemainingRange(m_total_range);
            setTotalStorage(m_total_storage);
            setRemainingStorage(m_total_storage);
        }

        Car(double t_remaining_range, double t_remaining_storage){
            setTotalRange(m_total_range);
            setRemainingRange(t_remaining_range);
            setTotalStorage(m_total_storage);
            setRemainingStorage(t_remaining_storage);
        }
};

#endif
