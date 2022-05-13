#include <iostream>
//namespace std;

class Car {
    private:
        double total_storage;
        double remaining_storage;

        double total_range;
        double remaining_range;

    public:
        /* Constructors */
        // "Clean" constructor
        Car(double total_storage_init, double total_range_init){
            total_range = total_range_init;
            remaining_range = total_range_init;
            total_storage = total_storage_init;
            remaining_storage = total_storage_init;
        }

        /* Getters */
        double get_total_storage(){
            return total_storage;
        }

        double get_remaining_storage(){
            return remaining_storage;
        }

        double get_used_storage(){
            return total_storage - remaining_storage;
        }

        /* Setters */
        double set_total_storage(double total_storage){
            return total_storage;
        }

        double set_remaining_storage(double value){
            return remaining_storage;
        }
};

int main(){
    Car car(4000, 500);
    std::cout << car.get_remaining_storage();
}