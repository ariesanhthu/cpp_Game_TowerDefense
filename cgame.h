#pragma once
#include "cplayer.h"
#include "cmap.h"
#include <fstream>
class cgame {
    private:
        cplayer player;
        cmap map;
        vector<ctower> listTower;
        vector<cenemy> listEnemy;
        bool _ISEXIT1, _ISEXIT2;
        
    public:
        cgame();
        bool getIsExist1() { return _ISEXIT1; }
        void setIsExist1(bool b) { _ISEXIT1 = b; }
        bool getIsExist2() { return _ISEXIT2; }
        void setIsExist2(bool b) { _ISEXIT2 = b; }
        cmap& getMap() { return map; }
        vector<ctower>& getTower() {return listTower;}
        vector<cenemy>& getEnemy() {return listEnemy;}
        void startGame();
        bool readFile(string);
        bool saveGame(string);
};
