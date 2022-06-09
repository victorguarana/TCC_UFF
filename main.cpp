#include "models/point.cpp"
#include "models/map.cpp"
#include "heusristics/greedy.cpp"
#include "heusristics/ils.cpp"


int main(){
    Point deposit("Deposito", 0, 0);

    Drone drone("Drone 1");
    Car car("Carro 1", drone);

    Map initial_map = initializeMap();

    Point far_client("Last Client", -1, 0, 990);
    initial_map.clients.push_back(far_client);

    cout << "Initial Greedy Route (Car only):" << endl;
    Route route = Greedy::single_car_greedy(initial_map, &car, deposit);
    route.calcCosts();
    route.print();


    cout << "\n\n" << endl;

    cout << "Hybrid Greedy Route (Car and drone):" << endl;
    Greedy::add_drone_flight(route);
    route.calcCosts();
    route.print();


    cout << "\n\n" << endl;

    cout << "Swap Worsts Stops (First):" << endl;
    Ils::printWorstsStops(&route);
    Ils::swapWorstsStops(&route);
    route.calcCosts();
    route.print();


    cout << "\n\n" << endl;

    cout << "Swap Worsts Stops (Second):" << endl;
    Ils::printWorstsStops(&route);
    Ils::swapWorstsStops(&route);
    route.calcCosts();
    route.print();


    cout << "\n\n" << endl;

    cout << "Swap Worsts Stops (Third):" << endl;
    Ils::printWorstsStops(&route);
    Ils::swapWorstsStops(&route);
    route.calcCosts();
    route.print();

    cout << "\n" << endl;
    return 0; 
}
