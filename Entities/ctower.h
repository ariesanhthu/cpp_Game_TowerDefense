#pragma once
#include "cbullet.h"
#include "constant.h"

class ctower {
    protected:
        cpoint location;
        int range, rate;
        time_point lastShoot;
    public:
        ctower() : ctower({ 0,0,0 }) {};
        ctower(const cpoint &lo) { 
            location = lo;
            range = 50;
            rate = 1;
            lastShoot = chrono::system_clock::now();
        }
        cpoint getLocation() { return location;}
        int getRange() { return range;}
        void setLocation(cpoint nLocation){ location = nLocation;}
        void draw();

        bool canShoot();

        virtual cbullet shoot(cenemy* target);

        /*void fire(cenemy&);*/
};