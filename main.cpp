#include "models/point.cpp"
#include "models/map.cpp"
#include "models/vehicles/car.cpp"
#include "models/vehicles/drone.cpp"
#include "heusristics/greedy.cpp"
#include "heusristics/ils.cpp"

#include <vector>
#include <string>

int foo(string t_filename){

    cout << "================================" << endl;
    cout << t_filename << endl;

    Map initial_map = initializeMap(t_filename);
    Point initial_point = initial_map.deposits.at(0);

    vector<Car*> cars;
    Car* carro1 = new Car("Carro1", initial_point);
    cars.push_back(carro1);

    Drone* drone1 = new Drone("Drone 1");
    Drone* drone2 = new Drone("Drone 2");

    carro1->addDrone(drone1);
    carro1->addDrone(drone2);

    // cout << "================================" << endl;
    cout << "Initial Client Greedy Route (Car only):" << endl;
    // cout << "================================" << endl << endl;
    Greedy::nearest_client_greedy(initial_map, cars, initial_point);
    //Greedy::best_insertion_greedy(initial_map, cars, initial_point);
    carro1->getRoute()->calcCosts();
    carro1->getRoute()->print();


    // cout << endl << endl << endl;

    // cout << "====================================" << endl;
    cout << "Hybrid Client Greedy Route (Car and drone):" << endl;
    // cout << "====================================" << endl << endl;
    Greedy::add_drone_flight(carro1->getRoute());
    carro1->getRoute()->calcCosts();
    carro1->getRoute()->print();

    // Switcher cases:
    //  0 -> Shift DroneStop to CarStop
    //  1 -> Shift CarStop to DroneStop
    //  2 -> Swap DroneStops
    //  3 -> Swap DroneStop and CarStop

    int switcher = 4;

    cout << endl << endl << endl;
    switch (switcher){
    case 0:
        cout << "========================" << endl;
        cout << "Shift Stop: Drone to Car" << endl;
        cout << "========================" << endl << endl;
        Ils::shiftWorstDroneToCarStop(carro1->getRoute());
        break;
    
    case 1:
        cout << "========================" << endl;
        cout << "Shift Stop: Car to Drone" << endl;
        cout << "========================" << endl << endl;
        Ils::shiftWorstCarToDroneStop(carro1->getRoute());
        break;

    case 2:
        cout << "================" << endl;
        cout << "Swap Drone Stops" << endl;
        cout << "================" << endl << endl;
        Ils::swapWorstsDroneStops(carro1->getRoute());
        break;

    case 3:
        cout << "=================================" << endl;
        cout << "Swap Worsts Stops: Car and Drone:" << endl;
        cout << "=================================" << endl << endl;
        // TODO: Swap is setting returning flight wrong?
        Ils::swapWorstsStops(carro1->getRoute());
        break;
    default:
        return 0;
    }

    carro1->getRoute()->calcCosts();
    carro1->getRoute()->print();
    
    cout << endl;


    return 0;
}

int main(){
    // foo("all_maps//map1.csv");
    // foo("all_maps//map2.csv");
    // foo("all_maps//map3.csv");
    // foo("all_maps//map4.csv");
    // foo("all_maps//map5.csv");
    // foo("all_maps//map6.csv");
    // foo("all_maps//map7.csv");
    // foo("all_maps//map8.csv");
    // foo("all_maps//map9.csv");
    // foo("all_maps//map10.csv");
    // foo("all_maps//map11.csv");
    // foo("all_maps//map12.csv");
    // foo("all_maps//map13.csv");
    // foo("all_maps//map14.csv");
    // foo("all_maps//map15.csv");
    // foo("all_maps//map16.csv");
    // foo("all_maps//map17.csv");
    // foo("all_maps//map18.csv");
    // foo("all_maps//map19.csv");
    foo("all_maps//map20.csv");
}