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

Route initialize_route(){
    Point ponto1;
    ponto1.lat = 10;
    ponto1.lon = 11;
    Client client1;
    client1.name = "Cliente1";
    client1.pos = ponto1;

    Point ponto2;
    ponto2.lat = 20;
    ponto2.lon = 21;
    Client client2;
    client2.name = "Cliente2";
    client2.pos = ponto2;

    Point ponto3;
    ponto3.lat = 5;
    ponto3.lon = 6;
    Client client3;
    client3.name = "Cliente3";
    client3.pos = ponto3;

    Point ponto4;
    ponto4.lat = 15;
    ponto4.lon = 16;
    Client client4;
    client4.name = "Cliente4";
    client4.pos = ponto4;

    Route route;
    route.clients[0] = client1;
    route.clients[1] = client2;
    route.clients[2] = client3;
    route.clients[3] = client4;
    route.size = 4;
    return route;
}