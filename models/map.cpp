#ifndef MAP_CPP
#define MAP_CPP

#include <iostream>
#include <vector>

#include "point.cpp"

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

    map.deposits.push_back(Point("Deposito", 0, 0));

    /*
    Point client1("Client1", 10, 11, 10);
    Point client2("Client2", 20, 21, 10);
    Point client3("Client3", 5, 6, 10);
    Point client4("Client4", 15, 16, 10);
    */
    map.clients.push_back(Point("Client1", 10, 0, 10));
    map.clients.push_back(Point("Client2", 20, 0, 10));
    map.clients.push_back(Point("Client3", 5, 0, 10));
    map.clients.push_back(Point("Client4", 15, 0, 10));
    map.clients.push_back(Point("Client5", 30, 0, 10));
    map.clients.push_back(Point("Client6", 25, 0, 10));

    return map;
}

#endif
