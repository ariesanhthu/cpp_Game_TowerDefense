#pragma once
#include <vector>
#include <cmath> 
#include <windows.h>
#include <Graphic.h>
using namespace std;

class cenemy {
private:
    vector<POINT> epath = {
        {0, 150},
        {100, 150},
        {200, 200},
        {300, 300},
        {400, 400}
    };

private:
    int health;
    int speed;
    POINT currentPosition;
    vector<POINT> path;
    size_t index = 0;

public:
    cenemy();
    POINT getCurr() const { return this->currentPosition; }
    void setPath(const vector<POINT>& ePath);
    void update();
    bool isEnd() const { return index >= path.size() - 1; }
};