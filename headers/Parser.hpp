#ifndef PARSER_H
#define PARSER_H

#include "common.hpp"
#include "vehicle.hpp"
#include <fstream>

vector<vector<string> > Parser(string name);
vector<Vehicle> InitVehicles(vector<vector<string> > parsed);
int RoadWid(vector<vector<string> > vec);
int RoadLen(vector<vector<string> > vec);

#endif