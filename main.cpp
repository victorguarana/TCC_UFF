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

void print_routes(Route* route){
    route->calcCosts();
    route->print();
    cout << endl;
}

int main(){

    Map initial_map = Map::initializeMap("all_maps//map3.csv");
    Point initial_point = initial_map.deposits.at(0);

    Car* carro1 = new Car("Carro1", initial_point);
    Car* carro2 = new Car("Carro2", initial_point);

    vector <Route*> routes;
    Route* route1 = carro1->getRoute();
    Route* route2 = carro2->getRoute();
    routes.push_back(route1);
    routes.push_back(route2);

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
    Greedy::nearest_client_greedy(initial_map, routes, initial_point);
    //Greedy::best_insertion_greedy(initial_map, cars, initial_point);

    print_routes(route1);
    print_routes(route2);
    cout << endl << endl << endl;

    cout << "====================================" << endl;
    cout << "Hybrid Greedy Route (Car and drone):" << endl;
    cout << "====================================" << endl << endl;
    Greedy::add_drone_flight(route1);
    Greedy::add_drone_flight(route2);

    print_routes(route1);
    print_routes(route2);

    Route* backup_route1 = route1->duplicate();
    Route* backup_route2 = route2->duplicate();

    bool success;
    cout << "=========================" << endl;
    cout << "Selecting best Operation:" << endl;
    cout << "=========================" << endl << endl;

    cout << "===================================" << endl;
    cout << "Shift Worst Drone Stop to Car Stop:" << endl;
    cout << "===================================" << endl;
    success = Ils::shiftWorstDroneToCarStop(route1);
    if(success && route1->getTotalCost() < backup_route1->getTotalCost()){
        cout << "shiftWorstDroneToCarStop is better: " <<  route1->getTotalCost() << endl;
        backup_route1->erase();
        backup_route1 = route1->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        route1->erase();
        route1 = backup_route1->duplicate();
    }
    cout << endl;

    cout << "===================================" << endl;
    cout << "Shift Worst Car Stop to Drone Stop:" << endl;
    cout << "===================================" << endl;
    success = Ils::shiftWorstCarToDroneStop(route1);
    if(success && route1->getTotalCost() < backup_route1->getTotalCost()){
        cout << "shiftWorstCarToDroneStop is better: " <<  route1->getTotalCost() << endl;
        backup_route1->erase();
        backup_route1 = route1->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        route1->erase();
        route1 = backup_route1->duplicate();
    }
    cout << endl;

    cout << "=======================" << endl;
    cout << "Swap Worst Drone Stops:" << endl;
    cout << "=======================" << endl;
    success = Ils::swapWorstsDroneStops(route1);
    if(success && route1->getTotalCost() < backup_route1->getTotalCost()){
        cout << "swapWorstsDroneStops is better: " <<  route1->getTotalCost() << endl;
        backup_route1->erase();
        backup_route1 = route1->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        route1->erase();
        route1 = backup_route1->duplicate();
    }
    cout << endl;

    cout << "===============================" << endl;
    cout << "Swap Worst Car and Drone Stops:" << endl;
    cout << "===============================" << endl;
    success = Ils::swapWorstsStops(route1);
    if(success && route1->getTotalCost() < backup_route1->getTotalCost()){
        cout << "swapWorstsStops is better: " <<  route1->getTotalCost() << endl;
        backup_route1->erase();
        backup_route1 = route1->duplicate();
    } else {
        cout << "backup is better: " <<  backup_route1->getTotalCost() << endl;
        route1->erase();
        route1 = backup_route1->duplicate();
    }

    cout << endl;


    return 0;
}
