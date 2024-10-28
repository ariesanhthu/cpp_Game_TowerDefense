#include "cmap.h"



void cmap::drawMap(){

}

void cmap::readMap(int i){

    if(i < 0 || i > 4) return;
    mapCode = i;
    string filename = "SetUpMap" + to_string(i) + ".cat";
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

    //read enemy

    /*inFile.read((char*) &nEnemy, sizeof(int));*/

}