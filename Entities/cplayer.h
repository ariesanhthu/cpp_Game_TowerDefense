#pragma once
#include "ctool.h"
#include <cstring>

class cplayer {
private:
    char name[50];
    char pass[50];
    // string name;
    // string pass;
    int point;

   
public:
    cplayer(string nName = "Unknown", int p = 0) {
        strcpy(name, nName.c_str());
        // name = nName;
        point = p;
    }
    string getName() { return name; }
    int getPoint() { return point; }
    void setPoint(int p) { point = p; }
    void addPoint(int a) { point += a; }
    string getPass() {
        return pass;
    }
    void setName(string nName);
    void setPass(string nPass);
    void registerUser(string nName, string nPass);
    void login(string nName, string nPass);
};