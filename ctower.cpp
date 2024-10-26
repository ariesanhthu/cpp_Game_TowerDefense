#include "ctower.h"


void ctower::fire(cenemy e) {
    cpoint eCurr = e.getCurr();
    if (location.distance(eCurr) < range) {

    }
}

void ctower::draw(){
    ctool::mtx.lock();
    ctool::GotoXY(location.getX(), location.getY());
    cout << "T";
    ctool::mtx.unlock();
}