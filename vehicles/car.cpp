#define TOTALRANGE 1000
#define TOTALSTORAGE 500

class Car {
    private:
        double remaining_storage;
        double remaining_range;

    public:
        /* Constructors */
        // "Clean" constructor
        Car(){
            remaining_range = TOTALRANGE;
            remaining_storage = TOTALSTORAGE;
        }

        Car(double t_remaining_range, double t_remaining_storage){
            remaining_range = t_remaining_range;
            remaining_storage = t_remaining_storage;
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
        void setRemainingStorage(double t_remaining_storage){
            remaining_storage = t_remaining_storage;
        }

        void setRemainingRange(double t_remaining_range){
            remaining_range = t_remaining_range;
        }
};
