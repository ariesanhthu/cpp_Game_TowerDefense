#pragma once
#include "cbullet.h"
#include "Graphic.h"
#include "cenemy.h"
#include <chrono>
#include <cmath>
#include <limits>

class ctower {
private:
    POINT location;
    cbullet bullet;
    bool isShooting;
    float range;
    float cooldownTime; // Thời gian hồi chiêu
    std::chrono::steady_clock::time_point lastShotTime;

    cenemy* enemy = NULL;

public:
    ctower() : range(100.0f), isShooting(false), cooldownTime(500) {}

    void setLocation(const POINT& loc) { location = loc; }
    POINT getLocation() const { return location; }

    float getRange() const { return range; }

    void setShooting(bool flag) {
        isShooting = flag;
    }

    bool getShooting() {
        return isShooting;
    }

    cbullet& getBullet() {
        return bullet;
    }

    void shootAt(const POINT& target) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShotTime).count() >= cooldownTime) {
            bullet.setCurr(location);
            bullet.setTarget(target);
            isShooting = true;
            lastShotTime = now;
        }
    }

    void shootAt(const cenemy* target) {
        auto now = std::chrono::steady_clock::now();
        enemy = const_cast<cenemy*> (target);
        POINT pos = {target->getCurr().x, target->getCurr().y};
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShotTime).count() >= cooldownTime) {
            bullet.setCurr(location);
            bullet.setTarget(pos);
            isShooting = true;
            lastShotTime = now;
        }
    }

    void updateBullet() {
        if (isShooting) {
            bullet.calPath();
            if (!bullet.isActive()) {
                isShooting = false;
                enemy->takeDamage(2);
            }
        }
    }

    void render(HBITMAP towerBitmap, HDC hdc) {
        Graphic::DrawBitmap(towerBitmap, location, hdc);
    }
};



