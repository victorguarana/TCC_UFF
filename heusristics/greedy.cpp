#include <iostream>
#include "greedy.hpp"

Route greedy(Point t_actual_position, Route t_route){
    Route greedy_route = t_route;
    int size = t_route.size;
    Client organized_clients[size];

    for (int i = 0; i < size; i++){
        greedy_route = set_best_client_for_position(t_actual_position, greedy_route, i);
        t_actual_position = greedy_route.clients[i].pos;
    }
    return greedy_route;
}

Route set_best_client_for_position(Point t_actual_position, Route t_route, int t_actual_index){
    int best_index = t_actual_index;
    Client nearest_client = t_route.clients[t_actual_index];
    double highest_priority = calc_priority(t_actual_position, nearest_client);

    for(int i = t_actual_index + 1; i < t_route.size; i++){
        Client new_client = t_route.clients[i];
        double new_priority = calc_priority(t_actual_position, new_client);

        if (highest_priority > new_priority){
            highest_priority = new_priority;
            best_index = i;
        }
    }

    if(best_index != t_actual_index)
        t_route = changeClients(t_route, t_actual_index, best_index);

    return t_route;
}

double calc_priority(Point t_actual, Client t_destiny){
    return distanceBetweenPoints(t_actual, t_destiny.pos);
}

/*
int main(){
    Point ponto0;
    ponto0.lat = 0;
    ponto0.lon = 0;

    Route initial_route = initialize_route();
    Route greedy_route = greedy(ponto0, initial_route);
    printRoute(greedy_route);

    return 0; 
}
*/