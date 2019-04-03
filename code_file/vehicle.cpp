#include "vehicle.hpp"

//Here we will add functions of the vehicle class

void Vehicle::setCorners(){
    vector<tuple<int,int> >cov  = coverage;
    int minX = 0,minY = 0,maxX = 0,maxY = 0;
    int x,y;
    for(int i = 0; i<cov.size(); i++){
        x = get<0>(cov[i]);
        y = get<1>(cov[i]);
        if (i == 0){
            minX = x;
            maxX = x;
            minY = y;
            maxY = y;
        }else{
            if (x > maxX){
                maxX = x;
            }
            if (x <minX){
                minX = x;
            }
            if (y > maxY){
                maxY = y;
            }
            if (y <minY){
                minY = y;
            }
        }
    }
    vector<tuple<int,int> > al = {make_tuple(minX,maxY),make_tuple(maxX,maxY),make_tuple(maxX,minY),make_tuple(minX,minY)};
    corners = al;
}

vector<tuple<int,int> >Vehicle::getCorners(){
    return corners;
}

void Vehicle::ShowCorners(){

                int x1 = get<0>(corners[0])*50;
                int y1 = get<1>(corners[0])*20+10;

                int x2 = get<0>(corners[1])*50;
                int y2 = get<1>(corners[1])*20+10;

                int x3 = get<0>(corners[2])*50;
                int y3 = get<1>(corners[2])*20;

                int x4 = get<0>(corners[3])*50;
                int y4 = get<1>(corners[3])*20;

                float sq_x = (x1+x2)/2;
                float sq_y = (y1+3*y4)/4;

                float tr_x = (3*x2+x1)/4;
                float tr_y = (3*y4+y1)/4;

                cout<<x1<<" "<<y1<<endl;
                cout<<x2<<" "<<y2<<endl;
                cout<<x3<<" "<<y3<<endl;
                cout<<x4<<" "<<y4<<endl;
                cout<<sq_x<<" "<<sq_y<<endl;
                cout<<tr_x<<" "<<tr_y<<endl;
}


//Intialising the position and specification of the vehicle. 
void Vehicle::setVehicle(string type, string colour, int len, int wid, int iSpeed, int start_time, int ac, int maxSpeed){
    setType(type);
    setBasicAttributes(len, wid, ac, iSpeed);
    setMaxSpeed(maxSpeed);
    setColour(colour);
    setStartTime(start_time);
    brake = 0;
    setCorners();
    // cout<<brake<<endl;
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
    float lcp = (1 - ((0.75)*float(l*w)/sumAllVeh))*0.5;
    //(1-(lcp*2))*(4/3) gives (l*w)/sumAllVeh
    // laneChangeProb = lcp;
    return laneChangeProb;
}

