#include "PrecompiledHeader.h"
#include "constant.h"
using namespace std;

//Game logic
//int game(int);
//int placeTower(cgame&);
//void enemyThread(cgame&, cenemy&);
//void towerThread(cgame&, ctower);
//void bulletThread(cbullet&, cenemy&);
//void checkAvaibleEnemy(cgame&);
//
//int game(int numMap) {
//    ctool::ShowConsoleCursor(0);
//    cgame game;
//    cmap &map = game.getMap();
//
//    //game.startGame();
//    map.readMap(numMap);
//    //place tower
//    placeTower(game);
//    //get Enemy
//    int NumOfPath = map.getNumOfPath();
//    vector<cenemy>& eList = game.getEnemy();
//    int nEnemy[4], AllEnemy = 0;
//    for (int i = 0; i < NumOfPath; i++) {
//        nEnemy[i] = map.getEnemy(i);
//        AllEnemy += nEnemy[i];
//    }
//    for (int i = 0; i < AllEnemy; i++) {
//        eList.push_back(cenemy());
//        eList[i].calPath(map.getEPath(i%NumOfPath));
//    }
//
//    //start thread
//    vector<ctower>& towerList = game.getTower();
//    //vector<thread> towerThreadList;
//    vector<thread> threads;
//    for (int i = 0; i < towerList.size(); i++) {
//        //towerThreadList.push_back(thread(towerThread, ref(game), towerList[i]));
//        threads.push_back(thread(towerThread, ref(game), towerList[i]));
//        
//    }
//    //vector<thread> enemyThreadList;
//    for (int i = 0; i < eList.size(); i++) {
//        //enemyThreadList.push_back(thread(enemyThread, ref(game), ref(eList[i])));
//        threads.push_back(thread(enemyThread, ref(game), ref(eList[i])));
//        this_thread::sleep_for(chrono::milliseconds(1000*2));
//    }
//    threads.push_back(thread(checkAvaibleEnemy, ref(game)));
//    //join thread
//    for (thread& t : threads) {
//        if (t.joinable())
//            t.join();
//    }
//
//    /*for(int i = 0; i < towerThreadList.size(); i++){
//        if(towerThreadList[i].joinable())
//            towerThreadList[i].join();
//    }*/
//    
//    /*for (int i = 0; i < enemyThreadList.size(); i++) {
//        if (enemyThreadList[i].joinable())
//            enemyThreadList[i].join();
//        Sleep(1000 / 2);
//    }*/
//    return 0;
//}
//
//int placeTower(cgame &game){
//    vector<ctower>& towerList = game.getTower();
//    vector<cpoint> tPlaces = game.getMap().getTPlaces();
//    for (cpoint t : tPlaces) {
//        towerList.push_back(t);
//    }
//    return 0;
//}
//
//void towerThread(cgame& game,ctower tower){
//    tower.draw();
//    vector<cenemy>& eList = game.getEnemy();
//    while (!game.getIsExist1()) {
//        for (int i = 0; i < eList.size(); i++) {
//            if (tower.getLocation().distance(eList[i].getCurr()) < tower.getRange() && eList[i].getHealth() > 0) {
//                cbullet& bullet = tower.getBullet();
//                bulletThread(bullet, eList[i]);
//                this_thread::sleep_for(chrono::milliseconds(500 * tower.getSpeed()));
//                break;
//            }
//        }
//    }
//}
//
//void bulletThread(cbullet& bullet, cenemy& enemy) {
//    int bullbetSpeed = bullet.getSpeed();
//    while (bullet.getCurr().distance(enemy.getCurr()) > 2) {
//        bullet.draw(' ');
//        bullet.calPath(enemy.getCurr());
//        bullet.draw('*');
//        Sleep(200 / bullbetSpeed); 
//    }
//    enemy.hit();
//    bullet.draw(' ');
//    enemy.draw();
//}
//
//void enemyThread(cgame& game, cenemy& enemy) {
//
//    int enemySpeed = enemy.getSpeed();
//    while (!game.getIsExist1()) {
//        if (enemy.isEnd()) {
//            game.setIsExist1(true);
//            break;
//        }
//        if (enemy.getHealth() <= 0) break;
//        enemy.draw();
//        this_thread::sleep_for(chrono::milliseconds(500 / enemy.getSpeed()));
//    }
//}
//
//void checkAvaibleEnemy(cgame& game) {
//    vector<cenemy>& eList = game.getEnemy();
//    while (!game.getIsExist1()) {
//        ctool::mtx.lock();
//        int count = 0;
//        for (cenemy& e : eList) {
//            if (e.getHealth() > 0) {
//                count++;
//            }
//        }
//        if (count == 0) break;
//        ctool::mtx.unlock();
//    }
//    game.setIsExist1(true);
//}

