#include "cbullet.h"
cbullet::cbullet() {
_n = 0;
_speed = 4;
_curr = { 0,0,0 };
for (int i = 0; i < cpoint::MAP_SIZE *
    cpoint::MAP_SIZE;i++) _p[i] = { 0,0,0 };
    for (int i = 0; i < cpoint::MAP_SIZE;i++) {
        for (int j = 0; j < cpoint::MAP_SIZE;j++) {
            _m[i][j] = { 0, 0, 0 };
        }
    }
}

void cbullet::updateMap(int i, int j, cpoint v) {
    // if (...)
        _m[i][j] = v;
}

int cbullet::queryCFromRowCol(int row, int col) {
    if (0)return -2;
    else {
        for (int i = 0; i < cpoint::MAP_SIZE; i++) {
            for (int j = 0; j < cpoint::MAP_SIZE; j++) {
                cpoint tmp = cpoint::fromXYToRowCol(_m[i][j]);
                    if (tmp.getX() == row && tmp.getY() == col) {
                    return _m[i][j].getC();
                }
            }
        }
    }
    return 0;
}

int cbullet::calcPathBullet(cpoint tower) {
    cpoint tmp = cpoint::fromXYToRowCol(tower);
    int row = tmp.getX(), col = tmp.getY(), i = 0;
    do {
        col++; row--;
        if (queryCFromRowCol(row, col) == 0) {
            _p[i] = cpoint::fromRowColToXY({ row,col,0 });
            i += 2;
        }
        else break;
    } while (i < cpoint::MAP_SIZE);
    _n = i;
    for (i = 1; i < _n;i += 2) {
        _p[i] = {_p[i - 1].getX() + 2,_p[i - 1].getY() - 1,0};
    }
    _curr = { _p[0].getX(),_p[0].getY(),_p[0].getC() };
    return _n;
}   