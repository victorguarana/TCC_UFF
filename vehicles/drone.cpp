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

        /* Getters */
        double get_total_storage(){
            return TOTALRANGE;
        }

        double get_remaining_storage(){
            return remaining_storage;
        }

        double get_used_storage(){
            return TOTALRANGE - remaining_storage;
        }

        /* Setters */
        void set_remaining_storage(double remaining_storage_param){
            remaining_storage = remaining_storage_param;
        }
};
