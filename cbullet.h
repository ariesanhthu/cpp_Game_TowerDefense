#pragma once
#include "cpoint.h"

class cbullet {
    private:
        cpoint currentPosition;
        int speed;
        int dame;
        cpoint path[2];
    public:
        cbullet(){
            speed = 6;
            dame = 1;
        };
        void setCurr(const cpoint &p) { currentPosition = p; }
        cpoint getCurr() { return currentPosition; }
        int getDame() { return dame;}
        int getSpeed() { return speed;}
        void calPath(const cpoint &e);
        bool isHit(){
            return currentPosition == path[1];
        }
        void draw();
};
