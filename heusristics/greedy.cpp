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

double calc_priority(Point actual, Client destiny){
    return distance_between_points(actual, destiny.pos);
}

Route set_best_client_for_position(Point actual, Route route, int actual_index){
    int best_index = actual_index;
    Client nearest_client = route.clients[actual_index];
    double highest_priority = calc_priority(actual, nearest_client);

    for(int i = actual_index + 1; i < route.size; i++){
        Client new_client = route.clients[i];
        double new_priority = calc_priority(actual, new_client);

        if (highest_priority > new_priority){
            highest_priority = new_priority;
            best_index = i;
        }
    }

    if(best_index != actual_index)
        route = change_clients(route, actual_index, best_index);

    return route;
}

Route greedy(Point actual_position, Route initial_route){
    Route greedy_route = initial_route;
    int size = initial_route.size;
    Client organized_clients[size];

    for (int i = 0; i < size; i++){
        greedy_route = set_best_client_for_position(actual_position, greedy_route, i);
        actual_position = greedy_route.clients[i].pos;
    }
    return greedy_route;
}

int main(){
    Point ponto0;
    ponto0.lat = 0;
    ponto0.lon = 0;

    Route initial_route = initialize_route();
    Route greedy_route = greedy(ponto0, initial_route);
    print_route(greedy_route);

    return 0; 
}
