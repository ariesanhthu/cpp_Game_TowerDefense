#include "cenemy.h"

cenemy::cenemy() {
    health = 300;
    speed = 10;
    path.clear();
    isMove = false;
}

void cenemy::setPath(vector<POINT> ePath) {
    if (ePath.empty()) {
        std::string err = "err";
        throw(err);
    }

    vector<int> directionX;
    vector<int> directionY;

    currentPosition = ePath[0];

    for (size_t i = 0; i < ePath.size() - 1; i++) {
        if (ePath[i].x < ePath[i + 1].x) {
            directionX.push_back(1);
            directionY.push_back(0);
        }
        else if (ePath[i].x > ePath[i + 1].x) {
            directionX.push_back(-1);
            directionY.push_back(0);
        }
        else if (ePath[i].y < ePath[i + 1].y) {
            directionY.push_back(1);
            directionX.push_back(0);
        }
        else if (ePath[i].y > ePath[i + 1].y) {
            directionY.push_back(-1);
            directionX.push_back(0);
        }
    }

    int currX = currentPosition.x;
    int currY = currentPosition.y;

    for (size_t i = 1; i < ePath.size(); i++) {
        while (currX != ePath[i].x || currY != ePath[i].y) {
            path.push_back({ currX, currY });
            currX += directionX[i - 1];
            currY += directionY[i - 1];
        }
    }

}

void cenemy::update(float delta) {
    if (index >= path.size() - 1) {
        isMove = false;
        return;
    }

    if ((index + speed) < (path.size() - 1)) {
        index += speed;
        currentPosition = path[index];
    }
    else {
        index = path.size() - 1;
        //index = 0;

    }

}

