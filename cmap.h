#pragma once
#include "ctool.h"
#include "cenemy.h"
#include "ctower.h"
#include <vector>

class cmap {
    private:
        //const int w = 300,h = 170;
        vector<vector<int>> map;
        vector<cpoint> tPlaces;
        vector<vector<cpoint>> ePath;
       /* vector<vector<int>> directionX;
        vector<vector<int>> directionY;*/
        int nEnemy;
        int mapCode = 0;
    public:
        //cmap();
        void readMap(int);
        void drawMap();
        vector<cpoint> getTPlaces() { return tPlaces;}
        vector<cpoint> getEPath(int i) { return ePath[i];}
        /*vector<int> getDirectionX(int i) { return directionX[i];}
        vector<int> getDirectionY(int i) { return directionY[i];}*/
        int getMapCode() { return mapCode;}
        int getEnemy() { return nEnemy;}
};