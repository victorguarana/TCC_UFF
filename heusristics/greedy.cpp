#include <iostream>
#include "../helpers/structs.cpp"



// ####### //
// HEADERS //
// ####### //
void greedy(Route&, Point);
void set_best_client_for_position(Route&, Point, int);
double calc_priority(Client, Point);



// ############## //
// IMPLEMENTATION //
// ############## //
void greedy(Route& t_route, Point t_actual_position){
    int size = t_route.size;
    Client organized_clients[size];

    for (int i = 0; i < size; i++){
        set_best_client_for_position(t_route, t_actual_position, i);
        t_actual_position = t_route.clients[i].pos;
    }
}

// Find the best unvisited client to the actual position
// Using the actual index as a pivot to define which position has to be calculated
void set_best_client_for_position(Route& t_route, Point t_actual_position, int t_actual_index){
    int best_index = t_actual_index;
    Client nearest_client = t_route.clients[t_actual_index];
    double highest_priority = calc_priority(nearest_client, t_actual_position);

    for(int i = t_actual_index + 1; i < t_route.size; i++){
        Client new_client = t_route.clients[i];
        double new_priority = calc_priority(new_client, t_actual_position);

        if (highest_priority < new_priority){
            highest_priority = new_priority;
            best_index = i;
        }
    }

    if(best_index != t_actual_index)
        t_route = changeClients(t_route, t_actual_index, best_index);
}

double calc_priority(Client t_destiny, Point t_actual){
    return distanceBetweenPoints(t_actual, t_destiny.pos) * -1 ;
}

/*
int main(){
    Point ponto0;
    ponto0.lat = 0;
    ponto0.lon = 0;

    Route initial_route = initialize_route();
    greedy(initial_route, ponto0);
    printRoute(initial_route);

    return 0; 
}
*/