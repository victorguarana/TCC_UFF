#ifndef CHROMOSSOME_CPP
#define CHROMOSSOME_CPP

#include <vector>
#include "point.cpp"
#include "vehicles/car.cpp"

enum Deliverer { CAR, DRONE };

class Chromo{
    private:
        Point m_point;
        Deliverer m_deliverer = CAR;

    public:
        // Initializers
        Chromo(Point t_point){
            m_point = t_point;
        }

        // Getters
        bool isDeliveredByCar(){
            return m_deliverer == CAR;
        }
        bool isDeliveredByDrone(){
            return m_deliverer == DRONE;
        }

        // Setters
        void DeliveredByCar(){
            m_deliverer = CAR;
        }
        void DeliveredByDrone(){
            m_deliverer = DRONE;
        }

        // Operations
        void changeOrder(){

        }
        void changeDeliverer(){
            
        }
};

#endif
