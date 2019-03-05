#include "common.hpp"
#include "vehicle.hpp"

void ShowRoad (vector<vector<char> > mat);
vector<vector<char> >  initRoad(int mat_wid, int mat_len);

int main(int argc, char **argv){

    int mat_len, mat_wid;
    mat_len = stoi(argv[1]);
    mat_wid = stoi(argv[2]);


    Vehicle car;
    car.setBasicAttributes(2,2,0,1);
    car.setColour("Red");
    car.setType("Car");
    car.setPosition(0.0, 1.0);
    int count = 20;

    while(count > 0){
        //clears the screen so that continuous output looks like an animation
        system("clear");
        //intializing the 2D road for positioning the vehicles on it.
        vector<vector<char> > mat = initRoad(mat_wid, mat_len);
        for(int i=0; i<car.Get_width(); i++){
            for(int j=0; j<car.Get_lenth(); j++){
                mat[i+car.Get_y()][j+car.Get_x()] = 'b';
            }
        }
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
    //assigning the len and the width of the road to the variables
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
