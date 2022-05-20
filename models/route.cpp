struct Route{
    int size;
    Client clients[4];
};

void printRoute(Route t_route){
    for(int i = 0; i < t_route.size; i++){
        Client client = t_route.clients[i];
        std::cout << "#" << i << " -> " << client.toString() << std::endl;
    }
}

Route changeClients(Route t_route, int t_client_index1, int t_client_index2){
    Client c1 = t_route.clients[t_client_index1];
    Client c2 = t_route.clients[t_client_index2];
    t_route.clients[t_client_index1] = c2;
    t_route.clients[t_client_index2] = c1;
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
    route.clients[0] = client1;
    route.clients[1] = client2;
    route.clients[2] = client3;
    route.clients[3] = client4;
    route.size = 4;
    return route;
}
