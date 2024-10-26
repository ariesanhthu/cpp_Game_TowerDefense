#pragma once
#include "ctool.h"
#include <cstring>

class cplayer{
    private:
        char name[10];
        int point;
    public:
        cplayer(char s[], int p){ strcpy_s(name, s); point = p;}
        cplayer(): cplayer((char*)"guest",0) {};

        char* getName() { return name;}
        int getPoint() { return point;}
        void setPoint(int p) { point = p;}
        void addPoint(int a) { point += a;}
};

