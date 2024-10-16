#include "cmap.h"
cmap::cmap() {
    resetMapData();
    makeMapData();
}

void cmap::resetMapData() {
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            _m[i][j] = {4 * j + cpoint::LEFT + 2,2 * i + cpoint::TOP + 1,-1 };
        }
    }
}

void cmap::makeMapData() {
    _m[2][0].setC(0); _m[2][1].setC(0); _m[2][2].setC(0); _m[2][3].setC(0);
    _m[2][7].setC(-2); _m[2][8].setC(-2);
    _m[3][1].setC(-2); _m[3][2].setC(-2); _m[3][3].setC(0);
    _m[3][4].setC(0); _m[3][5].setC(0); _m[3][6].setC(0);
    _m[3][7].setC(-2); _m[3][8].setC(-2);
    _m[4][1].setC(-2); _m[4][2].setC(-2); _m[4][6].setC(0);
    _m[4][7].setC(0); _m[4][8].setC(0);
    _m[5][8].setC(0);
    _m[5][6].setC(0);
    _m[6][5].setC(0);
    _m[6][8].setC(0);
    _m[7][3].setC(0); _m[7][4].setC(0); _m[7][5].setC(0); _m[7][6].setC(0);
    _m[7][7].setC(0); _m[7][8].setC(0);
    _m[8][1].setC(-2); _m[8][2].setC(-2); _m[8][3].setC(0);
    _m[9][1].setC(-2); _m[9][2].setC(-2); _m[9][3].setC(0);
    // Initializes the current, starting and ending coordinates that
    // character passes through
    _ce.setStart(_m[2][0]);_ce.setEnd(_m[9][3]);_ce.setCurr(_m[2][0]);
    // Calculate the path for the character
    _ce.findPath(_m, _ce.getStart(), _ce.getEnd());
    // Start assigning coordinates for Tower _ctw
    _ctw.setLocation(_m[9][2]);
    // Updated map information for cbullet object of Tower _ctw
    _ctw.setMapForBullet(_m);
    // Calculate the path for the cbullet object of Tower _ctw
    _ctw.calcPathBullet();
}

void cmap::drawMap() {
// Draw map data _m
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            ctool::GotoXY(_m[i][j].getX(), _m[i][j].getY());
            if (_m[i][j].getC() == -1) cout << '+';
            else if (_m[i][j].getC() == -2) cout << 'U';
        }
    }
    // Draw _ctw
    ctool::GotoXY(_ctw.getLocation().getX(), _ctw.getLocation().getY());
    cout << 'T';
}