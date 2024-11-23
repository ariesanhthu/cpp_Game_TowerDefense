#pragma once
#include "cpoint.h"

class cenemy {
    protected:
        int health;
        int speed;
        cpoint currentPosition;
        vector<cpoint> path;
        int index = 0;
    public:
        cenemy();
        cpoint& getCurr() {return currentPosition;}
        int getSpeed() { return speed;}
        int getHealth() { return health;}
        int getIdex() { return index;}
        void setIdex(int idx) { index = idx;}
        void calPath(vector<cpoint> ePath);
        bool isEnd() {
            return index == path.size() - 1;
        }
        void hit(int dame) { health -= dame; }

        virtual void update();

        void draw();

        virtual void writeFile(ofstream&);
        virtual void readFile(ifstream&);
};