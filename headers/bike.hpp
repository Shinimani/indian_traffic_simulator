#ifndef CAR_H
#define CAR_H

#include "vehicle.hpp"

class Bike : public Vehicle{

    void setBasicAttributes(int l, int w, int acc, int dec, float initSpeed);
    void setColour(string c);

};

#endif