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
            store = store.substr(store.find(" ",0) + 3, store.find("\n",0));
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
    //     cout<<res[i][0]<<" "<<res[i][1]<<"\n";
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
            //cout<<parsed[count][1]<<endl;
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
                vh[countVehicle].setAcceleration(stoi(parsed[count][1]));
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


//returns the positions of the road signals
vector<int> GetSignalPosition(vector<vector<string> > vec){

    vector<int> ans;
    int i=0; 

    while(vec[i][0] != "START"){
        if(vec[i][0] == "Road_Signal"){
            ans.push_back(stoi(vec[i][1]));
        }
        i+=1;
    }

    // for(int j=0; j<ans.size(); j++){
    //     cout<<ans[j]<<endl;
    // }
    return ans;

}




//Get the different types of vehicles from 2D input vector
vector<Vehicle> GetVehicle(vector<vector<string> > vec, vector<Vehicle> typeVehicle){


    //for generating random number
    srand(time(0));

    int count = 0;
    vector<Vehicle> vh;

    int time = -1;


    for(int i=0; i<vec.size(); i++){
       Vehicle temp = Search(typeVehicle, vec[i][0]);

       if(vec[i][0].find("START") != string::npos){
           time = 0;
       }

        if(temp.getType() != "null"){
            vh.push_back(temp);
            vh[count].setColour(vec[i][1]);
            int randspeed = rand()%(int)(vh[count].GetMaxSpeed() + 1);
            int randAccleration = rand()%(int)(vh[count].GetMaxAccleration() + 1);
            vh[count].setSpeed(randspeed);
            vh[count].setAcceleration(randAccleration);
            vh[count].setBrake(1);
            vh[count].setStartTime(time);

            //updating the time that initialises the start time of the car
            time += 1;
            count += 1;
        }

        if(vec[i][0].find("Pass") != string::npos){
            //incrementing the start time further
            time = time + stoi(vec[i][1]) - 1 ;
            //cout<<time<<endl;
            
        }

        if(vec[i][0].find("@") != string::npos ){
            int id = stoi(vec[i][0].substr(1));

            //checks if the signal exist or not
            if(CheckSignal(vec, id) > 0){
                vh.push_back(temp);
                vh[count].setType("Signal");//Tells that it is Signal not the car
                vh[count].setColour(vec[i][1]);//stores the colour of the signal to determine the stored time is release time or not
                vh[count].setStartTime(time);//start time stores the release time of the signal
                vh[count].setLength(id); //length stores the position of the Signal
            
            }
            //cout<<time<<endl;

            // if(vec[i][1] == "GREEN"){
            //     vh[count].setSpeed(0);
            // }else{
            //     vh[count].setSpeed(1);
            // }

            count += 1;
            //cout<<vec[i][0]<<" "<<vec[i][1]<<endl;
        }
    }

    // for(int j=0; j<vh.size(); j++){
    //    vh[j].ShowBasic();
    //    cout<<endl<<j<<" "<< vh.size()<<endl;
    // }

    return vh;

}




//returns the vehicle if the type matches with the given type
Vehicle Search(vector<Vehicle> tvehicle, string name){

    Vehicle temp ;
    //if no vehicle of particular if found then vehicle of type null is returned
    temp.setType("null");


    for(int i=0; i<tvehicle.size(); i++){

        //checks if the particular type of the vehicle is there or not
        if(tvehicle[i].getType().find(name) != string::npos){
            temp = tvehicle[i];
        }
    }

    return temp;
}

int CheckSignal(vector<vector<string> > vec, int id){
    int i=0;
    int ans = -1;
    
    while(vec[i][0] != "START"){
        if(vec[i][0] == "Road_Signal"){
            int temp = stoi(vec[i][1]);
            if(temp == id){
                ans = 1;
            }
        }

        i+=1;
    }

    return ans;
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

    return ans;
}