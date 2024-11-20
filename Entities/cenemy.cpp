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

void cenemy::update() {
    currentPosition = path[index++];
}

void cenemy::draw(){
    ctool::mtx.lock();

    ctool::GotoXY((int)currentPosition.getX(), (int)currentPosition.getY());
    cout << " ";
    currentPosition = path[index++];// update position
    ctool::GotoXY((int)currentPosition.getX(), (int)currentPosition.getY());
    cout << health;

    ctool::mtx.unlock();
}


void cenemy::writeFile(ofstream& outFile) {
    outFile.write((char*) &health, sizeof(int));
    outFile.write((char*) &speed, sizeof(int));
    outFile.write((char*) &currentPosition, sizeof(cpoint));
    outFile.write((char*) &index, sizeof(int));

    int size = path.size();
    outFile.write((char*) &size, sizeof(int));
    for (int i = 0; i < size; i++) {
        outFile.write((char*) &path[i], sizeof(cpoint));
    }
}
void cenemy::readFile(ifstream& inFile) {
    inFile.read((char*)&health, sizeof(int));
    inFile.read((char*)&speed, sizeof(int));
    inFile.read((char*)&currentPosition, sizeof(cpoint));
    inFile.read((char*)&index, sizeof(int));

    int size;
    inFile.read((char*)&size, sizeof(int));
    path.resize(size);
    for (int i = 0; i < size; i++) {
        inFile.read((char*)&path[i], sizeof(cpoint));
    }
}