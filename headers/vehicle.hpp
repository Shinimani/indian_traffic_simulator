#ifndef VEHICLE_H
#define VEHICLE_H

#include "common.hpp"

class Vehicle{
    protected:
            string colour;
            int length;
            int width;
            bool brake;
            float acceleration; //If brake = false
            float speed;
            float decelaration; //Will come into play if brake = true
            float x,y; //location of the top left of the vehicle

};

#endif