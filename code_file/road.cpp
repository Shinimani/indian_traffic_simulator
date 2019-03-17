#include "vehicle.hpp"
#include "road.hpp"
#include <algorithm>

vector<vector<tuple<int,int> > > Road::getAllVertices(){
    vector<vector<tuple<int,int> > > ans;
    for ( int i = 0; i < vehicles.size();i++){
        Vehicle currV = vehicles[i];
        ans.push_back(currV.getCorners());
    }
    return ans;
}


void Road::getAllVehSize(){
    int allSize = 0;
    int currSize = vehicles[0].Get_lenth() * vehicles[0].Get_width();
    allSize = currSize;
    Vehicle *currV;
    for (int i = 0; i<vehicles.size(); i++){
        currV  = &vehicles[i];
        currSize = (*currV).Get_lenth() * (*currV).Get_width();
        // allSize+=(((*currV).Get_lenth() * (*currV).Get_width()));
        allSize = (currSize>allSize)? currSize:allSize; 
    }
    sumAllVeh = allSize; 
}
void Road::setAllVehSize(){
    Vehicle *currV;
    float f;
    for (int i = 0; i<vehicles.size(); i++){
        currV  = &vehicles[i];
        (*currV).setSumAllVeh(sumAllVeh);
        f = (*currV).callaneChangeProb();
        (*currV).setLCProb(f);
    }
}

//Initializes the road attribute of the class. 
void Road::Init_road(int mat_wid, int mat_len){
    // road.reserve(mat_wid);

    for(int i=0; i< mat_wid; i++){
        // road[i] = vector<char>(mat_len);
        vector<char> roadRow;
        for(int j=0; j<mat_len; j++){
            if( i==0 || i == mat_wid - 1){
                roadRow.push_back('-');
            }else{
                roadRow.push_back(' ');
            }
        }
        road.push_back(roadRow);
    }
}

//Changes the road attribute with a vehicle
void Road::New_road(Vehicle a){
    char o = a.getType().at(0);
    for(int i=0; i<a.Get_width(); i++){
        for(int j=0; j<a.Get_lenth(); j++){
            road[i+a.Get_y()][j+a.Get_x()] = o;
        }
    }
}
//Returns a new road and takes a road matrix as an input
vector<vector<char> > Road::New_road(vector<vector<char> > roadMat,Vehicle a){
    char o = a.getType().at(0);
    for(int i=0; i<a.Get_width(); i++){
        for(int j=0; j<a.Get_lenth(); j++){
            int x = j+a.Get_x();
            int y = i+a.Get_y();
            if (x>roadMat[0].size()){
                continue;
            }else{
            roadMat[y][x] = o;
            }
        }
    }
    return roadMat;
}

//Prints the road attribute of a class
void Road::Show_road(){
    int w = road.size();
    int l = road[0].size();
    for (int i = 0; i<w;i++){
        for(int j = 0; j<l;j++){
            cout<<road[i][j]<<" "<<flush;
        }
        cout<<endl<<flush;
    }
}
//Prints any road
void Road::Show_road(vector<vector<char> > r){
    int w = r.size();
    int l = r[0].size();
    for (int i = 0; i<w;i++){
        for(int j = (l/10); j<l;j++){
            cout<<r[i][j]<<" "<<flush;
        }
        cout<<endl<<flush;
    }
}

//Adds vehicles to the vector of vehicles
void Road::Add_vehicles(Vehicle v){
    vehicles.push_back(v);
}

void Road::Add_vehicles(vector<Vehicle> v){
    vehicles.insert(vehicles.end(),v.begin(),v.end());
}

void Road::Vehicle_intializer(int mat_len, int mat_wid){
    Vehicle *currVehicle;
    vector<tuple<int,int> > all_coverage;
    int restarter = 0;
    for (int i = 0; i< vehicles.size(); i++){
        currVehicle = &vehicles[i];
        bool checker= true;
        while (checker){
            (*currVehicle).posInit(mat_wid);
            (*currVehicle).setCoverage(mat_len);
            vector<tuple<int,int> > cv =(*currVehicle).Get_coverage();
            int start_time = (*currVehicle).Get_start_time();
            for (int i = 0; i<cv.size();i++){
                tuple<int,int> curEle = cv[i];
                int x = get<0>(curEle) - start_time;
                int y = get<1>(curEle);
                cv[i] = make_tuple(x,y);
            }
            //check if 2 vectors have any common elemnts
            bool retVal = commIn2vectors(all_coverage,cv);
            if (retVal == true){
                all_coverage.insert(all_coverage.end(),cv.begin(),cv.end());
                checker = false;
            }
            if (restarter > 2*vehicles.size()){
                checker = false;
                i = 0;
            }
            restarter++;
        }
    }
}


