#include <iostream>
#include <fstream>

#include "cpoint.h"
#include "ctower.h"
#include "cenemy.h"
#include "cmap.h"

using namespace std;

int genSetUpFile(){
    {
    //    ofstream outFile("testSetUpMap1.cat", ios::binary);
    //    //tPlace setup
    //    int i = 1;
    //    cpoint t{5,5,0};
    //    outFile.write((char*) &i, sizeof(int));
    //    outFile.write((char*) &t, sizeof(cpoint));


    //    //ePath setup
    //    int n = 4;
    //    cpoint a{1,1,0};
    //    cpoint b{30,1,0};
    //    cpoint c{30,30,0};
    //    cpoint d{50,30,0};

    //    outFile.write((char*) &n, sizeof(int));
    //    outFile.write((char*) &a, sizeof(cpoint));
    //    outFile.write((char*) &b, sizeof(cpoint));
    //    outFile.write((char*) &c, sizeof(cpoint));
    //    outFile.write((char*) &d, sizeof(cpoint));
    //    outFile.close();

    //     ifstream inf("testSetUpMap1.cat", ios::binary);
    //     cmap map;
    //     map.readMap(0);
    //     vector<cpoint> tPlaces = map.getTPlaces();
    //     vector<cpoint> ePath = map.getEPath(0);
    //     for(int i = 0; i < tPlaces.size(); i++){
    //         cout << tPlaces[i].getX() << " " << tPlaces[i].getY() << endl;
    //     }
    }
    const int NumOfMap = 4;
    int n, m ,x ,y;
    cpoint p;
    for (int i = 0; i < NumOfMap; i++) {
        ifstream file("SetupMap/SetUpMap" + to_string(i + 1) + ".cat");
        if (file) continue; //skip if bin file is available

        ifstream inFile("SetupMap/map" + to_string(i + 1) + ".txt");
        ofstream outFile("SetupMap/SetUpMap" + to_string(i + 1) + ".cat");
        //tPlaces
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));
        for (int j = 0; j < n; j++) {
            cin >> x >> y;
            p = { x,y,0 };
            outFile.write((char*)&p, sizeof(cpoint));
        }
        //ePath
        inFile >> n;
        outFile.write((char*)&n, sizeof(int));
        for (int j = 0; j < n; j++) {
            inFile >> m;
            outFile.write((char*)&m, sizeof(int));
            for (int k = 0; k < m; k++) {
                inFile >> x >> y;
                outFile.write((char*)&p, sizeof(cpoint));
            }
        }
        inFile.close();
        outFile.close();
    }
    return 0;
}