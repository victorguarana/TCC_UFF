#ifndef POSITION_CPP
#define POSITION_CPP

#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

enum pointType { Deposit, Client };

class Point{
    private:
    // DATA //
    double m_latitude;
    double m_longitude;
    double m_package;
    string m_name;
    pointType m_type;

    // PRIVATE INITIALIZER //
    Point(){
        m_latitude = 0;
        m_longitude = 0;
        m_name = "";
    }


    public:
    // PUBLIC INITIALIZERS //
    // Initializer for client (Used in map and main)
    Point(string t_name, double t_latitude, double t_longitude, double t_package){
        m_name = t_name;
        m_latitude = t_latitude;
        m_longitude = t_longitude;
        m_package = t_package;
        m_type = Client;
    }

    // Initializer for deposit (Used in map and main)
    Point(string t_name, double t_latitude, double t_longitude){
        m_name = t_name;
        m_latitude = t_latitude;
        m_longitude = t_longitude;
        m_package = -1;
        m_type = Deposit;
    }

    // Initializer with memory allocation and returning pointer
    static Point* create(Point t_point){
        return new Point(t_point);
    }


    // GETTERS //
    bool is_deposit(){
        return m_type == Deposit;
    }
    bool is_client(){
        return m_type == Client;
    }

    double getPackage(){
        return m_package;
    }


    // STRINGFY //
    string toString(){
        std::stringstream latitude, longitude, package;
        latitude << std::fixed << std::setprecision(2) << m_latitude;
        longitude << std::fixed << std::setprecision(2) << m_longitude;
        package << std::fixed << std::setprecision(2) << m_package;

        string str = m_name + " (Pos: " + latitude.str() +  " : " + longitude.str() + ")";
        if (is_client())
            str += " Pacote: " + package.str();

        return str;
    }

    // OPERATIONS //
    bool equal(Point t_point){
        if (m_latitude == t_point.m_latitude && m_longitude == t_point.m_longitude && m_name == t_point.m_name && m_package == t_point.m_package && m_type  == t_point.m_type)
            return true;
        return false;
    }
    void erase(){
        delete this;
    }
    static double distanceBetweenPoints(Point t_p1, Point t_p2){
        return sqrt( ((t_p1.m_latitude - t_p2.m_latitude)*(t_p1.m_latitude - t_p2.m_latitude)) + ((t_p1.m_longitude - t_p2.m_longitude)*(t_p1.m_longitude - t_p2.m_longitude)) * 1.0);
    }
};

#endif
