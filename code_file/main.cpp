#include "common.hpp"
#include "vehicle.hpp"
#include <ctime>


void ShowRoad (vector<vector<char> > mat);
vector<vector<char> >  initRoad(int mat_wid, int mat_len);
vector<vector<char> > newRoad(vector<vector<char> > road, Vehicle a);
void simulation(Vehicle v, vector<vector<char> > road, int count);
void simulation(vector<Vehicle> vl, vector<vector<char> > road, int count);
int main(int argc, char **argv){
    srand(time(0));
    int mat_len, mat_wid;
    mat_len = stoi(argv[1]);
    mat_wid = stoi(argv[2]);


    vector<Vehicle> vh;
    Vehicle car,car2;
    int count = 20;
    car.setVehicle("car","red",2,2,1,0,0);
    car2.setVehicle("car2","blue",2,2,1,0,2);
    car.posInit(mat_wid);
    car2.posInit(mat_wid);
    vh ={car,car2};
    
    vector<vector<char> > road = initRoad(mat_wid,mat_len);
    simulation(vh,road,count);

return 0;
}

    //intialising the array with null and the ends with '-'
vector<vector<char> >  initRoad(int mat_wid, int mat_len){
    vector<vector< char> > mat(mat_wid);

    for(int i=0; i< mat_wid; i++){
        mat[i] = vector<char>(mat_len);
        for(int j=0; j<mat_len; j++){
            if( i==0 || i == mat_wid - 1){
                mat[i][j] ='-';
            }else{
                mat[i][j] = ' ';
            }
        }
    }
    return mat;
}

//shows the snapshot of the road at particular time
void ShowRoad (vector<vector<char> > arr){
    //intialising the basic value for output
    int l = arr[0].size();
    int w = arr.size();

    for(int i=0; i<w; i++){
        for(int j=0; j<l; j++){
            cout<<arr[i][j]<<" "<<flush;
        }
        cout<<endl<<flush;
    }
}

vector<vector<char> > newRoad(vector<vector<char> > road, Vehicle a){
    char o = a.getType().at(0);
    for(int i=0; i<a.Get_width(); i++){
        for(int j=0; j<a.Get_lenth(); j++){
            road[i+a.Get_y()][j+a.Get_x()] = o;
        }
    }
    return road;
}

void simulation(Vehicle v, vector<vector<char> > road, int count){
    int time = 0;
    vector<vector<char> > updatedRoad;
    while (count>0){
        system("clear");
        if (v.Get_start_time()<=time){
            updatedRoad = newRoad(road,v);
            ShowRoad(updatedRoad);
            v.NextPosition();
        }
        usleep(100000);
        count--;
        time++;
    }
}
void simulation(vector<Vehicle> vl, vector<vector<char> > road, int count){
    int time = 0;
    vector<vector<char> > updatedRoad;
    Vehicle *currVehicle;
    while (count>0){
        system("clear");
        updatedRoad = road;
        for (int i = 0; i<vl.size();i++){
            currVehicle = &vl[i];
            if ((*currVehicle).Get_start_time() <= time){
                updatedRoad = newRoad(updatedRoad,*currVehicle);
                (*currVehicle).NextPosition();
            }
        }
        ShowRoad(updatedRoad);
        // v.NextPosition();
        usleep(100000);
        time++;
        count--;
    }
}