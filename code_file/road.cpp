#include "vehicle.hpp"
#include "road.hpp"

void Road::Init_road(int mat_wid, int mat_len){
    // road.reserve(mat_wid);
    cout<<"Ok"<<endl;
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

void Road::New_road(Vehicle a){
    char o = a.getType().at(0);
    for(int i=0; i<a.Get_width(); i++){
        for(int j=0; j<a.Get_lenth(); j++){
            road[i+a.Get_y()][j+a.Get_x()] = o;
        }
    }
}

vector<vector<char> > Road::New_road(vector<vector<char> > roadMat,Vehicle a){
    char o = a.getType().at(0);
    for(int i=0; i<a.Get_width(); i++){
        for(int j=0; j<a.Get_lenth(); j++){
            roadMat[i+a.Get_y()][j+a.Get_x()] = o;
        }
    }
    return roadMat;
}


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

void Road::Simulation(vector<Vehicle> v,int count){
    int time = 0;
    vector<vector<char> > updatedRoad;
    Vehicle *currVehicle;
    while (count>0){
        system("clear");
        updatedRoad = Get_road();
        for (int i = 0; i<v.size();i++){
            currVehicle = &v[i];
            if ((*currVehicle).Get_start_time() <= time){
                updatedRoad = New_road(updatedRoad,*currVehicle);
                (*currVehicle).NextPosition();
            }
        }
        Show_road(updatedRoad);
        // v.NextPosition();
        usleep(100000);
        time++;
        count--;
    }

}


vector<vector<char> > Road::Get_road(){
    return road;
}