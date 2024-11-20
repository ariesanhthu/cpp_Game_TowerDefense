#pragma once
#include "cplayer.h"
#include "cmap.h"
#include <fstream>
class cgame {
    private:
        cplayer player;
        cmap map;
        vector<ctower> listTowers;
        vector<cenemy*> listEnemys;
        vector<cbullet> listBullets;
        bool _ISEXIT1, _ISEXIT2;
        
    public:
        cgame();
        ~cgame();
        bool getIsExist1() { return _ISEXIT1; }
        void setIsExist1(bool b) { _ISEXIT1 = b; }
        bool getIsExist2() { return _ISEXIT2; }
        void setIsExist2(bool b) { _ISEXIT2 = b; }
        void setPlayer(cplayer& nPlayer) { player = nPlayer; }
        void addPoint(int n) { player.addPoint(n); }
        cmap& getMap() { return map; }
        vector<ctower>& getTower() {return listTowers;}
        vector<cenemy*>& getEnemy() {return listEnemys;}
        vector<cbullet>& getBullet() {return listBullets;}
        void startGame();
        bool readFile(string);
        bool saveGame(string);
};
