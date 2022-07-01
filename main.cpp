#include "models/point.cpp"
#include "models/map.cpp"
#include "heusristics/greedy.cpp"
#include "heusristics/ils.cpp"

#include <vector>

int main(){

    Map initial_map = initializeMap("map.csv");
    Point initial_point = initial_map.deposits.at(0);

    vector<Car*> cars;
    Car* carro1 = new Car("Carro1", initial_point);
    Car* carro2 = new Car("Carro2", initial_point);

    cars.push_back(carro1);
    cars.push_back(carro2);

    Drone* drone1 = new Drone("Drone 1");
    Drone* drone2 = new Drone("Drone 2");

    carro1->setDrone(drone1);
    carro2->setDrone(drone2);

    // cout << "================================" << endl;
    // cout << "Initial Greedy Route (Car only):" << endl;
    // cout << "================================" << endl << endl;
    Greedy::multiple_car_greedy(initial_map, cars, initial_point);
    carro1->getRoute()->calcCosts();
    // carro1->getRoute()->print();
    cout << endl;
    carro2->getRoute()->calcCosts();
    // carro2->getRoute()->print();


    cout << endl << endl << endl;

    cout << "====================================" << endl;
    cout << "Hybrid Greedy Route (Car and drone):" << endl;
    cout << "====================================" << endl << endl;
    Greedy::add_drone_flight(carro1->getRoute());
    carro1->getRoute()->calcCosts();
    carro1->getRoute()->print();
    cout << endl;
    Greedy::add_drone_flight(carro2->getRoute());
    carro2->getRoute()->calcCosts();
    carro2->getRoute()->print();


    cout << endl << endl << endl;

    cout << "==========================" << endl;
    cout << "Swap Internal Worsts Stops (Car and Drone):" << endl;
    cout << "==========================" << endl << endl;
    Ils::swapWorstsStops(carro1->getRoute());
    carro1->getRoute()->calcCosts();
    carro1->getRoute()->print();
    cout << endl;
    Ils::swapWorstsStops(carro2->getRoute());
    carro2->getRoute()->calcCosts();
    carro2->getRoute()->print();


    cout << endl << endl << endl;

    cout << "==========================" << endl;
    cout << "Swap Worsts Car Stops (Only Car):" << endl;
    cout << "==========================" << endl << endl;
    Ils::swapWorstsCarStops(carro1->getRoute(), carro2->getRoute());
    carro1->getRoute()->calcCosts();
    carro1->getRoute()->print();
    cout << endl;
    carro2->getRoute()->calcCosts();
    carro2->getRoute()->print();


    cout << endl << endl << endl;

    cout << "==========================" << endl;
    cout << "Swap Worsts Drone Stops (Only Drone):" << endl;
    cout << "==========================" << endl << endl;
    Ils::swapWorstsDroneStops(carro1->getRoute(), carro2->getRoute());
    carro1->getRoute()->calcCosts();
    carro1->getRoute()->print();
    cout << endl;
    carro2->getRoute()->calcCosts();
    carro2->getRoute()->print();

    cout << endl;

}
