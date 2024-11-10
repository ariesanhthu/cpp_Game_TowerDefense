#pragma once
#include "cbullet.h"
class ctower {
    cpoint location;
    cbullet cb;
    int speed;
    public:
        ctower() { location = { 0,0,0 };}
        cpoint getLocation() { return location;}
        int getSpeed() { return speed;}
        void draw();
};