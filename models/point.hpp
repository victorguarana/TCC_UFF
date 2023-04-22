#ifndef POSITION_HPP
#define POSITION_HPP

#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <list>

class CarStop;
class DroneStop;

using namespace std;

enum pointType { Deposit, Client };

class Point{
    private:
    // DATA //
    double m_latitude;
    double m_longitude;
    double m_package;
    string m_name;
    pointType m_type;
    Point* m_nearest_points[2];
    CarStop* m_car_stop;
    DroneStop* m_drone_stop;

    // PRIVATE INITIALIZER //
    Point();


    public:
    // PUBLIC INITIALIZERS //
    // Initializer for client (Used in map and main)
    Point(string, double, double, double);

    // Initializer for deposit (Used in map and main)
    Point(string, double, double);

    // Initializer with memory allocation and returning pointer
    static Point* create(Point);


    // GETTERS //
    bool is_deposit();
    bool is_client();

    double getPackage();

    string getName();

    Point* getFirstNearestNeigbor();
    Point* getSecondNearestNeigbor();
    CarStop* getCarStop();
    DroneStop* getDroneStop();


    // SETTERS //
    void setFirstNearestNeigbor(Point*);
    void setSecondNearestNeigbor(Point*);
    void setCarStop(CarStop*);
    void setDroneStop(DroneStop*);


    // STRINGFY //
    string toString();

    // OPERATIONS //
    bool equal(Point);
    void erase();
    static double distanceBetweenPoints(Point t_p1, Point t_p2);
};

#endif
