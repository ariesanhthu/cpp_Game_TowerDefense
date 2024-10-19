#pragma once
#include "cpoint.h"
class cenemy {
    private:
        int health;
        int speed;
        cpoint curr;
        vector<cpoint> path;
        int idx;
    public:
        cenemy();
        cpoint getCurr();
        int getSpeed();
        int getIdex();
        void setIdex();
        void draw();
};