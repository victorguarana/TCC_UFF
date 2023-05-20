#ifndef CAR_HPP
#define CAR_HPP

#include <vector>

#include "vehicle.hpp"

#define DEFAULT_CAR_SPEED 10
class Route;
class Drone;

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
    void support(double);

    void changeRoute(Route *t_route);

};

#endif
