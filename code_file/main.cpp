#include "common.hpp"
#include "vehicle.hpp"
#include <ctime>


void ShowRoad (vector<vector<char> > mat);
vector<vector<char> >  initRoad(int mat_wid, int mat_len);
vector<vector<char> > newRoad(vector<vector<char> > road, Vehicle a);


int main(int argc, char **argv){
    srand(time(0));
    int mat_len, mat_wid;
    mat_len = stoi(argv[1]);
    mat_wid = stoi(argv[2]);


    vector<Vehicle> vh;
    int count = 20;

    while(count > 0){
        //clears the screen so that continuous output looks like an animation
        system("clear");
        //intializing the 2D road for positioning the vehicles on it. Erases the previous instance of the vehicle
        vector<vector<char> > mat = initRoad(mat_wid, mat_len);
        mat = newRoad(mat,car);
        ShowRoad(mat);
        //calculating the next cooridinates of the vehicle
        car.NextPosition();

        //waiting time in micro seconds
        usleep(100000);
        count -=1;
    }   

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