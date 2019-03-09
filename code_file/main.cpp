#include "common.hpp"
#include "vehicle.hpp"
#include "road.hpp"
#include <ctime>


// void ShowRoad (vector<vector<char> > mat);
// vector<vector<char> >  initRoad(int mat_wid, int mat_len);
// vector<vector<char> > newRoad(vector<vector<char> > road, Vehicle a);
// void simulation(Vehicle v, vector<vector<char> > road, int count);
// void simulation(vector<Vehicle> vl, vector<vector<char> > road, int count);
// vector<Vehicle> InitVehicles(vector<vector<string> > prased);
// vector<vector<string> > Parser(string name);


int main(int argc, char **argv){
    srand(time(0));
    int mat_len, mat_wid;
    mat_len = stoi(argv[1]);
    mat_wid = stoi(argv[2]);

    // vector<vector<string> > temp = Parser("Mayank.ini");
    // vector<Vehicle> vh = InitVehicles(temp);
    Road r;
    r.Init_road(mat_wid, mat_len);

    vector<Vehicle> vh;
    for(int i=0; i<vh.size(); i++){
        vh[i].posInit(mat_wid);
    }
    Vehicle car,car2;
    // int count = 20;
    car.setVehicle("car","red",2,2,1,3,0,4);
    car2.setVehicle("car2","blue",2,2,1,2,0,4);
    car.posInit(mat_wid);
    car2.posInit(mat_wid);
    vh ={car,car2};
    // simulation(vh,r.Get_road(),count);
    r.Add_vehicles(vh);
    r.Simulation(mat_len);

return 0;
}

// //intialising the array with null and the ends with '-'
// vector<vector<char> >  initRoad(int mat_wid, int mat_len){
//     vector<vector< char> > mat(mat_wid);

//     for(int i=0; i< mat_wid; i++){
//         mat[i] = vector<char>(mat_len);
//         for(int j=0; j<mat_len; j++){
//             if( i==0 || i == mat_wid - 1){
//                 mat[i][j] ='-';
//             }else{
//                 mat[i][j] = ' ';
//             }
//         }
//     }
//     return mat;
// }

// //shows the snapshot of the road at particular time
// void ShowRoad (vector<vector<char> > arr){
//     //intialising the basic value for output
//     int l = arr[0].size();
//     int w = arr.size();

//     for(int i=0; i<w; i++){
//         for(int j=0; j<l; j++){
//             cout<<arr[i][j]<<" "<<flush;
//         }
//         cout<<endl<<flush;
//     }
// }

// vector<vector<char> > newRoad(vector<vector<char> > road, Vehicle a){
//     char o = a.getType().at(0);
//     for(int i=0; i<a.Get_width(); i++){
//         for(int j=0; j<a.Get_lenth(); j++){
//             road[i+a.Get_y()][j+a.Get_x()] = o;
//         }
//     }
//     return road;
// }

// void simulation(Vehicle v, vector<vector<char> > road, int count){
//     int time = 0;
//     vector<vector<char> > updatedRoad;
//     while (count>0){
//         system("clear");
//         if (v.Get_start_time()<=time){
//             updatedRoad = newRoad(road,v);
//             ShowRoad(updatedRoad);
//             v.NextPosition();
//         }
//         usleep(100000);
//         count--;
//         time++;
//     }
// }
// void simulation(vector<Vehicle> vl, vector<vector<char> > road, int count){
//     int time = 0;
//     vector<vector<char> > updatedRoad;
//     Vehicle *currVehicle;
//     while (count>0){
//         system("clear");
//         updatedRoad = road;
//         for (int i = 0; i<vl.size();i++){
//             currVehicle = &vl[i];
//             if ((*currVehicle).Get_start_time() <= time){
//                 updatedRoad = newRoad(updatedRoad,*currVehicle);
//                 (*currVehicle).NextPosition();
//             }
//         }
//         ShowRoad(updatedRoad);
//         // v.NextPosition();
//         usleep(100000);
//         time++;
//         count--;
//     }
// }

vector<Vehicle> InitVehicles(vector<vector<string> > parsed){
    
    int count = 0; 
    int countVehicle = -1;

    vector<Vehicle> vh;

    //default value for all the vehicles
    float dMaxSpeed;
    float dAcceleration;

    Vehicle temp;

    while( parsed[count][0] != "START" ){

        if(parsed[count][0] == "Default_MaxSpeed"){
            dMaxSpeed = stoi(parsed[count][1]);
        }

        if(parsed[count][0] == "Default_Acceleration"){
            dAcceleration = stoi(parsed[count][1]);
        }

        if(parsed[count][0] == "Vehicle_Type"){
            //setting the default value and the type of the vehicle
            vh.push_back(temp);
            countVehicle += 1;
            vh[countVehicle].setType(parsed[count][1]);
            vh[countVehicle].setMaxSpeed(dMaxSpeed);
            vh[countVehicle].setMaxAcc(dAcceleration);
        }else{
            if(parsed[count][0] == "Vehicle_Length"){
                vh[countVehicle].setLength(stoi(parsed[count][1]));
            }
            if(parsed[count][0] == "Vehicle_Width"){
                vh[countVehicle].setWidth(stoi(parsed[count][1]));
            }
            if(parsed[count][0] == "Vehicle_MaxSpeed"){
                vh[countVehicle].setMaxSpeed(stoi(parsed[count][1]));
            }
            if(parsed[count][0] == "Vehicle_Acceleration"){
                vh[countVehicle].setMaxAcc(stoi(parsed[count][1]));
            } 
        }

        count += 1;
    }

    return vh;

}