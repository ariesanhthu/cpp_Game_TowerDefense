#pragma once
#include "ctool.h"
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
        int getX(){return x;}
        int getY(){return y;}
        int getC(){return c;}
};