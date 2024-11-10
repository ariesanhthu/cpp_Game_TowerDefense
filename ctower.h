#pragma once
#include "cbullet.h"

class ctower {
    cpoint location;
    cbullet cb;
    int speed, range;
    public:
        ctower() : ctower({ 0,0,0 }) {};
        ctower(const cpoint &lo) { 
            location = lo;
            speed = 1;
            range = 40;
        }
        cpoint getLocation() { return location;}
        int getSpeed() { return speed;}
        int getRange() { return range;}
        void setLocation(cpoint nLocation){ location = nLocation;}
        void draw();
        cbullet& getBullet() {
            cb.setCurr(location);
            return cb;
        };

        /*void fire(cenemy&);*/
};