#pragma once
#include "ctool.h"
#include <cstring>

class cplayer{
    private:
        char name[10];
        int point;
    public:
        cplayer(){};
        cplayer(char s[], int p){ strcpy(name, s); point = p;}

        char* getName() { return name;}
        int getPoint() { return point;}
        void setPoint(int p) { point = p;}
        void addPoint(int a) { point += a;}
};