//int main() {
//    game(1); 
//    return 0;
//}

void manageAllEnemy(cgame& game) {
	vector<cenemy>& eList = game.getEnemy();
	int numberOfE = 0;
	time_point nextAdd = chrono::system_clock::now();

	while (!game.getIsExist1()) {

		time_point start = chrono::system_clock::now();
		
		int countMoved = 0;

		for (cenemy& enemy : eList) {

			if (enemy.getHealth() < 0 || countMoved++ > numberOfE || chrono::system_clock::now() < nextAdd) continue;

			enemy.update();

			if (enemy.isEnd()) game.setIsExist1(true);
		}

		if (countMoved > numberOfE) {
			numberOfE++;
			nextAdd += chrono::milliseconds(1000);
		}

		time_point end = chrono::system_clock::now();
		chrono::microseconds timer = micro_cast(end - start);
		if (timer < micro(TIME_PER_TICK))
		this_thread::sleep_for(micro(TIME_PER_TICK) - timer); //sleep until next tick start
	}
}

void manageTowerAndBullet(cgame& game) {
	vector<ctower> tList = game.getTower();
	vector<cbullet> bList = game.getBullet();
	vector<cenemy>& eList = game.getEnemy();
	while (!game.getIsExist1()) {

		time_point start = chrono::system_clock::now();

		for (ctower& tower : tList) {
			if (tower.canShoot()) {
				for (cenemy& enemy : eList) {
					if (tower.getLocation().distance(enemy.getCurr()) < tower.getRange()) {
						cbullet nBullet = tower.shoot(&enemy);
						bList.push_back(nBullet);
					}
				}
			}
		}

		for (auto it = bList.begin(); it != bList.end();) {
			cbullet bullet = *it;

			cenemy* e = bullet.checkCollision();

			if (e == NULL) {
				bullet.update();
				++it;
			}
			else {
				e->hit(bullet.getDame());
				bList.erase(it);
			}

		}

		time_point end = chrono::system_clock::now();

		chrono::microseconds timer = micro_cast(end - start);

		if (timer < micro(TIME_PER_TICK))
			this_thread::sleep_for(micro(TIME_PER_TICK) - timer); //sleep until next tick start
	}
}

int game(int numMap) {
    ctool::ShowConsoleCursor(0);
    cgame game;
    cmap &map = game.getMap();

    //game.startGame();
    map.readMap(numMap);
    //place tower
    
    //get Enemy
    int NumOfPath = map.getNumOfPath();
    vector<cenemy>& eList = game.getEnemy();
    int nEnemy[4], AllEnemy = 0;
    for (int i = 0; i < NumOfPath; i++) {
        nEnemy[i] = map.getEnemy(i);
        AllEnemy += nEnemy[i];
    }
    for (int i = 0; i < AllEnemy; i++) {
        eList.push_back(cenemy());
        eList[i].calPath(map.getEPath(i%NumOfPath));
    }

	thread thread1(manageAllEnemy, ref(game));
	thread thread2(manageTowerAndBullet, ref(game));

	thread1.join();
	thread2.join();
    return 0;
}

int main() {
	game(1);
}