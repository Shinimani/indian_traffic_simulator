#ifndef ROAD_H
#define ROAD_H

#include "common.hpp"
#include "vehicle.hpp"
class Road{
    protected:
        vector<vector<char> > road; //The Road matrix.
        vector<Vehicle> vehicles; //The list of vehicles on the road
        vector<vector<int> >coverage; //The matrix cell numberseach of the car take. Useful for detecting collisions
        vector<int> signals; //List of signals with their Column Numbers. The length of the vector are the number of columns

    public:
        void ShowRoad (vector<vector<char> > mat);
        void Init_road(int mat_wid, int mat_len);
        void New_road(Vehicle a);

        vector<vector<char> > Get_road();
};


#endif