/**
#include <iostream>
#include "models/vehicles/drone.cpp"
#include "models/vehicles/car.cpp"
#include "models/point.cpp"

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
#include "measurer.cpp"

int main(){
    Point deposit("Deposito", 0, 0);
    Drone drone("Drone 1");
    Car car("Carro 1", drone);

    Map initial_map = initialize_map();

    Point far_client("Last Client", -1, 0, 990);
    initial_map.clients.push_back(far_client);

    cout << "Initial Route (Car only):" << endl;
    Greedy::single_car_greedy(car, initial_map, deposit);
    printPoints(car.getRoute());
    cout << "Measure (Car only): " << Measurer::route_measurer(car) << endl;


    // cout << "\n\n" << endl;

    // cout << "Final Route (Car and drone):" << endl;
    // Greedy::add_drone_flight(car);
    // printPoints(car.getRoute());
    // cout << "Measure (Car and drone): " << Measurer::route_measurer(car) << endl;

    return 0; 
}
/**/
