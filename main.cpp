/**
#include <iostream>
#include "models/vehicles/drone.cpp"
#include "models/vehicles/car.cpp"
#include "models/point.cpp"
#include "models/car_stop.cpp"

using namespace std;

int main(){
    Drone drone("Drone");
    Drone drone2(drone);
    drone2.deliver(10, 20);
    Drone* p_drone2 = &drone2;
    p_drone2->deliver(0, 20);
    drone2.resetAttributes();

    Point cliente0("nome", 10, 11, 10);

    CarStop carstop(&cliente0);

    // cout << car.getRemainingStorage() << endl;
    // cout << drone.getRemainingStorage() << endl;
    // cout << car2.getRemainingStorage() << endl;
};
/*/
// #include "helpers/database.cpp"
#include "models/point.cpp"
#include "models/map.cpp"
#include "heusristics/greedy.cpp"
#include "heusristics/ils.cpp"
// #include "measurer.cpp"

int main(){
    // Database database_instane;
    
    Point deposit("Deposito", 0, 0);

    Drone drone("Drone 1");
    Car car("Carro 1", drone);

    Map initial_map = initializeMap();

    Point far_client("Last Client", -1, 0, 990);
    initial_map.clients.push_back(far_client);

    cout << "Initial Route (Car only):" << endl;
    Route route = Greedy::single_car_greedy(initial_map, &car, deposit);
    route.setCosts();
    route.print();

    cout << "\n\n" << endl;

    cout << "Final Route (Car and drone):" << endl;
    Greedy::add_drone_flight(route);
    route.setCosts();
    route.print();

    cout << "\n\n" << endl;

    Ils::printWorstsStops(&route);

    return 0; 
}
/**/
