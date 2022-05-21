#ifndef ROUTE_CPP
#define ROUTE_CPP

#include <iostream>
#include <vector>
#include "client.cpp"

using namespace std;

struct Route{
    vector<Client> clients;
};

void printRoute(Route t_route){
    for(int i = 0; i < t_route.clients.size(); i++){
        Client client = t_route.clients.at(i);
        cout << "#" << i << " -> " << client.toString() << endl;
    }
}

Route swapClients(Route& t_route, int t_client_index1, int t_client_index2){
    swap(t_route.clients.at(t_client_index1), t_route.clients.at(t_client_index2));
    return t_route;
}

Route initialize_route(){
    Point ponto1;
    ponto1.lat = 10;
    ponto1.lon = 11;
    Client client1("Cliente1", ponto1, 10);

    Point ponto2;
    ponto2.lat = 20;
    ponto2.lon = 21;
    Client client2("Cliente2", ponto2, 10);

    Point ponto3;
    ponto3.lat = 5;
    ponto3.lon = 6;
    Client client3("Cliente3", ponto3, 10);

    Point ponto4;
    ponto4.lat = 15;
    ponto4.lon = 16;
    Client client4("Cliente4", ponto4, 10);

    Route route;
    route.clients.push_back(client1);
    route.clients.push_back(client2);
    route.clients.push_back(client3);
    route.clients.push_back(client4);
    return route;
}

#endif

int main(){
    Route route = initialize_route();
    swapClients(route, 1, 3);
    printRoute(route);

    return 0;
}