void Vehicle::setBasicAttributes(int l, int w, int acc, float initSpeed){
    length = l;
    width = w;
    acceleration = acc;
    brake = 1;
    speed = initSpeed;
    setCorners();
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

void Vehicle::setCoreFreeArea(vector<int> fa){
    core_free_area = fa;   
}

void Vehicle::collisionAvoider(int mat_len){
    vector<int> fs = Get_free_area();
    vector<int> cfs = Get_core_free_area();
    int core_front = cfs[0];
    int front = fs[0];
    int vspeed = Get_speed();
    int currX = Get_x();
    int vacc = Get_acceleration();
    int dec = decelaration;
    int signalOrCar;
    if (infSignal == false){
        signalOrCar = 1;
    }else{
        signalOrCar = (Get_lenth()* Get_width())/2;
    }
    //Brake 1 is forward accelaration. Brake 0 is retardation
    //(1-(lcp*2))*(4/3) gives (l*w)/sumAllVeh
    float frac = Get_lenth()*Get_width()/sumAllVeh;
    float currProb = laneChangeProb;
    if (mat_len - Get_x()<=3*Get_lenth()){
        setBrake(1);
        setLCProb(laneChangeProb - ((0.9999)* (1-currProb)));
    }
    else if(Get_x()<=1){
        setBrake(1);
    }else if (front < signalOrCar+1){
        if (core_front<signalOrCar+2){
            setBrake(0);
            setSpeed(0);
            setLCProb(laneChangeProb + ((0.75)* (1-currProb)));
        }else if(core_front>(vspeed+vacc+2+signalOrCar)){
            setBrake(1);
        }else{
            setSpeed(1);
            setBrake(0);
            setLCProb(laneChangeProb - ((0.9)* (1-currProb)));
        }
    }
    else if(front>(vacc + vspeed + 2-dec+signalOrCar) && front<2*(vacc + vspeed + 2-dec+signalOrCar)){
        setBrake(0);
        setLCProb(laneChangeProb + ((0.25)* (1-currProb)));
    }
    else if (front<=(vacc + vspeed + 2-dec+signalOrCar) ){
        setLCProb(laneChangeProb + ((0.50)* (1-currProb)));
        setBrake(0);
        setSpeed(front/2);
        // setSpeed(0);
    }
    else if(core_front>(vacc + vspeed + 2-dec+signalOrCar) && core_front<2*(vacc + vspeed + 2-dec+signalOrCar)){
        setBrake(0);
        setLCProb(laneChangeProb + ((0.25)* (1-currProb)));
    }
    else if (core_front<=(vacc + vspeed + 2-dec+signalOrCar) ){
        setLCProb(laneChangeProb + ((0.55)* (1-currProb)));
        setBrake(0);
        setSpeed(core_front/2);
        // setSpeed(0);
    }
    else{
        setLCProb(laneChangeProb - ((0.9)*(currProb)));
        setBrake(1);
    }   
}


void Vehicle::laneChange(){
    vector<int>fs = Get_free_area();
    int lfs = fs[2]; //left free space
    int rfs = fs[3]; //right free space
    int veh_wid = Get_width();
    int veh_len = Get_lenth();
    int signalOrCar;
    if (infSignal == false){
        signalOrCar = 1;
    }else{
        signalOrCar = Get_lenth();
    }
    if (core_free_area[0]>=signalOrCar){
    if (lfs >= 1){
        llc = true;
    }else{
        llc =false;
    }
    if (rfs >= 1){
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
    int signalOrCar;
    if (infSignal == false){
        signalOrCar = 1;
    }else{
        signalOrCar = Get_lenth();
    }
    if (Get_speed() != 0 || core_free_area[0]>= signalOrCar){
        if (rlc == true){
        if (llc == true){
            if (a < laneChangeProb){
            // (free_area[2]>free_area[3])? y-=1:y+=1;
            bool l = free_area[2]>free_area[3];
            if (a<0.35){
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
    setCorners();
    x = speed + x;
    calSpeed();

}

//Calculating the speed of the vehicle
void Vehicle::calSpeed(){
    // calAcceleration();
    if(brake == 0 ){
        decelaration +=1;
        acceleration = 0;
        speed = speed - decelaration;
        if(speed < 0){
            speed = 0;
        }
    }else{
        decelaration = 0;
        speed = acceleration + speed;
        if(speed >= maxspeed){
            speed = maxspeed;
        }
        acceleration = acceleration + 1;
        if(acceleration >= maxAcceleration){
            acceleration = maxAcceleration;
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

vector<int> Vehicle::Get_core_free_area(){
    return core_free_area;
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
    cout<<"Core Front: "<<core_free_area[0]<<" Front: "<<free_area[0]<<" Back: "<<free_area[1]<<" Left: "<<free_area[2]<<" Right: "<<free_area[3]<<endl<<endl;
    // cout<<"\nLane Change: "<<" Left: "<<llc<<" Right: "<<rlc<<endl;
    cout<<"Lane Changing Probability: "<<laneChangeProb<<endl;
    cout<<"\nCorners of the vehicle in the matrix: ";
    // vector<tuple<int,int> > corners = cv;
    for (int i = 0; i<corners.size();i++){
        int firEle2 = get<0>(corners[i]);
        int secEle2 = get<1>(corners[i]);
        cout<<"("<<firEle2<<","<<secEle2<<") ";
    }
    cout<<endl;
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