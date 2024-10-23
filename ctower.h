#pragma once
#include "cbullet.h"
class ctower {
    cpoint location;
    cbullet cb;
    int speed, range;
    public:
        ctower() { location = { 0,0,0 };}
        ctower(const cpoint &lo) { 
            location = lo;
            speed = 4;
            range = 10;
        }
        cpoint getLocation() { return location;}
        int getSpeed() { return speed;}
        void setLocation(cpoint nLocation){ location = nLocation;}
        void draw();
        cbullet& getBullet(){
            cb.setCurr(location);
            return cb;
        }
};