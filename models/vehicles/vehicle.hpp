#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>

class Point;

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
        void setTotalStorage(double);
        void setTotalRange(double);
        void setSpeed(double);
        void setRemainingStorage(double);
        void setRemainingRange(double);
        void setName(string);
        void setActualPosition(Point*);

    public:
        /* Getters */
        double getRemainingStorage();
        double getRemainingRange();
        double getSpeed();
        string getName();
        Point* getActualPosition();
        void resetAttributes();

        // Operations //
        bool canDeliver(double, double);
};

#endif
