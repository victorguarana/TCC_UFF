#ifndef POSITION_CPP
#define POSITION_CPP

#include <cmath>

class Point{
    public:
        double lat;
        double lon;

    static double distanceBetweenPoints(Point t_p1, Point t_p2){
        return sqrt( ((t_p1.lat - t_p2.lat)*(t_p1.lat - t_p2.lat)) + ((t_p1.lon - t_p2.lon)*(t_p1.lon - t_p2.lon)) * 1.0);
    }
};

#endif
