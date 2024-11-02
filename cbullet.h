#pragma once
#include "cpoint.h"
#include "cenemy.h"

class cbullet {
    private:
        cpoint currentPosition;
        int speed;
        int dame;
        //vector<cpoint> path;
    public:
        cbullet(){
            speed = 6;
            dame = 1;
        };
        void setCurr(const cpoint &p) { currentPosition = p; }
        cpoint getCurr() { return currentPosition; }
        int getDame() { return dame;}
        int getSpeed() { return speed;}
        void calPath(cpoint& e);
        void draw(char);
};
