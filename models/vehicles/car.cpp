#ifndef CAR_CPP
#define CAR_CPP

#include "vehicle.cpp"

#define DEFAULT_CAR_TOTAL_RANGE 500
#define DEFAULT_CAR_TOTAL_STORAGE 1000

class Car : public Vehicle {
    public:
        // Constructors
        // "Clean" constructor
        Car(){
            setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
            setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
            setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
        }

        Car(double t_remaining_range, double t_remaining_storage){
            setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
            setRemainingRange(t_remaining_range);
            setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setRemainingStorage(t_remaining_storage);
        }
};

#endif
