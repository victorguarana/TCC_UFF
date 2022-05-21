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
#include "models/route.cpp"
#include "heusristics/greedy.cpp"

int main(){
    Point ponto0("Ponto", 0, 0);

    Route initial_route = initialize_route();
    //initialize_route();
    Greedy::greedy(initial_route, ponto0);

    printRoute(initial_route);

    return 0; 
}
/**/
