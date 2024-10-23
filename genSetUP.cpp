#include <iostream>
#include <fstream>

#include "cpoint.h"
#include "ctower.h"
#include "cenemy.h"
#include "cmap.h"

using namespace std;

int main(){
    ofstream outFile("testSetUpMap1.cat", ios::binary);
    //tPlace setup
    int i = 1;
    cpoint t{5,5,0};
    outFile.write((char*) &i, sizeof(int));
    outFile.write((char*) &t, sizeof(cpoint));


    //ePath setup
    int n = 4;
    cpoint a{1,1,0};
    cpoint b{10,1,0};
    cpoint c{10,10,0};
    cpoint d{15,10,0};

    outFile.write((char*) &n, sizeof(int));
    outFile.write((char*) &a, sizeof(cpoint));
    outFile.write((char*) &b, sizeof(cpoint));
    outFile.write((char*) &c, sizeof(cpoint));
    outFile.write((char*) &d, sizeof(cpoint));
    return 0;
}