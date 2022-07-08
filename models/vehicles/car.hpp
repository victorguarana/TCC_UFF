#ifndef CAR_HPP
#define CAR_HPP

#include "vehicle.cpp"
#include "drone.cpp"

#define DEFAULT_CAR_TOTAL_RANGE 500
#define DEFAULT_CAR_TOTAL_STORAGE 1000
#define DEFAULT_CAR_SPEED 10
class Route;

class Car : public Vehicle {
    private:
    vector<Drone*> m_drone;
    Route* m_route;

    public:
    // CONSTRUCTORS //
    Car();
    Car(string, Point);

    // GETTERS //
    vector<Drone*> getDrones();
    Route* getRoute();

    // SETTERS //
    void addDrone(Drone*);


    // OPERATIONS //
    bool canDeliver(double, double);
    bool canSupport(double);
    void deliver(Point*);

};

#endif