//Adds Signal to the vector of signals 
void Road::Set_signal(int col,int rel_time){
    tuple<int,int> t = make_tuple(col,rel_time);
    signals.push_back(t);
}

bool Road::Signal_behavior(Vehicle v, int curr_time){
    for (int i = 0; i< signals.size();i++){
        int curr_signal = get<0>(signals[i]);
        int curr_rel_time = get<1>(signals[i]);
        int vehSpeed = v.Get_speed();
        float nextX = vehSpeed + v.Get_x();
        if (curr_signal - v.Get_x()-v.Get_lenth() >= 0 && curr_signal-nextX-v.Get_lenth() <= 0){
            if (curr_time < curr_rel_time){
                return true;
            }else{
                return false;
            }
        } else{
            continue;
        }
    }
    return false;
}

vector<vector<char> > Road::Set_signal_on_road(vector<vector<char> > r, int time){
    for(int i = 0; i< r.size();i++){
        for (int j = 0; j<r[0].size(); j++){
            for (int k =0;k<signals.size();k++){
                int sig_col = get<0>(signals[k]); 
                int sig_rel_time = get<1>(signals[k]);
                if (sig_col == j && sig_rel_time>time){
                    r[i][j] = '|';
                }
            }
        }
    }
    return r;
}


//Free space for each vehicle calculation
void Road::Set_free_area(vector<vector<char> > r,int mat_len,int mat_wid, int time){
    int most_forward = mat_len;
    vector<tuple<int,int> > s= signals;
    for (int k =0;k<s.size();k++){
        tuple<int,int> currSig = s[k];
        if (time < get<1>(currSig)){
            if (get<0>(currSig)<most_forward){
                most_forward = get<0>(currSig);
            }
        }
    }
    vector<Vehicle> *vl;
    vl = &(vehicles);
    vector<tuple<int,int> >all_coverage;
    Vehicle *currV;
    for (int i = 0; i<(*vl).size();i++){
        currV = &(*vl)[i];
        vector<tuple<int,int> > currCov = (*currV).Get_coverage();
        all_coverage.insert(all_coverage.end(),currCov.begin(),currCov.end());
    }
    //all coverage contains all the coverages of the vehicles on the road.
    for (int i = 0;i <(*vl).size();i++){
        currV = &(*vl)[i]; //Each Vehicle

        int front = most_forward-(*currV).Get_x() - (*currV).Get_lenth();
        
        int back = (*currV).Get_x();
        int left = (*currV).Get_y();
        int right = mat_wid - (*currV).Get_y() - (*currV).Get_width(); //wrt to the vehicle
        vector<tuple<int,int> > currCov = (*currV).Get_coverage();
        vector<int>x_cord,y_cord; //x and y coordinates of the curr vehicle's coverage
        for(int k = 0; k<currCov.size();k++){
            int x = get<0>(currCov[k]);
            int y = get<1>(currCov[k]);
            if(find(x_cord.begin(),x_cord.end(),x) != x_cord.end()){
            }else{
                x_cord.push_back(x);
            }
            if(find(y_cord.begin(),y_cord.end(),y) != y_cord.end()){
            }else{
                y_cord.push_back(y);
            }
        }

        for (int j = 0;j<all_coverage.size();j++){
            int x = get<0>(all_coverage[j]);
            int y = get<1>(all_coverage[j]);
            for (int k = 0;k<x_cord.size();k++){
                // if (x >= x_cord[k]-1 && x <= x_cord[k]+1){
                    if (x >= x_cord[k] &&  x <= x_cord[k]+2){
                    //for right
                    int test_right = y - *(max_element(y_cord.begin(),y_cord.end())) - 1;
                    if (test_right>=0 && test_right<right){
                        right = test_right;
                    }

                    //for left
                    int test_left =  *(min_element(y_cord.begin(),y_cord.end())) - y - 1;
                    if (test_left>=0 && test_left<left){
                        left = test_left;
                    }
                }

                // if (y >= y_cord[k]-1 && y <= y_cord[k]+1 (){
                    if (y == y_cord[k]){
                    //for front
                    int test_front = x - *(max_element(x_cord.begin(),x_cord.end())) - 1;
                    if (test_front>=0 && test_front<front){
                        front = test_front;
                    }

                    //for back
                    int test_back =  *(min_element(x_cord.begin(),x_cord.end())) - x - 1;
                    if (test_back>=0 && test_back<back){
                        back = test_back;
                    }
                }
            }

        }
        (*currV).setFreeArea({front,back,left,right});
    }
}

