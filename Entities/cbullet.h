#pragma once
#include "cenemy.h"

class cbullet {
private:
    POINT currentPosition;
    int speed;
    int dame;

public:
    cbullet(){
        speed = 6;
        dame = 1;
    };
    void setCurr(const POINT &p) { currentPosition = p; }
    POINT getCurr() { return currentPosition; }
    int getDame() { return dame;}
    int getSpeed() { return speed;}

    void calPath(POINT& e);

    void handleInput();
    void render();
};
