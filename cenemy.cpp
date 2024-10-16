#include "cenemy.h"

cenemy::cenemy() {
    for (int i = 0; i < cpoint::MAP_SIZE * cpoint::MAP_SIZE;i++)
        _p[i] = { 0,0,0 };
    dd[0] = -1; dd[1] = 0; dd[2] = 1; dd[3] = 0;
    dc[0] = 0; dc[1] = -1; dc[2] = 0; dc[3] = 1;
    _start = _end = _curr = { 0,0,0 };
    _speed = 3;
}

cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr) : cenemy() {
    _start = tstart;
    _end = tend;
    _curr = tcurr;
}

void cenemy::calcPath(int a[][cpoint::MAP_SIZE], int n, cpoint s, cpoint e, int step) {
    a[s.getX()][s.getY()] = step;
    if (s.getX() == e.getX() && s.getY() == e.getY()) {
        int k = 1;
        while (k <= step) {
            for (int i = 0; i < cpoint::MAP_SIZE; i++) {
                for (int j = 0; j < cpoint::MAP_SIZE; j++) {
                    if (a[i][j] == k) {
                        _p[k - 1] = cpoint::fromRowColToXY({ i,j,0 });
                        goto nhan;
                    }
                }
            }
            nhan: k++;
        }
        return;
    }
    for (int i = 0; i < 4;i++) {
        int dmoi = dd[i] + s.getX(), cmoi = dc[i] + s.getY();
        if (dmoi>=0 && dmoi<n && cmoi>=0 && cmoi<n && a[dmoi][cmoi] == 0)
            calcPath(a, n, { dmoi, cmoi, 0 }, e, step + 1);
    }
    a[s.getX()][s.getY()] = 0;
}

void cenemy::findPath(cpoint a[][cpoint::MAP_SIZE], cpoint s, cpoint e){
    int ta[cpoint::MAP_SIZE][cpoint::MAP_SIZE];
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++)
            ta[i][j] = a[i][j].getC();
    }
    s = cpoint::fromXYToRowCol(s);
    e = cpoint::fromXYToRowCol(e);
    calcPath(ta, cpoint::MAP_SIZE, s, e);
}