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
            float decelaration; //Will come into play if brake = true
            float x,y; //location of the top left of the vehicle
    public:
        void Vehicle::setType(string type);
        void Vehicle::setBasicAttributes(int l, int w, int acc, int dec, float initSpeed);
        void Vehicle::setColour(string c);



};

#endif