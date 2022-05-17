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
        double getTotalStorage(){
            return TOTALSTORAGE;
        }
        double getRemainingStorage(){
            return remaining_storage;
        }
        double getUsedStorage(){
            return TOTALSTORAGE - remaining_storage;
        }

        double getTotalRange(){
            return TOTALRANGE;
        }
        double getRemainingRange(){
            return remaining_range;
        }
        double getUsedRange(){
            return TOTALRANGE - remaining_range;
        }

        /* Setters */
        void setRemainingStorage(double remaining_storage_param){
            remaining_storage = remaining_storage_param;
        }

        void setRemainingRange(double remaining_range_param){
            remaining_range = remaining_range_param;
        }
};
