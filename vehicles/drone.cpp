#define TOTALRANGE 100
#define TOTALSTORAGE 10

class Drone {
    private:
        double m_remaining_range;
        double m_remaining_storage;

    public:
        /* Constructors */
        // "Clean" constructor
        Drone(){
            m_remaining_range = TOTALRANGE;
            m_remaining_storage = TOTALSTORAGE;
        }

        Drone(double t_remaining_range, double t_remaining_storage){
            m_remaining_range =  t_remaining_range;
            m_remaining_storage = t_remaining_storage;
        }

        /* Getters */
        double getTotalStorage(){
            return TOTALSTORAGE;
        }
        double getRemainingStorage(){
            return m_remaining_storage;
        }
        double getUsedStorage(){
            return TOTALSTORAGE - m_remaining_storage;
        }

        double getTotalRange(){
            return TOTALRANGE;
        }
        double getRemainingRange(){
            return m_remaining_range;
        }
        double getUsedRange(){
            return TOTALRANGE - m_remaining_range;
        }

        /* Setters */
        void setRemainingStorage(double t_remaining_storage){
            m_remaining_storage = t_remaining_storage;
        }

        void setRemainingRange(double  t_remaining_range){
            m_remaining_range =  t_remaining_range;
        }
};
