#include "cenemy.h"

cenemy::cenemy() {
    health = 3;
    speed = 4;
    path.clear();
}

void cenemy::calPath(vector<cpoint> ePath) {

    vector<int> directionX;
    vector<int> directionY;
    currentPosition = ePath[0];
    for (int i = 0; i < ePath.size()-1; i++) {
        if (ePath[i].getX() < ePath[i + 1].getX())
        {
            directionX.push_back(1);
            directionY.push_back(0);
        }
        else if (ePath[i].getX() > ePath[i + 1].getX()) 
        {
            directionX.push_back(-1);
            directionY.push_back(0);
        }
        else if (ePath[i].getY() < ePath[i + 1].getY()) 
        {
            directionY.push_back(1);
            directionX.push_back(0);
        }
        else if (ePath[i].getY() > ePath[i + 1].getY()) 
        {
            directionY.push_back(-1);
            directionX.push_back(0);
        }
    }

    int currX = currentPosition.getX();
    int currY = currentPosition.getY();
    for (int i = 1; i < ePath.size(); i++)
    {
        while (currX != ePath[i].getX() || currY != ePath[i].getY()) {
            path.push_back({ currX, currY, 0 });
            currX += directionX[i-1];
            currY += directionY[i-1];
        }
    }
    
}

void cenemy::draw(){
    ctool::mtx.lock();
    ctool::GotoXY((int)currentPosition.getX(), (int)currentPosition.getY());
    cout << " ";
    currentPosition = path[++index];// update position
    ctool::GotoXY((int)currentPosition.getX(), (int)currentPosition.getY());
    cout << health;

    ctool::mtx.unlock();
}