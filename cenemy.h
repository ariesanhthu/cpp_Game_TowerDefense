#pragma once
#include "cpoint.h"

class cenemy {
    private:
        int health;
        int speed;
        cpoint currentPosition;
        vector<cpoint> path;
        int index;
    public:
        cenemy();
        cpoint getCurr() {return currentPosition;}
        int getSpeed() { return speed;}
        int getIdex() { return index;}
        void setIdex(int idx) { index = idx;}
        void draw();
};