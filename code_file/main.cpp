#include "common.hpp"
#include "vehicle.hpp"
#include "road.hpp"
#include "Parser.hpp"
#include <ctime>


vector<Vehicle> InitVehicles(vector<vector<string> > prased);
vector<vector<string> > Parser(string name);

int main(int argc, char **argv){
    srand(time(0));
    int mat_len, mat_wid;

    vector<vector<string> > temp = Parser("Mayank.ini");
    vector<Vehicle> vh1 = InitVehicles(temp);

    mat_len = RoadLen(temp);
    mat_wid = RoadWid(temp);

    Road r;
    r.Init_road(mat_wid, mat_len);

    vector<Vehicle> list_vehicle = GetVehicle(temp, vh1);

    vector<Vehicle> vh;
    
    // for(int i=0; i<list_vehicle.size(); i++){
    //     list_vehicle[i].posInit(mat_wid);
    // }
     Vehicle car,car2;
    int count = 40;
    car.setVehicle("car","red",2,2,1,0,0.5,2);
    // car2.setVehicle("car2","blue",2,2,1,2,0.6,3);
    // vh ={car,car2};
    list_vehicle.push_back(car);
    r.Add_vehicles(list_vehicle);
    r.Vehicle_intializer(mat_len,mat_wid);
    r.Set_signal(10);
    r.Simulation(count,mat_len);

    cout<<mat_len<<" "<<mat_wid<<endl;


return 0;
}
