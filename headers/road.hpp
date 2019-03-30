#ifndef ROAD_H
#define ROAD_H

#include "common.hpp"
#include "vehicle.hpp"
class Road{
    protected:
        vector<vector<char> > road; //The Road matrix.
        vector<Vehicle> vehicles; //The list of vehicles on the road
        // vector<vector<int> >coverage; //The matrix cell numberseach of the car take. Useful for detecting collisions
        // vector<tuple<int,int> > signals; //List of signals with their Column Numbers. The length of the vector are the number of columns
        vector<tuple<int,vector<int> > > signals; //List of signals of the form tuple<Column numbers,[+24., -20 +....]>
        int sumAllVeh;
    public:
        void getAllVehSize();
        void setAllVehSize();
        void ShowRoad (vector<vector<char> > mat);
        void Init_road(int mat_wid, int mat_len);
        void New_road(Vehicle a);
        vector<vector<char> > New_road(vector<vector<char> > roadMat,Vehicle a);
        void Show_road();
        void Show_road(vector<vector<char> > r);

        void Add_vehicles(Vehicle v);
        void Add_vehicles(vector<Vehicle> v);

        void New_initializer(int mat_len, int mat_wid);
        void Vehicle_intializer(int mat_len, int mat_wid);

        vector<vector<tuple<int,int> > > getAllVertices();

        void Set_signal(int col,vector<int> rel_time);
        bool Signal_behavior(Vehicle v, int time);
        vector<vector<char> > Set_signal_on_road(vector<vector<char> > r,int time);

        void Set_free_area(vector<vector<char> > r, int mat_len, int mat_wid, int time);

        void Simulation(vector<Vehicle> v ,int count); //can be deleted afterwards
        void Simulation(int mat_len, int mat_wid);
        bool Sim_fin();

        void SimulationOpenGL(int mat_len, int mat_wid);
        void LoopSimulation(int mat_len, int mat_wid);

        vector<vector<char> > Get_road();
        vector<Vehicle> Get_vehicles();
        vector<tuple <int,vector<int> > > Get_signals();

        int time;

};


#endif