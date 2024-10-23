#include "cgame.h"
#include <thread>

using namespace std;

void ThreadFunc2(cgame&);
void ThreadFunc1(cgame&);

int main() {
    cout << "Press any key to start demo: ";
    cin.get();
    ctool::ShowConsoleCursor(false);
    cgame game;
    game.getMap().readMap(0);

    thread t1(ThreadFunc1, std::ref(game));
    thread t2(ThreadFunc2, std::ref(game));
    t1.join();
    t2.join();
}

void ThreadFunc2(cgame& cg) {
    vector<cpoint> tPlaces = cg.getMap().getTPlaces();
    ctower tw(tPlaces[0]);
    cbullet& bullet = tw.getBullet().get;
    int speed = bullet.getSpeed();
    cenemy e = cg.getEnemy()[0];
    while (!cg.getIsExist1()) {
        tw.draw();
        if(!isBullet){
            bullet.setCurr(tw.getLocation());
        }else{
        }
    }
    cg.setIsExist2(true);
}

void ThreadFunc1(cgame& cg) {
    vector<cpoint> ePath = cg.getMap().getEPath(0);

    while (!cg.getIsExist1()) {
       
    }
    cg.setIsExist1(true);
}