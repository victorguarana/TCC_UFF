#define TOTALRANGE 100
#define TOTALSTORAGE 10

class Drone {
    private:
        double remaining_storage;
        double remaining_range;

    public:
        /* Constructors */
        // "Clean" constructor
        Drone(){
            remaining_range = TOTALRANGE;
            remaining_storage = TOTALSTORAGE;
        }

        Drone(double remaining_range_init, double remaining_storage_init){
            remaining_range = remaining_range_init;
            remaining_storage = remaining_storage_init;
        }

        /* Getters */
        double get_total_storage(){
            return TOTALSTORAGE;
        }
        double get_remaining_storage(){
            return remaining_storage;
        }
        double get_used_storage(){
            return TOTALSTORAGE - remaining_storage;
        }

        double get_total_range(){
            return TOTALRANGE;
        }
        double get_remaining_range(){
            return remaining_range;
        }
        double get_used_range(){
            return TOTALRANGE - remaining_range;
        }

        /* Setters */
        void set_remaining_storage(double remaining_storage_param){
            remaining_storage = remaining_storage_param;
        }

        void set_remaining_range(double remaining_range_param){
            remaining_range = remaining_range_param;
        }
};
