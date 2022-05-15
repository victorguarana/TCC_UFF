#include <iostream>
#include "vehicles/car.cpp"
#include "vehicles/drone.cpp"

using namespace std;

int main(){
    Drone drone;
    Car car2;
    Car car(4000.0, 800.0);
    std::cout << car.get_remaining_storage() << endl;
    std::cout << drone.get_remaining_storage() << endl;
    std::cout << car2.get_remaining_storage() << endl;
}
