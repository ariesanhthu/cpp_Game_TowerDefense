#include "cmap.h"



void cmap::drawMap(){

}

void cmap::readMap(int i){

    if(i < 0 || i > 4) return;
    mapCode = i;
    string filename = "testSetUpMap1.cat";
    ifstream inFile(filename, ios::binary);

    //read tPlace
    int nTPlace;
    inFile.read((char*) &nTPlace, sizeof(int));
    tPlaces.resize(nTPlace);

    for(int i = 0; i < nTPlace; i++)
        inFile.read((char*) &tPlaces[i], sizeof(cpoint));

    //read ePath
    int nConer;
    inFile.read((char*) &nConer, sizeof(int));
    ePath.resize(1);
    ePath[0].resize(nConer);
    for(int i = 0; i < nConer; i++)
        inFile.read((char*) &ePath[0][i], sizeof(cpoint));
    
    /*directionX.resize(1);
    directionY.resize(1);
    directionX[0].resize(nConer - 1);
    directionY[0].resize(nConer - 1);
    for (int i = 0; i < nConer-1; i++) {
        if (ePath[0][i].getX() < ePath[0][i + 1].getX()) directionX[0][i] = 1;
        else if (ePath[0][i].getX() < ePath[0][i + 1].getX()) directionX[0][i] = -1;
        else if (ePath[0][i].getY() > ePath[0][i + 1].getY()) directionY[0][i] = 1;
        else if (ePath[0][i].getY() < ePath[0][i + 1].getY()) directionY[0][i] = -1;*/
    //}

    //read enemy

    /*inFile.read((char*) &nEnemy, sizeof(int));*/

}