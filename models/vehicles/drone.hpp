#ifndef DRONE_HPP
#define DRONE_HPP

#include "vehicle.hpp"

#define DEFAULT_DRONE_TOTAL_RANGE 100
#define DEFAULT_DRONE_TOTAL_STORAGE 10
#define DEFAULT_DRONE_SPEED 25


class Drone : public Vehicle {
    private:
        bool m_flying;

    public:
        // INITIALIZER //
        Drone();
        Drone(string t_name);

    public:
        // OPERATIONS //
        bool isFlying();
        void takeOff(Point*);
        void land();

        void deliver(Point*);

        static double defaultStorage();
};

#endif
