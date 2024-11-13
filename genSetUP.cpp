#pragma once

#include "genSetUP.h"

using namespace std;

int genSetUpFile(){
    const int NumOfMap = 4;
    int n, m ,x ,y;

    for (int i = 0; i < NumOfMap; i++) {
        ifstream inFile("SetupMap/map" + to_string(i + 1) + ".txt");
        ofstream outFile("SetupMap/SetUpMap" + to_string(i + 1) + ".catfam", ios::binary);
        //tPlaces
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));
        for (int j = 0; j < n; j++) {
            inFile >> x >> y;
            cpoint p{ x,y,0 };
            outFile.write((char*) &p, sizeof(cpoint));
        }
        //ePath
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));
        for (int j = 0; j < n; j++) {
            inFile >> m;
            outFile.write((char*)&m, sizeof(int));
            for (int k = 0; k < m; k++) {
                inFile >> x >> y;
                cpoint p{ x,y,0 };
                outFile.write((char*) &p, sizeof(cpoint));
            }
        }
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));

        inFile.close();
        outFile.close();

    }
    return 0;
}