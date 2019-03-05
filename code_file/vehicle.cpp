#include "vehicle.hpp"

//Here we will add functions of the vehicle class


//Intialising the position and specification of the vehicle. 
void Vehicle::setType(string type){
    vehicle_type = type;
}

void Vehicle::setBasicAttributes(int l, int w, int acc, float initSpeed){
    length = l;
    width = w;
    acceleration = acc;
    brake = false;
    speed = initSpeed;
}

void Vehicle::setColour(string c){
    colour = c;
}

void Vehicle::setPosition(float x0 , float y0){
    x = x0;
    y = y0;
}


//Calculating the Next Set of coordinates from the previous set of the cooridinate of the vehicle. 
void Vehicle::NextPosition(){
    x = speed + x;
}


//Getters Function 
float Vehicle::Get_x(){
    return x;
}

float Vehicle::Get_y(){
    return y;
}

int Vehicle::Get_lenth(){
    return length;
}

int Vehicle::Get_width(){
    return width;
}