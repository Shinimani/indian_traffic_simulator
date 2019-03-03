#include "vehicle.hpp"

//Here we will add functions of the vehicle class
void Vehicle::setType(string type){
    vehicle_type = type;
}

void Vehicle::setBasicAttributes(int l, int w, int acc, int dec, float initSpeed){
    length = l;
    width = w;
    acceleration = acc;
    decelaration = dec;
    brake = false;
    speed = initSpeed;
}
void Vehicle::setColour(string c){
    colour = c;
}