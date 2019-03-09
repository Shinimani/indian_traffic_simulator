#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <time.h>  
#include <tuple>
using namespace std;

template<typename T>
bool commIn2vectors(vector<T> a, vector<T> b){
    for (int i = 0; i<a.size(); i++){
        for (int j = 0; j<b.size();j++){
            if (a[i] == b[j]){
                return false;
                break;
            }else{
                continue;
            }
        }
    }
    return true;
}

#endif