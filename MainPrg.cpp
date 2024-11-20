#include "PrecompiledHeader.h"

#include <conio.h>

using namespace std;

mutex mtx;
condition_variable cv;
bool pause = false;
bool phase = false;

//Game logic
int StartGame(int, cplayer&);
int placeTower(cgame&);
void enemyThread(cgame&, cenemy&);
void towerThread(cgame&, ctower);
void bulletThread(cbullet&, cenemy&);
void checkAvaibleEnemy(cgame&);
void pauseGameMenu(cgame& game);

int StartGame(int numMap, cplayer& player) {
    //ctool::ShowConsoleCursor(0);

    cgame game;
    game.setPlayer(player);
    cmap &map = game.getMap();
    
    //game.startGame();
    map.readMap(numMap);

    //place tower
    //placeTower(game);

    game.readFile("testSaveGame");


    //get Enemy
    int NumOfPath = map.getNumOfPath();
    vector<cenemy>& eList = game.getEnemy();
    /*for (auto e : eList) {
        ctool::GotoXY(1, 1);
        cout << 1;
    }
    int nEnemy[4], AllEnemy = 0;

    for (int i = 0; i < NumOfPath; i++) {
        nEnemy[i] = map.getEnemy(i);
        AllEnemy += nEnemy[i];
    }

    for (int i = 0; i < AllEnemy; i++) {
        eList.push_back(cenemy());
        eList[i].calPath(map.getEPath(i%NumOfPath));
    }*/
    //start thread

    vector<ctower>& towerList = game.getTower();

    vector<thread> threads;

    threads.push_back(thread(pauseGameMenu, ref(game)));
    for (int i = 0; i < towerList.size(); i++) {
        threads.push_back(thread(towerThread, ref(game), towerList[i]));
        
    }

    for (int i = 0; i < eList.size(); i++) {
        unique_lock<mutex> lock{ mtx };
        cv.wait(lock, []() {return !pause; });
        threads.push_back(thread(enemyThread, ref(game), ref(eList[i])));
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000 * 2));
        //threads.push_back(thread(enemyThread, ref(game), ref(eList[i])));
        this_thread::sleep_for(chrono::milliseconds(1000*2));
    }

    threads.push_back(thread(checkAvaibleEnemy, ref(game)));

    //join thread
    for (thread& t : threads) {
        if (t.joinable())
            t.join();
    }
    return 0;
}

int placeTower(cgame &game){
    vector<ctower>& towerList = game.getTower();
    vector<cpoint> tPlaces = game.getMap().getTPlaces();
    for (cpoint t : tPlaces) {
        towerList.push_back(t);
    }
    return 0;
}

void towerThread(cgame& game,ctower tower){
    tower.draw();
    vector<cenemy>& eList = game.getEnemy();

    while (!game.getIsExist1()) {

        for (int i = 0; i < eList.size(); i++) {

            if (tower.getLocation().distance(eList[i].getCurr()) < tower.getRange() && eList[i].getHealth() > 0) {

                cbullet& bullet = tower.getBullet();
                bulletThread(bullet, eList[i]);

                this_thread::sleep_for(chrono::milliseconds(500 * tower.getSpeed()));
                break;
            }
        }
    }
}

void bulletThread(cbullet& bullet, cenemy& enemy) {
    int bullbetSpeed = bullet.getSpeed();

    while (bullet.getCurr().distance(enemy.getCurr()) > 2 && enemy.getHealth() > 0) {
        unique_lock<mutex> lock{ mtx };
        cv.wait(lock, []() {return !pause; });
        bullet.draw(' ');
        bullet.calPath(enemy.getCurr());
        bullet.draw('*');
        lock.unlock();
        Sleep(200 / bullbetSpeed); 
    }

    enemy.hit();
    bullet.draw(' ');
    enemy.draw();
}

void enemyThread(cgame& game, cenemy& enemy) {

    int enemySpeed = enemy.getSpeed();

    while (!game.getIsExist1()) {

        unique_lock<mutex> lock{ mtx };
        cv.wait(lock, []() {return !pause; });

        if (enemy.isEnd()) {
            game.setIsExist1(true);
            break;
        }

        if (enemy.getHealth() <= 0) break;

        enemy.draw();

        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(500 / enemy.getSpeed()));
    }
    game.addPoint(10);
    //game.setIsExist1(true);
}

void checkAvaibleEnemy(cgame& game) {
    vector<cenemy>& eList = game.getEnemy();

    while (!game.getIsExist1()) {
        ctool::mtx.lock();
        int count = 0;

        for (cenemy& e : eList) {

            if (e.getHealth() > 0) {
                count++;
            }

        }

        if (count == 0) break;
        //if (count < game.getEnemy().size()/2) 
        ctool::mtx.unlock();
    }
    game.setIsExist1(true);
    //game.saveGame("testSavegame");
}

void pauseGameMenu(cgame& game) {
    while (!game.getIsExist1()) {
        //listenEvent
        while (!pause) {
            int c = _getch();
            if (c == 27 || c == 80) {
                std::unique_lock<std::mutex> lock{ ctool::mtx };
                pause = true;
                cv.notify_all();
            }
        }
        //set player name
        //show popup screen
        game.saveGame("testSaveGame");
        int index = 0;
        while (pause) {
            int ch = _getch();
            if (ch == KEY_ARROW_PREFIX) {
                ch = _getch();
                if (ch == KEY_LEFT) {
                    index--;
                }
                else if (ch == KEY_RIGHT) {
                    index++;
                }
                if (index == -1) index = 1;
                if (index == 2) index = 0;
            }
            else if (ch == KEY_ENTER) {
                //if (index == 1) screenCode = "main screen"; // den Main screen
                //else game.setIsExist2(false); // tiep tuc choi
            }
            else if (ch == KEY_ESC) {
                game.setIsExist2(false);
                pause = false;
                cv.notify_all();
            }
            //continue;
            //Sleep(500);
        }
        //lock.unlock();
    }
}

int main() {
    //genSetUpFile();
    cplayer player;
    StartGame(1, player); // man choi 1
    //StartGame(2, player); // man choi 2
    return 0;
}