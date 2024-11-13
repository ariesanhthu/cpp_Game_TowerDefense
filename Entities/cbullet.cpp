#include "cbullet.h"
//cbullet::cbullet() {
//
//} 

void cbullet::calPath(cpoint& e){
    cpoint derection = e - currentPosition;
    cpoint normalizedDirection = derection.normalized();
    currentPosition = currentPosition + normalizedDirection;
    /*ctool::mtx.lock();
    ctool::GotoXY(21, 21);
    cout << e.getX() << " " << e.getY();
    ctool::mtx.unlock();*/
}

void cbullet::draw(char c){
    ctool::mtx.lock();
    ctool::GotoXY(currentPosition.getX(), currentPosition.getY());
    cout << c;
    ctool::mtx.unlock();
}