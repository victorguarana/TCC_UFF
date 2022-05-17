#include <iostream>
#include "../helpers.cpp"

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

double calc_priority(Point t_actual, Client t_destiny){
    return distanceBetweenPoints(t_actual, t_destiny.pos);
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

int main(){
    Point ponto0;
    ponto0.lat = 0;
    ponto0.lon = 0;

    Route initial_route = initialize_route();
    Route greedy_route = greedy(ponto0, initial_route);
    printRoute(greedy_route);

    return 0; 
}
