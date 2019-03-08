#include "vehicle.hpp"
#include "road.hpp"

void Road::Init_road(int mat_wid, int mat_len){
    road.reserve(mat_wid);
    for(int i=0; i< mat_wid; i++){
        road[i] = vector<char>(mat_len);
        for(int j=0; j<mat_len; j++){
            if( i==0 || i == mat_wid - 1){
                road[i][j] ='-';
            }else{
                road[i][j] = ' ';
            }
        }
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

vector<vector<char> > Road::Get_road(){
    return road;
}