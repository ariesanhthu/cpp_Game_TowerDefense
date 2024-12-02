#pragma once
#include "Graphic.h"
#include <cmath>
#include <windows.h>
#include <cenemy.h>

class cbullet {
private:
    POINT currentPosition;
    POINT targetPosition;
    int speed;
    int damage;
    bool active;
    

public:
    cbullet() : speed(10), damage(1), active(false) {}

    void setCurr(const POINT& p) { currentPosition = p; }
    POINT getCurr() const { return currentPosition; }

    void setTarget(const POINT& target) {
        targetPosition = target;
        active = true;
    }

    int getDamage() const { return damage; }
    int getSpeed() const { return speed; }
    bool isActive() const { return active; }

    void calPath() {
        if (!active) return;

        POINT direction = { targetPosition.x - currentPosition.x, targetPosition.y - currentPosition.y };
        float length = std::sqrt(static_cast<float>(direction.x * direction.x + direction.y * direction.y));

        // Normalize the direction vector and scale by speed
        if (length != 0) {
            direction.x = static_cast<int>(direction.x / length * speed);
            direction.y = static_cast<int>(direction.y / length * speed);

            currentPosition.x += direction.x;
            currentPosition.y += direction.y;
        }

        // Deactivate bullet if it reaches the target
        if (std::abs(currentPosition.x - targetPosition.x) <= speed &&
            std::abs(currentPosition.y - targetPosition.y) <= speed) {
            currentPosition = targetPosition;
            active = false;
        }
    }

    void render(HBITMAP element, HDC hdc) {
        if (active) {
            Graphic::DrawBitmap(element, currentPosition, hdc);
        }
    }
};
