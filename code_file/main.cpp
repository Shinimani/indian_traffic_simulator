#include "common.hpp"
#include "vehicle.hpp"
#include "road.hpp"
#include "Parser.hpp"
#include <ctime>


vector<Vehicle> InitVehicles(vector<vector<string> > prased);
vector<vector<string> > Parser(string name);
vector<Vehicle> GetSignals(vector<Vehicle> temp);
vector<Vehicle> GetVehicles(vector<Vehicle> temp);

int main(int argc, char **argv){
    srand(time(0));
    int mat_len, mat_wid;

    vector<vector<string> > temp = Parser("Mayank.ini");
    vector<Vehicle> vh1 = InitVehicles(temp);

    mat_len = RoadLen(temp);
    mat_wid = RoadWid(temp);
    // int add_l = mat_len/10;
    mat_len+= mat_len/10;
    Road r;
    r.Init_road(mat_wid, mat_len);

    vector<Vehicle> list_vehicle1 = GetVehicle(temp, vh1);

    vector<Vehicle> Signals = GetSignals(list_vehicle1);

    for(int i=0; i<Signals.size(); i++){
        if(Signals[i].GetColour() == "GREEN"){
            r.Set_signal(Signals[i].Get_lenth(), Signals[i].Get_start_time());
        }
    }

    vector<Vehicle> list_vehicle = GetVehicles(list_vehicle1);

    vector<Vehicle> vh;

    vector<int> signaltime = GetSignalPosition(temp);
    
    int count = 100;
     r.Add_vehicles(list_vehicle);
     r.Vehicle_intializer(mat_len,mat_wid);
     r.getAllVehSize();
     r.setAllVehSize();
     r.Simulation(mat_len,mat_wid);
    cout<<mat_len<<" "<<mat_wid<<endl;


return 0;
}


//Getting the list of signals from the earlier parsed list
vector<Vehicle> GetSignals(vector<Vehicle> temp){

    vector<Vehicle> ans;


    for(int i=0; i<temp.size(); i++){
        if(temp[i].getType() == "Signal"){
            ans.push_back(temp[i]);
        }
    }

    return ans;
}


//Getting the list of all the vehicles from the earlier parsed list
vector<Vehicle> GetVehicles(vector<Vehicle> temp){

    vector<Vehicle> ans;

    for(int i=0; i<temp.size(); i++){
        if(temp[i].getType() != "Signal"){
            ans.push_back(temp[i]);
        }
    }

    for(int i=0; i<ans.size(); i++){
        ans[i].ShowOrder();
    }

    return ans;
}