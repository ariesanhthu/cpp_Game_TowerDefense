#include "cbullet.h"


//void cbullet::calPath(POINT& e){
//    POINT direction;
//    direction.x = e.x - currentPosition.x;
//    direction.y = e.y - currentPosition.y;
//
//    POINT normalizedDirection = direction;
//    normalizedDirection.x = direction.x / abs(direction.x);
//    normalizedDirection.y = direction.y / abs(direction.y);
//
//    currentPosition.x = currentPosition.x + normalizedDirection.x;
//    currentPosition.y = currentPosition.y + normalizedDirection.y;
//}

//void cbullet::draw(char c){
//    ctool::mtx.lock();
//    ctool::GotoXY(currentPosition.getX(), currentPosition.getY());
//    cout << c;
//    ctool::mtx.unlock();
//}