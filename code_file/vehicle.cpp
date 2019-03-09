#include "vehicle.hpp"

//Here we will add functions of the vehicle class


//Intialising the position and specification of the vehicle. 
void Vehicle::setVehicle(string type, string colour, int len, int wid, int iSpeed, int start_time, int ac=1, int maxSpeed=1){
    setType(type);
    setBasicAttributes(len, wid, ac, iSpeed);
    setMaxSpeed(maxSpeed);
    setColour(colour);
    setStartTime(start_time);
    // setPosition(x0, y0);
}

void Vehicle::setMaxSpeed(float maxSpeed){
    maxspeed = maxSpeed;
}

void Vehicle::setMaxAcc(float a){
    maxAcceleration = a;
}

void Vehicle::setType(string type){
    vehicle_type = type;
}

void Vehicle::setLength(int l){
    length = l;
}

void Vehicle::setWidth(int w){
    width = w;
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

void Vehicle::setCoverage(int mat_len){
    coverage={};
    int x = Get_x();
    int y = Get_y();
    int ele;
    for (int i = 0; i<Get_width();i++){
        for (int j = 0; j<Get_lenth();j++){
            int length;
            if (j+x > Get_lenth()){
                length = 0;
            } else {
                length = j+x;
            }
            ele = ((i+y)*mat_len + length); //This line will give the element in the road matrix.
            //(i+y) is the current row while length will make sure the column number doesn't exceed the lengh of the road
            coverage.push_back(ele);
        }
    }
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

vector<int> Vehicle::Get_coverage(){
    return coverage;
}


//Extra Functions for the greater good

void Vehicle::posInit(int road_wid){
    int veh_wid = Get_width();
    int den = road_wid - 2 - veh_wid +1;
    float y_c = (rand()%den)+1;
    setPosition(0,y_c);
}

// vector<int> Vehicle::coverage()

//Showing the attributes of the vehicle
void Vehicle::ShowVehicle(){
    cout<<"Vehicle Type: "<<vehicle_type;
    cout<<"\nVehicle Length: "<<length;
    cout<<"\nVehicle Width: "<<width;
    cout<<"\nVehicle MaxSpeed: "<<maxspeed;
    cout<<"\nVehicle MaxAcceleration: "<<maxAcceleration;
    cout<<endl<<endl;

}