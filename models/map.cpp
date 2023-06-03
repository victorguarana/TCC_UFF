#ifndef MAP_CPP
#define MAP_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "point.cpp"

using namespace std;

class Map{
    public:
        vector<Point> clients;
        vector<Point> deposits;

        void insertPoint(vector<string> t_point){
            if(t_point.size() < 3)
                return;

            string name = t_point.at(0);
            double lat = stod(t_point.at(1));
            double lon = stod(t_point.at(2));
            double package = -1;

            if (t_point.size() == 3){
                deposits.push_back(Point(name, lat, lon));
            }
            else if (t_point.size() == 4){
                package = stod(t_point.at(3));
                clients.push_back(Point(name, lat, lon, package));
            }
        }

        void setNeighbors(){
            for(int i = 0; i < clients.size(); i++){
                Point* actual_point = &clients.at(i);
                int nearest_point_distance_1 = -1, nearest_point_distance_2 = -1;

                for(int j = 0; j < clients.size(); j++){
                    if (i == j) continue;
                    Point* next_point = &clients.at(j);
                    int next_distance = Point::distanceBetweenPoints(*actual_point, *next_point);

                    if (nearest_point_distance_1 == -1 || next_distance < nearest_point_distance_1) {
                        nearest_point_distance_2 = nearest_point_distance_1;
                        nearest_point_distance_1 = next_distance;

                        actual_point->setSecondNearestNeigbor(actual_point->getFirstNearestNeigbor());
                        actual_point->setFirstNearestNeigbor(next_point);

                    } else if (nearest_point_distance_2 == -1 || next_distance < nearest_point_distance_2) { 
                        nearest_point_distance_2 = next_distance;

                        actual_point->setSecondNearestNeigbor(next_point);
                    }
                }
            }
        }

        static Map initializeMap(string t_filename){
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

                    map.insertPoint(row);
                }
            }
            else
                cout<<"Could not open the file\n";
        
            map.setNeighbors();

            return map;
        }
};

#endif
