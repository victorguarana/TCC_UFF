/**
#include <iostream>
#include "models/vehicles/drone.cpp"
#include "models/vehicles/car.cpp"
#include "models/point.cpp"
#include "models/client.cpp"

using namespace std;

int main(){
    Drone drone(100, 200);
    Car car2;
    Car car(4000.0, 800.0);

    Point cliente0("nome", 10, 11, 10);

    cout << car.getRemainingStorage() << endl;
    cout << drone.getRemainingStorage() << endl;
    cout << car2.getRemainingStorage() << endl;
};
/*/

#include "models/point.cpp"
#include "models/map.cpp"
#include "heusristics/greedy.cpp"

int main(){
    Point deposit("Deposito", 0, 0);
    Car car;
    Map initial_map = initialize_map();

    Point far_client("Last Client", -1, -5, 990);
    initial_map.clients.push_back(far_client);

    cout << "Initial Route (Car only):" << endl;
    Greedy::single_car_greedy(car, initial_map, deposit);
    printPoints(car.getRoute());

    cout << "\n\n" << endl;

    cout << "Final Route (Car and drone):" << endl;
    Greedy::add_drone_flight(car);
    printPoints(car.getRoute());

    return 0; 
}
/**/
