#ifndef PARSER_H
#define PARSER_H

#include "common.hpp"
#include "vehicle.hpp"
#include <fstream>

vector<vector<string> > Parser(string name);
vector<Vehicle> InitVehicles(vector<vector<string> > parsed);
int RoadWid(vector<vector<string> > vec);
int RoadLen(vector<vector<string> > vec);
Vehicle Search(vector<Vehicle> tvehicle, string name);
vector<Vehicle> GetVehicle(vector<vector<string> > vec, vector<Vehicle> typeVehicle);
vector<int> GetSignalPosition(vector<vector<string> > vec);
int CheckSignal(vector<vector<string> > vec, int id);


vector<Vehicle> InitVehicles(vector<vector<string> > prased);
vector<Vehicle> GetSignals(vector<Vehicle> temp);
vector<Vehicle> GetVehicles(vector<Vehicle> temp);

#endif