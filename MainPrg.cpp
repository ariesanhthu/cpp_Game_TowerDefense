//#include "PrecompiledHeader.h"
//using namespace std;
//
//void ThreadFunc2(cgame&);
//void ThreadFunc1(cgame&);
//
////int main() {
////    cout << "Press any key to start demo: ";
////    cin.get();
////    ctool::ShowConsoleCursor(false);
////    // genSetUpFile();
////    cgame game;
////    game.getMap().readMap(0);
////    game.startGame();
////    cout << "game";
////    thread t1(ThreadFunc1, std::ref(game));
////    thread t2(ThreadFunc2, std::ref(game));
////    t1.join();
////    t2.join();
////
////}
////
////void ThreadFunc2(cgame& cg) {
////    vector<cpoint> tPlaces = cg.getMap().getTPlaces();
////    //ctower tw(tPlaces[0]);
////    ctower tw({ 0,15,0 });
////    cbullet& bullet = tw.getBullet();
////    int speed = bullet.getSpeed();
////    cenemy& e = cg.getEnemy()[0];
////    
////   /* bullet.calPath(eCurr);*/
////    int i = 0;
////    cout << "threat 2";
////    while (!cg.getIsExist1()) {
////        cpoint eCurr = e.getCurr();
////        tw.draw();
////        if(bullet.getCurr().distance(e.getCurr()) < 2){
////            cout << "hit";
////            cg.setIsExist1(true);
////            break;
////        }else{
////
////            bullet.draw(' ');
////            bullet.calPath(e.getCurr());
////            bullet.draw('*');
////            i++;
////        }
////        Sleep(1000 / bullet.getSpeed());
////    }
////    cg.setIsExist2(true);
////}
////
////void ThreadFunc1(cgame& cg) {
////    vector<cpoint> ePath = cg.getMap().getEPath(0);
////   /* vector<cpoint> directionX = cg.getMap().getEPath(0);
////    vector<cpoint> directionX = cg.getMap().getEPath(0);*/
////    int i = 0;
////    cenemy& e = cg.getEnemy()[0];
////    e.calPath(ePath);
////
////    while (!cg.getIsExist1()) {
////        if (e.isEnd()) break;
////        e.draw();
////        Sleep(1000 / e.getSpeed());
////    }
////    cg.setIsExist1(true);
////}
//
////Game logic
////int game(int);
////int placeTower(cgame&);
////void enemyThread(cgame&, cenemy&);
////void towerThread(cgame&, ctower);
////void bulletThread(cbullet&, cenemy&);
////void checkAvaibleEnemy(cgame&);
////
////int game(int numMap) {
////    ctool::ShowConsoleCursor(0);
////    cgame game;
////    cmap &map = game.getMap();
////
////    //game.startGame();
////    map.readMap(numMap);
////    //place tower
////    placeTower(game);
////    //get Enemy
////    int NumOfPath = map.getNumOfPath();
////    vector<cenemy>& eList = game.getEnemy();
////    int nEnemy[4], AllEnemy = 0;
////    for (int i = 0; i < NumOfPath; i++) {
////        nEnemy[i] = map.getEnemy(i);
////        AllEnemy += nEnemy[i];
////    }
////    for (int i = 0; i < AllEnemy; i++) {
////        eList.push_back(cenemy());
////        eList[i].calPath(map.getEPath(i%NumOfPath));
////    }
////
////    //start thread
////    vector<ctower>& towerList = game.getTower();
////    //vector<thread> towerThreadList;
////    vector<thread> threads;
////    for (int i = 0; i < towerList.size(); i++) {
////        //towerThreadList.push_back(thread(towerThread, ref(game), towerList[i]));
////        threads.push_back(thread(towerThread, ref(game), towerList[i]));
////        
////    }
////    //vector<thread> enemyThreadList;
////    for (int i = 0; i < eList.size(); i++) {
////        //enemyThreadList.push_back(thread(enemyThread, ref(game), ref(eList[i])));
////        threads.push_back(thread(enemyThread, ref(game), ref(eList[i])));
////        this_thread::sleep_for(chrono::milliseconds(1000*2));
////    }
////    threads.push_back(thread(checkAvaibleEnemy, ref(game)));
////    //join thread
////    for (thread& t : threads) {
////        if (t.joinable())
////            t.join();
////    }
////
////    /*for(int i = 0; i < towerThreadList.size(); i++){
////        if(towerThreadList[i].joinable())
////            towerThreadList[i].join();
////    }*/
////    
////    /*for (int i = 0; i < enemyThreadList.size(); i++) {
////        if (enemyThreadList[i].joinable())
////            enemyThreadList[i].join();
////        Sleep(1000 / 2);
////    }*/
////    return 0;
////}
////
////int placeTower(cgame &game){
////    vector<ctower>& towerList = game.getTower();
////    vector<cpoint> tPlaces = game.getMap().getTPlaces();
////    for (cpoint t : tPlaces) {
////        towerList.push_back(t);
////    }
////    return 0;
////}
////
////void towerThread(cgame& game,ctower tower){
////    /*ctool::mtx.lock();
////    cout << this_thread::get_id() << endl;
////    cout << tower.getLocation().getX() << endl;
////    ctool::mtx.unlock();*/
////    tower.draw();
////    vector<cenemy>& eList = game.getEnemy();
////    while (!game.getIsExist1()) {
////        for (int i = 0; i < eList.size(); i++) {
////            if (tower.getLocation().distance(eList[i].getCurr()) < tower.getRange() && eList[i].getHealth() > 0) {
////                cbullet& bullet = tower.getBullet();
////                bulletThread(bullet, eList[i]);
////                this_thread::sleep_for(chrono::milliseconds(500 * tower.getSpeed()));
////                break;
////            }
////        }
////    }
////}
////
////void bulletThread(cbullet& bullet, cenemy& enemy) {
////    int bullbetSpeed = bullet.getSpeed();
////    while (bullet.getCurr().distance(enemy.getCurr()) > 2) {
////        bullet.draw(' ');
////        bullet.calPath(enemy.getCurr());
////        bullet.draw('*');
////        Sleep(200 / bullbetSpeed); 
////    }
////    enemy.hit();
////    bullet.draw(' ');
////    enemy.draw();
////}
////
////void enemyThread(cgame& game, cenemy& enemy) {
////
////    int enemySpeed = enemy.getSpeed();
////    while (!game.getIsExist1()) {
////        if (enemy.isEnd()) {
////            game.setIsExist1(true);
////            break;
////        }
////        if (enemy.getHealth() <= 0) break;
////        enemy.draw();
////        this_thread::sleep_for(chrono::milliseconds(500 / enemy.getSpeed()));
////    }
////    //game.setIsExist1(true);
////}
////
////void checkAvaibleEnemy(cgame& game) {
////    vector<cenemy>& eList = game.getEnemy();
////    while (!game.getIsExist1()) {
////        ctool::mtx.lock();
////        int count = 0;
////        for (cenemy& e : eList) {
////            if (e.getHealth() > 0) {
////                count++;
////            }
////        }
////        if (count == 0) break;
////        ctool::mtx.unlock();
////    }
////    game.setIsExist1(true);
////}
////
////int main() {
////    //genSetUpFile();
////
////    game(1); // man choi 1
////    //game(2); // man choi 2
////    return 0;
////}