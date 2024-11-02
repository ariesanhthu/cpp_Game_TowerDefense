#include "cmap.h"



void cmap::drawMap(){

}

void cmap::readMap(int i){

    if(i < 0 || i > 4) return;
    mapCode = i;
    string filename = "SetupMap/SetUpMap" + to_string(i) + ".catfam";
    ifstream inFile(filename, ios::binary);
    //read tPlace
    if (!inFile) {
        cout << "ReadFile Faile";
        exit(1);
    }
    int nTPlace;
    inFile.read((char*) &nTPlace, sizeof(int));
    //tPlaces.resize(nTPlace);
    for (int i = 0; i < nTPlace; i++) {
        cpoint p;
        inFile.read((char*) &p, sizeof(cpoint));
        tPlaces.push_back(p);
    }
    //read ePath
    int nRoad,nConer;
    inFile.read((char*) &nRoad, sizeof(int));
    ePath.resize(nRoad);
    for(int i = 0; i < nRoad; i++){
        inFile.read((char*)&nConer, sizeof(int));
        for (int j = 0; j < nConer; j++){
            cpoint p;
            inFile.read((char*)&p, sizeof(cpoint));
            ePath[i].push_back (p);
        }
    }


    //read enemy
    inFile.read((char*)&nEnemy[0], sizeof(int));
    inFile.read((char*)&nEnemy[1], sizeof(int));
    inFile.read((char*)&nEnemy[2], sizeof(int));
    inFile.read((char*)&nEnemy[3], sizeof(int));
}