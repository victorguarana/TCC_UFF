#include <iostream>
#include "vehicles/car.cpp"

using namespace std;

int main(){
    Car car(4000.0, 500.0);
    std::cout << car.get_remaining_storage() << endl;
}