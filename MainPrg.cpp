#include "cgame.h"
// #include "genSetUP.cpp"
#include <thread>

using namespace std;

void ThreadFunc2(cgame&);
void ThreadFunc1(cgame&);

int main() {
    cout << "Press any key to start demo: ";
    cin.get();
    ctool::ShowConsoleCursor(false);
    // genSetUpFile();
    cgame game;
    game.getMap().readMap(0);
    game.startGame();
    cout << "game";
    thread t1(ThreadFunc1, std::ref(game));
    thread t2(ThreadFunc2, std::ref(game));
    t1.join();
    t2.join();
}

void ThreadFunc2(cgame& cg) {
    vector<cpoint> tPlaces = cg.getMap().getTPlaces();
    //ctower tw(tPlaces[0]);
    ctower tw({ 0,15,0 });
    cbullet& bullet = tw.getBullet();
    int speed = bullet.getSpeed();
    cenemy& e = cg.getEnemy()[0];
    
   /* bullet.calPath(eCurr);*/
    int i = 0;
    cout << "threat 2";
    while (!cg.getIsExist1()) {
        cpoint eCurr = e.getCurr();
        tw.draw();
        if(bullet.getCurr().distance(e.getCurr()) < 2){
            cout << "hit";
            cg.setIsExist1(true);
            break;
        }else{

            bullet.draw(' ');
            bullet.calPath(e.getCurr());
            bullet.draw('*');
            i++;
        }
        Sleep(1000 / bullet.getSpeed());
    }
    cg.setIsExist2(true);
}

void ThreadFunc1(cgame& cg) {
    vector<cpoint> ePath = cg.getMap().getEPath(0);
   /* vector<cpoint> directionX = cg.getMap().getEPath(0);
    vector<cpoint> directionX = cg.getMap().getEPath(0);*/
    int i = 0;
    cenemy& e = cg.getEnemy()[0];
    e.calPath(ePath);

    while (!cg.getIsExist1()) {
        if (e.isEnd()) break;
        e.draw();
        Sleep(1000 / e.getSpeed());
    }
    cg.setIsExist1(true);
}

//test

int loadMap(int numMap) {
    cgame game;
    cmap map = game.getMap();
    map.readMap(numMap);
    //place tower

    //get Enemy

    //join tower threat
}