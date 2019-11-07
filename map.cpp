#include <fstream>
#include <iostream>
#include "map.h"
using namespace std;

void mapArray::set_map(int map_arr[][10],int level,int &a,int &b,int &goalCount){
    ifstream input;
    if(level==1){
        input.open("./mapFile/level1.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
        
    }
    else if(level==2){
        input.open("./mapFile/level2.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }
    else if(level==3){
        input.open("./mapFile/level3.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }
    if(level==4){
        input.open("./mapFile/level4.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }
    if(level==5){
        input.open("./mapFile/level5.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }
    if(level==6){
        input.open("./mapFile/level6.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }
    // if(level==7){
    //     input.open("./mapFile/level7.txt");
    //     for(int i=0;i<10;i++){
    //         for(int j=0;j<10;j++){
    //             input>>map_arr[i][j];
    //         }
    //     }
    //     input>>goalCount>>a>>b;
    // }
    if(level==7){
        input.open("./mapFile/level8.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }
    if(level==8){
        input.open("./mapFile/level9.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }
    if(level==9){
        input.open("./mapFile/level10.txt");
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                input>>map_arr[i][j];
            }
        }
        input>>goalCount>>a>>b;
    }

}

