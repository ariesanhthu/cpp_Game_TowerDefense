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
        int mapCode;
    public:
        cmap();
        void readMap(int);
        void drawMap();
        vector<cpoint> getTPlaces() { return tPlaces;}
        vector<cpoint> getEPath(int i) { return ePath[i];}
        int getMapCode() { return mapCode;}
};