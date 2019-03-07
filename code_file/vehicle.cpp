#include "vehicle.hpp"

//Here we will add functions of the vehicle class


//Intialising the position and specification of the vehicle. 
void Vehicle::setVehicle(string type, string colour, int len, int wid, int iSpeed, int ac, int start_time){//, float x0, float y0){
    setType(type);
    setBasicAttributes(len, wid, ac, iSpeed);
    setColour(colour);
    setStartTime(start_time);
    // setPosition(x0, y0);
}


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

void Vehicle::setStartTime(int t){
    start_time = t;
}

//function needed for simulation

//Calculating the Next Set of coordinates from the previous set of the cooridinate of the vehicle. 
void Vehicle::NextPosition(){
    calSpeed();
    x = speed + x;
}

//Calculating the speed of the vehicle
void Vehicle::calSpeed(){
    if(brake = false){
        speed = acceleration + speed;
    }else{
        speed = speed - acceleration;
        if(speed < 0){
            speed = 0;
        }
    }
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
string Vehicle::getType(){
    return vehicle_type;
}

int Vehicle::Get_start_time(){
    return start_time;
}

//Extra Functions for the greater good

void Vehicle::posInit(int road_wid){
    int veh_wid = Get_width();
    int den = road_wid - 2 - veh_wid +1;
    float y_c = (rand()%den)+1;
    setPosition(0,y_c);
}

// vector<int> Vehicle::coverage()