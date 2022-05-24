#ifndef ROUTE_CPP
#define ROUTE_CPP

#include <iostream>
#include <vector>

using namespace std;

// DOUBT: Use vectors or linked list to represent?
struct Map{
    vector<Point> clients;
    vector<Point> deposits;
};

// Map and point Helpers
void printPoints(vector<Point> t_points){
    for(int i = 0; i < t_points.size(); i++){
        cout << "#" << i+1 << " -> " << t_points.at(i).toString() << endl;
    }
}

Map initialize_map(){
    Map map;

    Point deposit("Deposito", 0, 0);
    map.deposits.push_back(deposit);

    /*
    Point client1("Client1", 10, 11, 10);
    Point client2("Client2", 20, 21, 10);
    Point client3("Client3", 5, 6, 10);
    Point client4("Client4", 15, 16, 10);
    */
    Point client1("Client1", 10, 0, 10);
    Point client2("Client2", 20, 0, 10);
    Point client3("Client3", 5, 0, 10);
    Point client4("Client4", 15, 0, 10);
    map.clients.push_back(client1);
    map.clients.push_back(client2);
    map.clients.push_back(client3);
    map.clients.push_back(client4);

    return map;
}

#endif

/*
int main(){
    Route route = initialize_map();
    swapClients(route, 1, 3);
    printRoute(route);

    return 0;
}
*/
