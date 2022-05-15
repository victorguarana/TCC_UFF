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
        void set_total_storage(double total_storage_param){
            total_storage = total_storage_param;
        }

        void set_remaining_storage(double remaining_storage_param){
            remaining_storage = remaining_storage_param;
        }
};
