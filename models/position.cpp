struct Point{
    double lat;
    double lon;
};

double distanceBetweenPoints(Point t_p1, Point t_p2){
    return sqrt( ((t_p1.lat - t_p2.lat)*(t_p1.lat - t_p2.lat)) + ((t_p1.lon - t_p2.lon)*(t_p1.lon - t_p2.lon)) * 1.0);
}