#include "structs.cpp"
#include <string>
#include "../vehicles/vehicle.cpp"

class Client{
    private:
        Point pos;
        std::string name;
        double package;
        // Isso vai funcionar para descobrir qual tipo de veiculo está sendo utilizado?
        // Ou é preciso utilizar uma logica mais complexa utilizando dois membros separados?
        // Ou utilizar um enumerador dentro da classe de vehicle?
        Vehicle delivery_vehicle;

    public:
        Client(std::string t_name, Point t_pos, double t_package ){
            name = t_name;
            pos = t_pos;
            package = t_package;
        }

        Vehicle getDeliveryVehicle(){

        }
    
};