#pragma once
#include "cpoint.h"

class cenemy {
    private:
        int health;
        int speed;
        cpoint currentPosition;
        vector<cpoint> path;
        int index = 0;
    public:
        cenemy();
        cpoint& getCurr() {return currentPosition;}
        int getSpeed() { return speed;}
        int getIdex() { return index;}
        void setIdex(int idx) { index = idx;}
        void calPath(vector<cpoint> ePath);
        bool isEnd() {
            return index == path.size() - 1;
        }
        void draw();
};