#pragma once
#include <vector>
#include <cmath> 
#include <windows.h>
#include <Graphic.h>
using namespace std;

class cenemy {
private:
    int health = 300;
    int speed;
    POINT currentPosition;
    vector<POINT> path;
    int index = 0;

public:
    bool isMove = false;

    cenemy();

    int getHealth() const { return this->health; }
    int getIndex() const { return index; }
    void setIndex(int x) {
        index = x;
    }

    void setHealth(int value) {
        health = value;
        if (health <= 0) {
            health = 0;
            isMove = false;  // Dừng di chuyển nếu chết
        }
    }

    void takeDamage(int damage) {
        if (health > 0) { // Prevent negative health
            health -= damage;
            if (health <= 0) {
                health = 0;   // Ensure no negative values
                if (isDead()) {
                    isMove = false;
                }
            }
        }
    }

    POINT getCurr() const { return currentPosition; }
    void setCurr(POINT curr) { currentPosition = curr; }

    bool isEnd() const { return index >= path.size() - 1; }
    bool isDead() const { return health <= 0; }

    void setPath(vector<POINT> ePath);
    std::vector<POINT> getPath() { return path; }

    void update(float delta);
    void render(HBITMAP element, HDC hdc) {
        if (!isDead()) {  // Chỉ vẽ nếu không chết
            Graphic::DrawBitmap(element, currentPosition, hdc);
        }
    }
};
