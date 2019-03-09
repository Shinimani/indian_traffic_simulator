#include "vehicle.hpp"
#include "road.hpp"


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
            roadMat[y][x] = o;
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
        for(int j = 0; j<l;j++){
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
    vector<int> all_coverage;
    int restarter = 0;
    for (int i = 0; i< vehicles.size(); i++){
        currVehicle = &vehicles[i];
        bool checker= true;
        while (checker){
            (*currVehicle).posInit(mat_wid);
            (*currVehicle).setCoverage(mat_len);
            vector<int> cv =(*currVehicle).Get_coverage();
            //check if 2 vectors have any common elemnts
            bool retVal = commIn2vectors(all_coverage,cv);
            if (retVal == true){
                all_coverage.insert(all_coverage.end(),cv.begin(),cv.end());
                checker = false;
            }
            if (restarter > 5*vehicles.size()){
                checker = false;
                i = 0;
            }
            restarter++;
        }
    }
}


//Adds Signal to the vector of signals 
void Road::Set_signal(int i){
    signals.push_back(i);
}

bool Road::Signal_behavior(Vehicle v){
    for (int i = 0; i< signals.size();i++){
        int curr_signal = signals[i];
        if (curr_signal - v.Get_x()-v.Get_lenth() == 0){
            return true;
        } else{
            continue;
        }
    }
    return false;
}

vector<vector<char> > Road::Set_signal_on_road(vector<vector<char> > r){
    for(int i = 0; i< r.size();i++){
        for (int j = 0; j<r[0].size(); j++){
            for (int k =0;k<signals.size();k++){
                if (signals[k] == j){
                    r[i][j] = '|';
                }
            }
        }
    }
    return r;
}

//Simulates.
void Road::Simulation(int count, int mat_len){
    int time = 0;
    vector<vector<char> > updatedRoad;
    Vehicle *currVehicle,*currVehicle2;
    while (count>0){
        system("clear");
        updatedRoad = Get_road();
        for (int i = 0; i<vehicles.size();i++){
            currVehicle = &vehicles[i];
                if ((*currVehicle).Get_start_time() <= time){
                (*currVehicle).setCoverage(mat_len);
                updatedRoad = New_road(updatedRoad,*currVehicle);

                if ((*currVehicle).Get_x()-(*currVehicle).Get_lenth() > mat_len){
                    continue;
                }else{
                bool chk = Signal_behavior((*currVehicle));
                if (chk == false){
                    (*currVehicle).NextPosition();
                }
                }
            }   
        }
        //Shows the information of the vehicles
        for (int i = 0; i<vehicles.size();i++){
            currVehicle2 = &vehicles[i];
            (*currVehicle2).ShowVehicle();   
        }
        updatedRoad = Set_signal_on_road(updatedRoad);
        Show_road(updatedRoad);
        usleep(100000);
        time++;
        count--;
    }

}

vector<vector<char> > Road::Get_road(){
    return road;
}

vector<Vehicle> Road::Get_vehicles(){
    return vehicles;
}
vector<int> Road::Get_signals(){
    return signals;
}