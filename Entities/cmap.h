#pragma once
#include "ctool.h"
#include "cenemy.h"
#include "ctower.h"
#include <vector>

class cmap {
    private:
        //vector<vector<int>> map;
        vector<cpoint> tPlaces;
        vector<vector<cpoint>> ePath;
        int nEnemy[4]{0,0,0,0};
        int mapCode = 0;
    public:
        void readMap(int);
        void drawMap();
        vector<cpoint> getTPlaces() { return tPlaces;}
        int getNumOfPath() { return ePath.size(); }
        vector<cpoint> getEPath(int i) { return ePath[i]; }
        int getMapCode() { return mapCode;}
        int getEnemy(int i) { return nEnemy[i];}
};