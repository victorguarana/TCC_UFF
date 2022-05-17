#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct Point{
    double lat;
    double lon;
};

struct Client{
    Point pos;
    std::string name;
};

struct Route{
    int size;
    struct Client clients[4];
};

double distanceBetweenPoints(Point t_p1, Point t_p2){
    return sqrt( ((t_p1.lat - t_p2.lat)*(t_p1.lat - t_p2.lat)) + ((t_p1.lon - t_p2.lon)*(t_p1.lon - t_p2.lon)) * 1.0);
}

void printRoute(Route t_route){
    for(int i = 0; i < t_route.size; i++){
        Client client = t_route.clients[i];
        std::cout << "Cliente " << client.name << " #" << i << " (Pos: " << client.pos.lat <<  " : " << client.pos.lon << ")" << std::endl;
    }
}

Route changeClients(Route t_route, int t_client_index1, int t_client_index2){
    Client c1 = t_route.clients[t_client_index1];
    Client c2 = t_route.clients[t_client_index2];
    t_route.clients[t_client_index1] = c2;
    t_route.clients[t_client_index2] = c1;
    return t_route;
}
