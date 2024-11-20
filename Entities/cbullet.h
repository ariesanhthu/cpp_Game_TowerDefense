#pragma once
#include "cpoint.h"
#include "cenemy.h"

class cbullet {
    private:
        cpoint currentPosition;
        int speed;
        int dame;
        cenemy* target;
    public:
        cbullet();

        cbullet(cpoint pos, cenemy* nTarget, int nSpeed, int nDame);
        cbullet(cpoint pos, cenemy* nTarget);

        void setCurr(const cpoint &p) { currentPosition = p; }
        cpoint getCurr() { return currentPosition; }
        void setTarget(cenemy* nTarget) { target = nTarget; }
        cenemy* getTarget() { return target; }
        int getDame() { return dame;}
        int getSpeed() { return speed;}

        void update();

        cenemy* checkCollision();

        void draw(char);
};
