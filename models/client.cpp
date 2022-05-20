#include <string>

class Client{
    private:
        struct Point m_pos;
        std::string m_name;
        double m_package;

        // Ou é preciso utilizar uma logica mais complexa utilizando dois membros separados?
        // Ou utilizar um enumerador dentro da classe de vehicle?
        // Car m_delivery_car;
        // Drone m_delivery_drone;
        // enum Type { Car, Drone };

    public:
        Client(){
            Point ponto;
            ponto.lat = 0;
            ponto.lon = 0;
            m_pos = ponto;
            m_name = "Default";
            m_package = 0;
        }
        Client(std::string t_name, Point t_pos, double t_package){
            m_name = t_name;
            m_pos = t_pos;
            m_package = t_package;
        }

        std::string getName(){
            return m_name;
        }
        Point getPosition(){
            return m_pos;
        }
        
        std::string toString(){
            std::string client_str = getName() + " (Pos: " + std::to_string(getPosition().lat) +  " : " + std::to_string(getPosition().lon) + ")";
            return client_str;
        }
};