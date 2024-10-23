#pragma once
#include "ctool.h"
#include <cmath>
#include <vector>

class cpoint {
    private:
        int x,y,c;
    public:
        cpoint(){x = 0; y = 0; c = 0;}
        cpoint(int nX, int nY, int nC) {
            x = nX;
            y = nY;
            c = nC;
        };
        bool operator==(const cpoint &a){
            return x == a.x && y == a.y;
        }
        int distance(const cpoint &a){
            return sqrt((x-a.x)*(x-a.x) +(y-a.y)*(y-a.y));
        }
        int getX(){return x;}
        int getY(){return y;}
        int getC(){return c;}
};