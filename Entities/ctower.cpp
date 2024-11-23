#include "ctower.h"

bool ctower::canShoot() {
    time_point now = chrono::system_clock::now();
    if (micro(1000000 * 4 / rate) > micro_cast(now - lastShoot)) {
        lastShoot = chrono::system_clock::now();
        return true;
    }
    return false;
}

cbullet ctower::shoot(cenemy* target) {
    lastShoot = chrono::system_clock::now();
    return cbullet(location, target);
};

void ctower::draw(){
    ctool::mtx.lock();
    ctool::GotoXY(location.getX(), location.getY());
    cout << "T";
    ctool::mtx.unlock();
}