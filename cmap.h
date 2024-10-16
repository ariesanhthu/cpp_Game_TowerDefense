#pragma once
#include "ctool.h"
#include "cenemy.h"
#include "ctower.h"

class cmap {
    cenemy _ce;
    ctower _ctw;
    // Map matrix _m
    cpoint _m[cpoint::MAP_SIZE][cpoint::MAP_SIZE];
    public:
        cmap();
        //-1 là tường, 0 là trống, 1 là Tower
        void resetMapData();
        void makeMapData();
        void drawMap();
        cenemy& getEnemy() { return _ce; }
        ctower& getTower() { return _ctw; }
};