#ifndef MAP_CPP
#define MAP_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "point.cpp"

using namespace std;

// DOUBT: Use vectors or linked list to represent?
struct Map{
    vector<Point> clients;
    vector<Point> deposits;
};

void insertPoint(Map &t_map, vector<string> t_point){
    if(t_point.size() < 3)
        return;

    string name = t_point.at(0);
    double lat = stod(t_point.at(1));
    double lon = stod(t_point.at(2));
    double package = -1;

    if (t_point.size() == 3){
        t_map.deposits.push_back(Point(name, lat, lon));
    }
    else if (t_point.size() == 4){
        package = stod(t_point.at(3));
        t_map.clients.push_back(Point(name, lat, lon, package));
    }
}


Map initializeMap(string t_filename){
    Map map;

    vector<string> row;
    string line, word;
 
    fstream file (t_filename, ios::in);

    if(file.is_open()){
        while(getline(file, line)){
            row.clear();

            stringstream str(line);
 
            while(getline(str, word, ';'))
                row.push_back(word);

            insertPoint(map, row);
        }
    }
    else
        cout<<"Could not open the file\n";
 

    return map;
}

#endif
