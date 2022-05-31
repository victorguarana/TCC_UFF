#ifndef DRONE_CPP
#define DRONE_CPP

#include "vehicle.cpp"
// #include "../point.cpp"
// #include "../route.cpp"

#define DEFAULT_DRONE_TOTAL_RANGE 100
#define DEFAULT_DRONE_TOTAL_STORAGE 10
#define DEFAULT_DRONE_SPEED 25


class Drone : public Vehicle {
    private:
        bool m_flying;

    public:
        // INITIALIZER //
        Drone(){
            setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
            setRemainingRange(DEFAULT_DRONE_TOTAL_RANGE);
            setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setSpeed(DEFAULT_DRONE_SPEED);
            setName("");
        }

        Drone(string t_name){
            setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
            setRemainingRange(DEFAULT_DRONE_TOTAL_RANGE);
            setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setSpeed(DEFAULT_DRONE_SPEED);
            setName(t_name);
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
            m_flying = false;
            resetAttributes();
        }
};

#endif
