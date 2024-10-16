#include "cgame.h"
#include <thread>

using namespace std;

void ThreadFunc2(cgame&);
void ThreadFunc1(cgame&);

int main() {
    cout << "Press any key to start demo: ";
    // cin.get();
    int speed;
    cin >> speed;
    ctool::ShowConsoleCursor(false);
    cgame cg;
    cg.getMap().getTower().getBullet().setSpeed(speed);
    cg.startGame();
    thread t1(ThreadFunc1, std::ref(cg));
    thread t2(ThreadFunc2, std::ref(cg));
    t1.join();
    t2.join();
    ctool::GotoXY(0, 20); // Jump to the last line to exit the program
    ctool::ShowConsoleCursor(true);
    return 0;
}

void ThreadFunc2(cgame& cg) {
    int i = 0;
    cenemy& ce = cg.getMap().getEnemy(); // Get the cenemy object
    cpoint _ENEMY;
    cbullet& cb = cg.getMap().getTower().getBullet(); // Get the cbullet object
    int _SPEED = cb.getSpeed(), _NBULLET = cb.getN();
    cpoint* _BULLET1_P = cb.getP();
    cpoint _BULLET1 = cb.getCurr();
    while (!cg.getIsExist1()) {
        ctool::Draw((char*)"o", i, _BULLET1_P, _BULLET1);
        cb.setCurr(_BULLET1);
        _ENEMY = ce.getCurr();
        if (_BULLET1.getX() == _ENEMY.getX() && _BULLET1.getY() == _ENEMY.getY()) {
            ctool::Draw((char*)" ", i, _BULLET1_P, _BULLET1);
            cg.setIsExist1(true);
            break;
        }
        else i++;
        Sleep(1000 / _SPEED);
        ctool::Draw((char*)" ", i - 1, _BULLET1_P, _BULLET1);
        if (i == _NBULLET)i = 0;
    }
    cg.setIsExist2(true);
}

void ThreadFunc1(cgame& cg) {
    int i = 0;
    cenemy& ce = cg.getMap().getEnemy(); // Get the cenemy object
    cpoint _ENEMY = ce.getCurr(), _END = ce.getEnd(); int SPEED = ce.getSpeed();
    cpoint* _P = ce.getP(); // Get the _p path of the cenemy object
    cbullet& cb = cg.getMap().getTower().getBullet(); // Get the cbullet object
    cpoint _BULLET1;
    while (!cg.getIsExist1()) {
        ctool::Draw((char*)"K", i, _P, _ENEMY);
        ce.setCurr(_ENEMY);
        _BULLET1 = cb.getCurr();
        if (_ENEMY.getX() == _END.getX() && _ENEMY.getY() == _END.getY()) {
            break;
        }
        else if (_ENEMY.getX() == _BULLET1.getX() && _ENEMY.getY() == _BULLET1.getY()) {
            ctool::Draw((char*)" ", i, _P, _ENEMY);
            break;
        }
        else i++;
        Sleep(1000 / SPEED);
        ctool::Draw((char*)" ", i - 1, _P, _ENEMY);
    }
    cg.setIsExist1(true);
}