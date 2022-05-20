class Greedy{
    private:
        /**
            Calculates the priority based on the distance from the actual position to the client
            @param t_destiny client to be used in the calculation
            @param t_actual drivers actual position
        */
        static double calc_priority(Client t_destiny, Point t_actual){
            return distanceBetweenPoints(t_actual, t_destiny.getPosition()) * -1 ;
        }

        /**
            Finds the best unvisited client to the actual position
            @param t_route route to be modified
            @param t_actual_position drivers actual position (usually is the same as the last client)
            @param t_actual_index index used as a pivot to define which position has to be calculated
        */
        static void set_best_client_for_position(Route& t_route, Point t_actual_position, int t_actual_index){
            int best_index = t_actual_index;
            Client nearest_client = t_route.clients[t_actual_index];
            double highest_priority = calc_priority(nearest_client, t_actual_position);

            for(int i = t_actual_index + 1; i < t_route.size; i++){
                Client new_client = t_route.clients[i];
                double new_priority = calc_priority(new_client, t_actual_position);

                if (highest_priority < new_priority){
                    highest_priority = new_priority;
                    best_index = i;
                }
            }

            if(best_index != t_actual_index)
                t_route = changeClients(t_route, t_actual_index, best_index);
        }
    public: 
        /**
            Implements a greedy algorithm to get an good route
            @param t_route initial route
            @param t_actual_position route starting point
        */
        static void greedy(Route& t_route, Point t_actual_position){
            int size = t_route.size;

            for (int i = 0; i < size; i++){
                set_best_client_for_position(t_route, t_actual_position, i);
                t_actual_position = t_route.clients[i].getPosition();
            }
        }
};

/*
int main(){
    Point ponto0;
    ponto0.lat = 0;
    ponto0.lon = 0;

    Route initial_route = initialize_route();
    Greedy::greedy(initial_route, ponto0);

    printRoute(initial_route);

    return 0; 
}
*/