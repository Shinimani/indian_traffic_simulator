#include "vehicle.hpp"

//Here we will add functions of the vehicle class


//Intialising the position and specification of the vehicle. 
void Vehicle::setVehicle(string type, string colour, int len, int wid, int iSpeed, int start_time, int ac, int maxSpeed){
    setType(type);
    setBasicAttributes(len, wid, ac, iSpeed);
    setMaxSpeed(maxSpeed);
    setColour(colour);
    setStartTime(start_time);
    brake = 0;
    cout<<brake<<endl;
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

void Vehicle::setSumAllVeh(int i){
    sumAllVeh = i;
}

void Vehicle::setLCProb(float f){
    laneChangeProb = f;   
}

float Vehicle:: callaneChangeProb(){
    int l = Get_lenth();
    int w = Get_width();
    cout<<"Sum: "<<sumAllVeh<<" "<<endl;
    float lcp = (1 - ((0.75)*float(l*w)/sumAllVeh))*0.5;
    laneChangeProb = lcp;
    cout<<lcp<<" ";
    return laneChangeProb;
}

void Vehicle::setBasicAttributes(int l, int w, int acc, float initSpeed){
    length = l;
    width = w;
    acceleration = acc;
    brake = 1;
    speed = initSpeed;
}

void Vehicle::setBrake(int t){
    brake = t;
}


void Vehicle::setAcceleration(float ac){
    acceleration = ac;
}

// void Vehicle::setDeceleration(float ac){
//     acceleration = ac;
// }

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
void Vehicle::collisionAvoider(int mat_len){
    vector<int> fs = Get_free_area();
    int front = fs[0];
    int vspeed = Get_speed();
    int currX = Get_x();
    int vacc = Get_acceleration();
    int dec = decelaration;
    //Brake 1 is forward accelaration. Brake 0 is retardation
    if (mat_len - Get_x()<=3*Get_lenth()){
        setBrake(1);
    }else if(Get_x()<=1){
        setBrake(1);
    }
    else if (front < 2){
        float currProb = laneChangeProb;
        setBrake(0);
        // setLCProb(laneChangeProb + ((0.9)* (1-currProb)));
        setSpeed(0);
    } 
    else if(front>(vacc + vspeed - 2) && front<2*(vacc + vspeed - 2) && vspeed !=0){
        float currProb = laneChangeProb;
        setBrake(0);
        setLCProb(laneChangeProb + ((0.75)* (1-currProb)));
    }
    else if (front<=(vacc + vspeed - 2) && vspeed != 0){
        float currProb = laneChangeProb;
        setLCProb(laneChangeProb + ((0.9)* (1-currProb)));
        setBrake(0);
        setSpeed(1);
    }
    else{
        float currProb = laneChangeProb;
        setLCProb(laneChangeProb - ((0.5)*(currProb)));
        setBrake(1);
    }   
}


void Vehicle::laneChange(){
    vector<int>fs = Get_free_area();
    int lfs = fs[2]; //left free space
    int rfs = fs[3]; //right free space
    int veh_wid = Get_width();
    int veh_len = Get_lenth();
    if (free_area[0]<=1){
    if (lfs > 1){
        llc = true;
    }else{
        llc =false;
    }
    if (rfs > 1){
        rlc = true;
    } else{
        rlc =false;
    }
    } 
    else
    {
        llc =false;
        rlc = false;
    }
        
}

void Vehicle::laneChanger(){
    float a = 0;
    a = static_cast<float>(rand())/(static_cast<float>(RAND_MAX));

    if (Get_speed() != 0 ){
        if (rlc == true){
        if (llc == true){
            if (a < laneChangeProb){
            // (free_area[2]>free_area[3])? y-=1:y+=1;
            bool l = free_area[2]>free_area[3];
            if (a<0.25){
                l = not l;
            }
            if (l==true){
                y-=1;
            } else{
                y+=1;
            }
            x+=1;    
            }
        } else{
            if (a < laneChangeProb){
                        y +=1;
                        x+=1;
        }
        }
        
    } else if (llc == true){
        if (a < laneChangeProb){
            y -=1;
            x+=1;

        }
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
    // calAcceleration();
    if(brake == 0 ){
        decelaration +=2;
        acceleration = 0;
        speed = speed - decelaration;
        if(speed < 0){
            speed = 0;
        }
    }else{
        decelaration = 0;
        acceleration = acceleration + 2;
        if(acceleration >= maxAcceleration){
            acceleration = maxAcceleration;
        }
        speed = acceleration + speed;
        if(speed >= maxspeed){
            speed = maxspeed;
        }
    }
}

//Calculating the accleration of the vehicle based on the previous acceleration and state of breaks
void Vehicle::calAcceleration(){
  acceleration = acceleration + 1;
  if(acceleration >= maxAcceleration){
      acceleration = maxAcceleration;
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

float Vehicle::Get_speed(){
    return speed;
}

float Vehicle::Get_acceleration(){
    return acceleration;
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
    // cout<<"\tVehicle Length: "<<length;
    // cout<<"\tVehicle Width: "<<width;
    cout<<"\nSpeed: "<<speed;
    // cout<<"\tVehicle MaxSpeed: "<<maxspeed;
    cout<<"\nAccelaration: "<<acceleration;
    // cout<<"\tVehicle MaxAcceleration: "<<maxAcceleration;
    cout<<"\nBrake value:"<<brake;
    // cout<<"\tColour: "<<colour;
    cout<<"\nStart Time: "<<start_time;
    cout<<"\nX: "<<x<<" Y: "<<y;
    // cout<<"\nCoverage of the vehicle in the matrix: ";
    vector<tuple<int,int> > cv = Get_coverage();
    for (int i = 0; i<cv.size();i++){
        int firEle = get<0>(cv[i]);
        int secEle = get<1>(cv[i]);
        // cout<<"("<<firEle<<","<<secEle<<") ";
    }
    // cout<<endl;
    cout<<"\nFree Area: ";
    cout<<"Front: "<<free_area[0]<<" Back: "<<free_area[1]<<" Left: "<<free_area[2]<<" Right: "<<free_area[3]<<endl<<endl;
    // cout<<"\nLane Change: "<<" Left: "<<llc<<" Right: "<<rlc<<endl;
    cout<<"Lane Changing Probability: "<<laneChangeProb<<endl;
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
    cout<<"\n Brake Value: "<<brake;
    cout<<"\n Max Speed: "<<maxspeed<<endl;
}

void Vehicle::ShowEssential(){
    cout<<"\n Intial speed: "<<speed;
    cout<<"\n Max Speed: "<<maxspeed;
    cout<<"\n Acceleration: "<<acceleration;
    cout<<"\n Max Acceleration: "<<maxAcceleration;
    cout<<"\n Start Time: "<<start_time;
    cout<<"\n Brake Value: "<<brake;
}

void Vehicle::ShowBasic(){
    cout<<"\n Type: "<<vehicle_type;
    cout<<"\n Colour: "<<colour;
    cout<<"\n Start Time: "<<start_time;
}