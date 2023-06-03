// including *.cpp instead of *.hpp to simplify compilation and run

#include "models/car_stop.cpp"
#include "models/drone_stop.cpp"
#include "models/flight.cpp"
#include "models/point.cpp"
#include "models/car_stop.cpp"
#include "models/map.cpp"
#include "models/vehicles/vehicle.cpp"
#include "models/vehicles/car.cpp"
#include "models/vehicles/drone.cpp"
#include "heusristics/greedy.cpp"
#include "heusristics/ils.cpp"

#include <vector>

int main(){

    Map initial_map = Map::initializeMap("all_maps//map1.csv");
    Point initial_point = initial_map.deposits.at(0);

    vector<Car*> cars;
    Car* carro1 = new Car("Carro1", initial_point);
    Car* carro2 = new Car("Carro2", initial_point);
    cars.push_back(carro1);
    cars.push_back(carro2);

    Drone* drone11 = new Drone("Drone 1.1");
    Drone* drone12 = new Drone("Drone 1.2");

    Drone* drone21 = new Drone("Drone 2.1");
    Drone* drone22 = new Drone("Drone 2.2");

    carro1->addDrone(drone11);
    carro1->addDrone(drone12);
    carro2->addDrone(drone21);
    carro2->addDrone(drone22);

    cout << "================================" << endl; 
    cout << "Initial Greedy Route (Car only):" << endl;
    cout << "================================" << endl << endl;
    Greedy::nearest_client_greedy(initial_map, cars, initial_point);
    //Greedy::best_insertion_greedy(initial_map, cars, initial_point);

    for(int i = 0; i < cars.size(); i++){
        cars.at(i)->getRoute()->calcCosts();
        cars.at(i)->getRoute()->print();
        cout << endl;
    }

    cout << endl << endl << endl;

    cout << "====================================" << endl;
    cout << "Hybrid Greedy Route (Car and drone):" << endl;
    cout << "====================================" << endl << endl;
    Greedy::add_drone_flight(carro1->getRoute());
    Greedy::add_drone_flight(carro2->getRoute());

    for(int i = 0; i < cars.size(); i++){
        cars.at(i)->getRoute()->calcCosts();
        cars.at(i)->getRoute()->print();
        cout << endl;
    }

    Route* backup_route1 = carro1->getRoute()->duplicate();
    Route* backup_route2 = carro2->getRoute()->duplicate();
    
    cout << "=========================" << endl;
    cout << "Selecting best Operation:" << endl;
    cout << "=========================" << endl << endl;

    cout << "===================================" << endl;
    cout << "Shift Worst Drone Stop to Car Stop:" << endl;
    cout << "===================================" << endl;
    Ils::shiftWorstDroneToCarStop(carro1->getRoute());
    if(backup_route1->getTotalCost() > carro1->getRoute()->getTotalCost()){
        cout << "shiftWorstDroneToCarStop is better: " <<  carro1->getRoute()->getTotalCost() << endl;
        backup_route1 = carro1->getRoute()->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        carro1->changeRoute(backup_route1->duplicate());
    }
    cout << endl;

    cout << "===================================" << endl;
    cout << "Shift Worst Car Stop to Drone Stop:" << endl;
    cout << "===================================" << endl;
    Ils::shiftWorstCarToDroneStop(carro1->getRoute());
    if(backup_route1->getTotalCost() > carro1->getRoute()->getTotalCost()){
        cout << "shiftWorstCarToDroneStop is better: " <<  carro1->getRoute()->getTotalCost() << endl;
        backup_route1 = carro1->getRoute()->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        carro1->changeRoute(backup_route1->duplicate());
    }
    cout << endl;

    cout << "=======================" << endl;
    cout << "Swap Worst Drone Stops:" << endl;
    cout << "=======================" << endl;
    Ils::swapWorstsDroneStops(carro1->getRoute());
    if(backup_route1->getTotalCost() > carro1->getRoute()->getTotalCost()){
        cout << "swapWorstsCarStops is better: " <<  carro1->getRoute()->getTotalCost() << endl;
        backup_route1 = carro1->getRoute()->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        carro1->changeRoute(backup_route1->duplicate());
    }
    cout << endl;

    cout << "===============================" << endl;
    cout << "Swap Worst Car and Drone Stops:" << endl;
    cout << "===============================" << endl;
    Ils::swapWorstsStops(carro1->getRoute());
    if(backup_route1->getTotalCost() > carro1->getRoute()->getTotalCost()){
        cout << "swapWorstsStops is better: " <<  carro1->getRoute()->getTotalCost() << endl;
        backup_route1 = carro1->getRoute()->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        carro1->changeRoute(backup_route1->duplicate());
    }

    carro1->getRoute()->toFile("result.csv");

    for(int i = 0; i < cars.size(); i++){
        cars.at(i)->getRoute()->calcCosts();
        cars.at(i)->getRoute()->print();
        cout << endl;
    }
    
    cout << endl;


    return 0;
}
