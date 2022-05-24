#ifndef POSITION_CPP
#define POSITION_CPP

#include <cmath>
#include <string>

using namespace std;

enum pointType { Deposit, Client };

class Point{
    private:
        double m_latitude;
        double m_longitude;
        double m_package;
        string m_name;
        pointType m_type;

    public:
        Point(){
            m_latitude = 0;
            m_longitude = 0;
            m_name = "";
        }

        // Initializer for client
        Point(string t_name, double t_latitude, double t_longitude, double t_package){
            m_name = t_name;
            m_latitude = t_latitude;
            m_longitude = t_longitude;
            m_package = t_package;
            m_type = Client;
        }

        // Initializer for deposit
        Point(string t_name, double t_latitude, double t_longitude){
            m_name = t_name;
            m_latitude = t_latitude;
            m_longitude = t_longitude;
            m_package = -1;
            m_type = Deposit;
        }

        bool is_deposit(){
            return m_type == Deposit;
        }
        bool is_client(){
            return m_type == Client;
        }

        double getPackage(){
            return m_package;
        }

        string toString(){
            string str = m_name + " (Pos: " + to_string(m_latitude) +  " : " + to_string(m_longitude) + ")";
            if (is_client())
                str += " Pacote: " + to_string(m_package);

            return str;
        }
        bool equal(Point t_point){
            if (m_latitude == t_point.m_latitude && m_longitude == t_point.m_longitude && m_name == t_point.m_name && m_package == t_point.m_package && m_type  == t_point.m_type)
                return true;
            return false;
        }

        static double distanceBetweenPoints(Point t_p1, Point t_p2){
            return sqrt( ((t_p1.m_latitude - t_p2.m_latitude)*(t_p1.m_latitude - t_p2.m_latitude)) + ((t_p1.m_longitude - t_p2.m_longitude)*(t_p1.m_longitude - t_p2.m_longitude)) * 1.0);
        }
};

#endif
