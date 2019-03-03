#include "car.hpp"

void Car::setBasicAttributes(int l, int w, int acc, int dec, float initSpeed){
    length = l;
    width = w;
    acceleration = acc;
    decelaration = dec;
    brake = false;
    speed = initSpeed;
}
void Car::setColour(string c){
    colour = c;
}
