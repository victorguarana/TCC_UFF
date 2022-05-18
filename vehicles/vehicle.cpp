class Vehicle {
    private:
        double m_total_storage;
        double m_remaining_storage;
        double m_total_range;
        double m_remaining_range;

    public:
        /* Getters */
        double getTotalStorage(){
            return m_total_storage;
        }
        double getRemainingStorage(){
            return m_remaining_storage;
        }
        double getUsedStorage(){
            return m_total_storage - m_remaining_storage;
        }

        double getTotalRange(){
            return m_total_range;
        }
        double getRemainingRange(){
            return m_remaining_range;
        }
        double getUsedRange(){
            return m_total_range - m_remaining_range;
        }

        /* Setters */
        void setRemainingStorage(double t_remaining_storage){
            m_remaining_storage = t_remaining_storage;
        }
        void setRemainingRange(double t_remaining_range){
            m_remaining_range = t_remaining_range;
        }
        void setTotalStorage(double t_total_storage){
            m_total_storage = t_total_storage;
        }
        void setTotalRange(double t_total_range){
            m_total_range = t_total_range;
        }
};
