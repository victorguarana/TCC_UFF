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
        Car* m_car;

    public:
        // INITIALIZER //
        Drone(){
            setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
            setRemainingRange(DEFAULT_DRONE_TOTAL_RANGE);
            setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setSpeed(DEFAULT_DRONE_SPEED);
            setName("");
            m_flying = false;
        }

        Drone(string t_name){
            setTotalRange(DEFAULT_DRONE_TOTAL_RANGE);
            setRemainingRange(DEFAULT_DRONE_TOTAL_RANGE);
            setTotalStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setRemainingStorage(DEFAULT_DRONE_TOTAL_STORAGE);
            setSpeed(DEFAULT_DRONE_SPEED);
            setName(t_name);
            m_flying = false;
        }

    public:
        bool canDeliver(double t_distance, double t_package){
            return (t_package <= getRemainingStorage() && t_distance <= getRemainingRange());
        }
        bool isFlying(){
            return m_flying;
        }
        void takeOff(Point* t_point){
            m_flying = true;
            setActualPosition(t_point);
        }
        void land(){
            m_flying = false;
            resetAttributes();
        }

        // OPERATIONS //
        void deliver(Point* t_point){
            Point* last_position = getActualPosition();

            if(last_position != nullptr){
                double remaining_storage = getRemainingStorage() - t_point->getPackage();
                double remaining_range = getRemainingRange() - Point::distanceBetweenPoints(*t_point, *t_point);
                setRemainingStorage(remaining_storage);
                setRemainingRange(remaining_range);

                //Debit from car storage too
                m_car->useStorage(t_point->getPackage());
            }
            setActualPosition(t_point);
        }
};

#endif