//Simulates.
void Road::Simulation(int mat_len, int mat_wid){
    int time = 0;
    vector<vector<char> > updatedRoad;
    Vehicle *currVehicle,*currVehicle2;
    while (Sim_fin()){
        system("clear");
        updatedRoad = Get_road();
        updatedRoad = Set_signal_on_road(updatedRoad,time);
        for (int i = 0; i<vehicles.size();i++){
            currVehicle = &vehicles[i];
                //Further condiiton checked if only start time is after the current time
                if ((*currVehicle).Get_start_time() <= time){
                //Coverage for the current vehicle set.
                (*currVehicle).setCoverage(mat_len);
                Set_free_area(updatedRoad,mat_len,mat_wid,time);
                //Road updated with the current vehicle
                updatedRoad = New_road(updatedRoad,*currVehicle);
                //If current vehicle moves past the simulation then stop it
                if ((*currVehicle).Get_x()-2*(*currVehicle).Get_lenth() > mat_len){
                    continue;
                }else{
                    Set_free_area(updatedRoad,mat_len,mat_wid,time);
                    (*currVehicle).collisionAvoider(mat_len);
                    (*currVehicle).NextPosition();
                    Set_free_area(updatedRoad,mat_len,mat_wid,time);
                    (*currVehicle).laneChange();
                    (*currVehicle).laneChanger();
                    Set_free_area(updatedRoad,mat_len,mat_wid,time);
                }
            }   
        }
        Set_free_area(updatedRoad, mat_len,mat_wid,time);

        Show_road(updatedRoad);
        usleep(100000);
        time++;
    }

}

void Road::LoopSimulation(int mat_len, int mat_wid){
    
            vector<vector<char> > updatedRoad;
    Vehicle *currVehicle,*currVehicle2;

     system("clear");
        updatedRoad = Get_road();
        updatedRoad = Set_signal_on_road(updatedRoad,time);
        for (int i = 0; i<vehicles.size();i++){
            currVehicle = &vehicles[i];
                //Further condiiton checked if only start time is after the current time
                if ((*currVehicle).Get_start_time() <= time){
                //Coverage for the current vehicle set.
                (*currVehicle).setCoverage(mat_len);
                Set_free_area(updatedRoad,mat_len,mat_wid,time);
                //Road updated with the current vehicle
                updatedRoad = New_road(updatedRoad,*currVehicle);
                //If current vehicle moves past the simulation then stop it
                if ((*currVehicle).Get_x()-(*currVehicle).Get_lenth() > mat_len){
                    continue;
                }else{
                    Set_free_area(updatedRoad,mat_len,mat_wid,time);
                    (*currVehicle).collisionAvoider(mat_len);
                    (*currVehicle).NextPosition();
                    Set_free_area(updatedRoad,mat_len,mat_wid,time);
                    (*currVehicle).laneChange();
                    (*currVehicle).laneChanger();
                    Set_free_area(updatedRoad,mat_len,mat_wid,time);
                }
            }   
        }
        Set_free_area(updatedRoad, mat_len,mat_wid,time);

        usleep(500000);
        time++;
}


//Checks if the simulation must be finished or not
bool Road::Sim_fin(){
    for (int i = 0; i<vehicles.size();i++){
        Vehicle v = vehicles[i];
        if (v.Get_x()-2*v.Get_lenth()>road[0].size()){
            continue;
        }else{
            return true;
        }
    }
    return false;
}

vector<vector<char> > Road::Get_road(){
    return road;
}

vector<Vehicle> Road::Get_vehicles(){
    return vehicles;
}
vector<tuple<int,int> > Road::Get_signals(){
    return signals;
}