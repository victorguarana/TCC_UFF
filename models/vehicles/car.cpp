#ifndef CAR_CPP
#define CAR_CPP

#include "vehicle.cpp"
#include "drone.cpp"

#define DEFAULT_CAR_TOTAL_RANGE 500
#define DEFAULT_CAR_TOTAL_STORAGE 1000
#define DEFAULT_CAR_SPEED 10

class Car : public Vehicle {
    private:
        Drone m_drone;

    public:
        // Constructors
        // "Clean" constructor
        Car(){
            setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
            setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
            setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setSpeed(DEFAULT_CAR_SPEED);
            setName("");
        }

        Car(string t_name, Drone t_drone){
            setTotalRange(DEFAULT_CAR_TOTAL_RANGE);
            setRemainingRange(DEFAULT_CAR_TOTAL_RANGE);
            setTotalStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_CAR_TOTAL_STORAGE);
            setSpeed(DEFAULT_CAR_SPEED);
            setName(t_name);
            m_drone = t_drone;
        }

        Drone* getDrone(){
            return &m_drone;
        }
};

#endif
