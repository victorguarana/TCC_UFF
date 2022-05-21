#ifndef ROUTE_CPP
#define ROUTE_CPP

#include <iostream>
#include <vector>
#include "client.cpp"

using namespace std;

struct Route{
    vector<Point> clients;
};


void printRoute(Route t_route){
    for(int i = 0; i < t_route.clients.size(); i++){
        cout << "#" << i << " -> " << t_route.clients.at(i).toString() << endl;
    }
}


Route swapClients(Route& t_route, int t_client_index1, int t_client_index2){
    swap(t_route.clients.at(t_client_index1), t_route.clients.at(t_client_index2));
    return t_route;
}

Route initialize_route(){
    Point client1("Client1", 10, 11, 10);
    Point client2("Client2", 20, 21, 10);
    Point client3("Client3", 5, 6, 10);
    Point client4("Client4", 15, 16, 10);

    Route route;
    route.clients.push_back(client1);
    route.clients.push_back(client2);
    route.clients.push_back(client3);
    route.clients.push_back(client4);
    return route;
}

#endif

/*
int main(){
    Route route = initialize_route();
    swapClients(route, 1, 3);
    printRoute(route);

    return 0;
}
*/
