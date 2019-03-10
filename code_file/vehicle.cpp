#include "vehicle.hpp"

//Here we will add functions of the vehicle class


//Intialising the position and specification of the vehicle. 
void Vehicle::setVehicle(string type, string colour, int len, int wid, int iSpeed, int start_time, int ac, int maxSpeed){
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

void Vehicle::setAcceleration(float ac){
    acceleration = ac;
}


void Vehicle::setSpeed(float Speed){
    speed = Speed;
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
    coverage.clear();
    int x = Get_x();
    int y = Get_y();
    tuple<int,int> ele;
    for (int i = 0; i<Get_width();i++){
        for (int j = 0; j<Get_lenth();j++){
            int length;
            length = j+x;
            ele = make_tuple( length,(i+y)); //This line will give the element in the road matrix.
            //(i+y) is the current row while length will make sure the column number doesn't exceed the lengh of the road
            coverage.push_back(ele);
        }
    }
}

void Vehicle::setFreeArea(vector<int> fa){
    free_area = fa;   
}

//function needed for simulation

//Calculating the Next Set of coordinates from the previous set of the cooridinate of the vehicle. 
void Vehicle::NextPosition(){
    calSpeed();
    x = speed + x;
}

//Calculating the speed of the vehicle
void Vehicle::calSpeed(){
    if(brake = 0){
        speed = speed - acceleration;
        if(speed < 0){
            speed = 0;
        }
    }else{
        speed = acceleration + speed;
        if(speed >= maxspeed){
            speed = maxspeed;
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

vector<tuple<int,int> > Vehicle::Get_coverage(){
    return coverage;
}


float Vehicle::GetMaxSpeed(){
    return maxspeed;
}

float Vehicle::GetMaxAccleration(){
    return maxAcceleration;
}

vector<int> Vehicle::Get_free_area(){
    return free_area;
}

string Vehicle::GetColour(){
    return colour;
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
    cout<<"\tVehicle Length: "<<length;
    cout<<"\tVehicle Width: "<<width;
    cout<<"\nSpeed: "<<speed;
    cout<<"\tVehicle MaxSpeed: "<<maxspeed;
    cout<<"\nAccelaration: "<<acceleration;
    cout<<"\tVehicle MaxAcceleration: "<<maxAcceleration;
    cout<<"\nBrake value:"<<brake;
    cout<<"\tColour: "<<colour;
    cout<<"\nStart Time: "<<start_time;
    cout<<"\nX: "<<x<<" Y: "<<y;
    cout<<"\nCoverage of the vehicle in the matrix: ";
    vector<tuple<int,int> > cv = Get_coverage();
    for (int i = 0; i<cv.size();i++){
        int firEle = get<0>(cv[i]);
        int secEle = get<1>(cv[i]);
        cout<<"("<<firEle<<","<<secEle<<") ";
    }
    // cout<<endl;
    cout<<"\nFree Area: ";
    cout<<"Front: "<<free_area[0]<<" Back: "<<free_area[1]<<" Left: "<<free_area[2]<<" Right: "<<free_area[3]<<endl<<endl;

}

//void Vehicle::setVehicle(string type, string colour, int len, int wid, int iSpeed, int start_time, int ac, int maxSpeed)
void Vehicle::ShowOrder(){
    cout<<"\n Type: "<<vehicle_type;
    cout<<"\n Colour: "<<colour;
    cout<<"\n Length: "<<length;
    cout<<"\n Width: "<<width;
    cout<<"\n Intial speed: "<<speed;
    cout<<"\n Start Time: "<<start_time;
    cout<<"\n Accleration: "<<acceleration;
    cout<<"\n Max Speed: "<<maxspeed<<endl;
}

void Vehicle::ShowEssential(){
    cout<<"\n Intial speed: "<<speed;
    cout<<"\n Acceleration: "<<acceleration;
    cout<<"\n Start Time: "<<start_time;
}

void Vehicle::ShowBasic(){
    cout<<"\n Type: "<<vehicle_type;
    cout<<"\n Colour: "<<colour;
    cout<<"\n Start Time: "<<start_time;
}