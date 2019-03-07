#include "common.hpp"
#include <fstream>

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