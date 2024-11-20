#include "cbullet.h"
cbullet::cbullet() {
    speed = 6;
    dame = 1;
} 

cbullet::cbullet(cpoint pos, cenemy* nTarget, int nSpeed, int nDame) {
    currentPosition = pos;
    speed = nSpeed;
    dame = nDame;
    target = nTarget;
}

cbullet::cbullet(cpoint pos, cenemy* nTarget) : cbullet() {
    currentPosition = pos;
    target = nTarget;
}

void cbullet::update(){
    cpoint e = target->getCurr();
    
    cpoint derection = e - currentPosition;
    cpoint normalizedDirection = derection.normalized();
    this->currentPosition = this->currentPosition + normalizedDirection * speed;
    //cout << e.getX() << " " << e.getY() << " ";
}

cenemy* cbullet::checkCollision() {
    if (currentPosition.distance(target->getCurr()) < speed)
        return target;
    return NULL;
}

void cbullet::draw(char c){
    ctool::mtx.lock();
    ctool::GotoXY(currentPosition.getX(), currentPosition.getY());
    cout << c;
    ctool::mtx.unlock();
}