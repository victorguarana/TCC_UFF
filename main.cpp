#include "main.hpp"

/*
int main(){
    Drone drone(100, 200);
    Car car2;
    Car car(4000.0, 800.0);
    std::cout << car.getRemainingStorage() << std::endl;
    std::cout << drone.getRemainingStorage() << std::endl;
    std::cout << car2.getRemainingStorage() << std::endl;
};
*/
int main(){
    Point ponto0;
    ponto0.lat = 0;
    ponto0.lon = 0;

    Route initial_route = initialize_route();
    Greedy::greedy(initial_route, ponto0);

    printRoute(initial_route);

    return 0; 
}
