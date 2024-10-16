#pragma once
#include "cpoint.h"
class cenemy {
    private:
        int _speed;
        cpoint _start, _end, _curr;
        // Array contains the path for the cenemy object from _start to _end
        cpoint _p[cpoint::MAP_SIZE * cpoint::MAP_SIZE];
        // Data for pathfinding for cenemy objects
        int dd[4], dc[4];

    public:
        cenemy();
        cenemy(cpoint tstart, cpoint tend, cpoint tcurr);
        cpoint* getP() { return _p; }
        cpoint getStart() { return _start; }
        cpoint getEnd() { return _end; }
        int getSpeed() { return _speed; }
        cpoint getCurr() { return _curr; }
        void setSpeed(int tspeed) {
            if (tspeed > 0 && tspeed < 10) _speed = tspeed;
        }
        void setStart(cpoint tstart) {
            // if (...) 
                _start = tstart;
        }
        void setEnd(cpoint tend) {
            // if (...) 
                _end = tend;
        }
        void setCurr(cpoint tcurr) {
            // if (...) 
                _curr = tcurr;
        }
        void findPath(cpoint[][cpoint::MAP_SIZE], cpoint, cpoint);

    private:
        void calcPath(int[][cpoint::MAP_SIZE], int, cpoint, cpoint, int=1);
};