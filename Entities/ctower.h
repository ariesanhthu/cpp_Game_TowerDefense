#pragma once
#include "cbullet.h"
#include "constant.h"

class ctower {
    cpoint location;
    int range, rate;
    time_point lastShoot;
    public:
        ctower() : ctower({ 0,0,0 }) {};
        ctower(const cpoint &lo) { 
            location = lo;
            range = 50;
            rate = 3;
            lastShoot = chrono::system_clock::now();
        }
        cpoint getLocation() { return location;}
        int getRange() { return range;}
        void setLocation(cpoint nLocation){ location = nLocation;}
        void draw();

        bool canShoot();

        cbullet shoot(cenemy* target);

        /*void fire(cenemy&);*/
};