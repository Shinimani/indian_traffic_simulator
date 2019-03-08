#ifndef VEHICLE_H
#define VEHICLE_H

#include "common.hpp"

// enum {car, bike, bus, truck}

class Vehicle{
    protected:  
        string vehicle_type; //Can change into enum type afterwards
        string colour;
        int length;
        int width;
        bool brake;
        float acceleration; //If brake = false
        float speed;
        float maxspeed;
        float maxAcceleration;
        int start_time;
        float x,y; //location of the top left of the vehicle

        void calSpeed();
    public:
        //Intialising the position and specification of the vehicle. 
        void setVehicle(string type, string colour, int len, int wid, int ispeed, int start_time, int ac, int maxSpeed);//, float x0, float y0);
        void setBasicAttributes(int l, int w, int acc, float initSpeed);
        void setColour(string c);
        void setPosition(float x, float y);         
        void setStartTime(int t);
        void setMaxSpeed(float maxspeed);
        void setType(string type);
        void setLength(int t);
        void setWidth(int w);
        void setMaxAcc(float a);

        //functions for getting the coordinates and dimension of the vehicle.
        float Get_x();
        float Get_y();
        int Get_lenth();
        int Get_width();
        string getType();
        int Get_start_time();
        void posInit(int road_wid);

        //Calculating the Next Set of coordinates from the previous set of the cooridinate of the vehicle. 
        void NextPosition();

        //Showing the basic attributes of the object of the class
        void ShowVehicle();

};

#endif