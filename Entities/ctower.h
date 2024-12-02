#pragma once
#include "cbullet.h"
#include "Graphic.h"

class ctower {
private:
    POINT location;
    cbullet cb;
    int speed, range;
public:
    ctower() {};
    ctower(const POINT& lo) {
        location = lo;
        speed = 1;
        range = 40;
    }

    POINT getLocation() { return location;}
    int getSpeed() { return speed;}
    int getRange() { return range;}
    void setLocation(POINT nLocation) { location = nLocation;}

    cbullet& getBullet() {
        cb.setCurr(location);
        return cb;
    }

    void handleInput();
    void update(float delta);
    void render(HBITMAP element, HDC hdc) {
        Graphic::DrawBitmap(element, location, hdc);
    }
};