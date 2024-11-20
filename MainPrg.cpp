#include "PrecompiledHeader.h"
#include "constant.h"
using namespace std;

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
