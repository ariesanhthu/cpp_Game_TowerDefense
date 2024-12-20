#pragma once
#include "ctool.h"
#include <cmath>
#include <vector>

class cpoint {
    private:
        int x,y,c;
    public:
        cpoint(){x = 0; y = 0; c = 0;}
        cpoint(int nX, int nY, int nC = 0) {
            x = nX;
            y = nY;
            c = nC;
        };
        bool operator==(const cpoint& a);
        float distance(const cpoint& a);
        int& getX(){return x;}
        int& getY(){return y;}
        int getC(){return c;}

        cpoint operator+(const cpoint&);
        cpoint operator-(const cpoint&);
        cpoint operator*(const int&);
        //cpoint operator/(const float& scale);
        cpoint normalized(float lenght, int speed);
};