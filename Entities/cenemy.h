#pragma once
#include <vector>
#include <cmath> 
#include <windows.h>
#include <Graphic.h>
using namespace std;

class cenemy {
private:
    int health;
    int speed;
    POINT currentPosition;
    vector<POINT> path;
    size_t index = 0;

public:
    bool isMove = false;
    
    cenemy();
    
    POINT getCurr() const { return this->currentPosition; }
    void setCurr(POINT curr) { this->currentPosition = curr; }

    bool isEnd() const { return index >= path.size() - 1; }
    bool isDead() const { return health == 0; }

    void setPath(vector<POINT> ePath);

    void handleinput(); 
    void update(float delta);
    void render(HBITMAP element, HDC hdc) {
        Graphic::DrawBitmap(element, currentPosition, hdc);
    }
};