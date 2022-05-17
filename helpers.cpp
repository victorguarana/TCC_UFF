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

double distanceBetweenPoints(Point p1, Point p2){
    return sqrt( ((p1.lat - p2.lat)*(p1.lat - p2.lat)) + ((p1.lon - p2.lon)*(p1.lon - p2.lon)) * 1.0);
}

void printRoute(Route route){
    for(int i = 0; i < route.size; i++){
        Client client = route.clients[i];
        std::cout << "Cliente " << client.name << " #" << i << " (Pos: " << client.pos.lat <<  " : " << client.pos.lon << ")" << std::endl;
    }
}

Route changeClients(Route route, int client1, int client2){
    Client c1 = route.clients[client1];
    Client c2 = route.clients[client2];
    route.clients[client1] = c2;
    route.clients[client2] = c1;
    return route;
}
