#pragma once
#include "cpoint.h"

class cbullet {
    private:
        cpoint curr;
        int speed;
        int dame;

    public:
        cbullet();
        cpoint getCurr() { return curr; }
        int getDame() { return dame;}
        cpoint calPath();
        void draw();
};