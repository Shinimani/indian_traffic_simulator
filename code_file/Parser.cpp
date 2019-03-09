#include "Parser.hpp"

vector<vector<string> > Parser(string name){

    ifstream fileopen(name, ios::in);
    string store; 

    //storing the result in an 2-D vector
    vector<vector<string> > res;
    int count = 0; 
        
    while(getline(fileopen,store)){

        store = store.substr(0, store.find("#",0));

        if(store != ""){
            string tempstring;
            res.push_back(vector<string>());

            //checking if the line contains "="
            if(store.find("=",0) != string::npos){

            tempstring = store.substr(0, store.find("=",0)-1);
            res[count].push_back(tempstring);
            store = store.substr(store.find(" ",0) + 2, store.find("\n",0));
            res[count].push_back(store);

            }else{

            tempstring = store.substr(0, store.find(" ",0));
            res[count].push_back(tempstring);
            store = store.substr(store.find(" ",0) + 1, store.find("\n",0));
            res[count].push_back(store);

            }
            count +=1;
        }

        
    }

    // for(int i=0; i<res.size(); i++){
    //     cout<<res[i][0]<<" "<<res[i][1]<<endl;
    // }

    fileopen.close();
    return res;
}


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

//returns the width of the road
int RoadWid(vector<vector<string> > vec){
    int wid = 10;
    int i = 0; 
    int flag = 0;

    while(vec[i][0] != "Road_Width"){
        if(vec[i][0] == "START"){
            flag = 1;
            break;
        }
        i+=1;
    }

    if(flag == 0){
        wid = stoi(vec[i][1]);
    }
    return wid;
}

//Returns the length of the road
int RoadLen(vector<vector<string> > vec){
    int len = 100;
    int i = 0; 
    int flag = 0;

    while(vec[i][0] != "Road_Length"){
        if(vec[i][0] == "START"){
            flag = 1;
            break;
        }
        i+=1;
    }

    if(flag == 0){
        len = stoi(vec[i][1]);
    }
    return len;
}