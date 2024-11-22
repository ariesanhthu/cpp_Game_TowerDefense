#include "PrecompiledHeader.h"
#include "constant.h"
using namespace std;

mutex gameMutex;

void manageAllEnemy(cgame& game, vector<cenemy*>& eList) {
	//vector<cenemy*>& eList = game.getEnemy();
	int eListSize = eList.size();
	int numberOfE = 1;
	int remainE = 0;
	const int enemySpawnInterval = 1;
	time_point lastSpawn = chrono::system_clock::now();

	cout << eList[0]->getIdex();
	while (!game.getIsExist1()) {

		time_point start = chrono::system_clock::now();

		if (micro_cast(start - lastSpawn) > micro(1000000 * enemySpawnInterval) && numberOfE < eListSize) {
			numberOfE++;
			lastSpawn = chrono::system_clock::now();
		}
		remainE = 0;
		for (cenemy* e : eList) {
			if (remainE > numberOfE) break;
			if (e->getHealth() < 0) continue;

			//e->draw();
			e->update();

			remainE++;
			if (e->isEnd() || !remainE) game.setIsExist1(true);
		}


		time_point end = chrono::system_clock::now();
		chrono::microseconds timer = micro_cast(end - start);

		if (timer < micro(TIME_PER_TICK))
			this_thread::sleep_for(micro(TIME_PER_TICK) - timer); //sleep until next tick start
	}
}

void manageTowerAndBullet(cgame& game, vector<cenemy*>& eList) {
	vector<ctower>& tList = game.getTower();
	vector<cbullet>& bList = game.getBullet();
	//vector<cenemy*>& eList = game.getEnemy();

	while (!game.getIsExist1()) {
		
		time_point start = chrono::system_clock::now();

		for (ctower& tower : tList) {
			if (tower.canShoot()) {
				for (cenemy* enemy : eList) {

					if (tower.getLocation().distance(enemy->getCurr()) < tower.getRange() && enemy->getHealth() > 0) {
						cbullet nBullet = tower.shoot(enemy);

						bList.push_back(nBullet);

						break;
					}
				}
			}
		}

		//cout << "+++++++++++++++++++++++++++++++++" << endl;
		int i = 0;
		for (cbullet& bullet: bList) {

			cenemy* e = bullet.checkCollision();
			if (e == NULL) {
				bullet.update();

				//cout << bullet.getCurr().getX() << " " << bullet.getCurr().getY() << " " << bullet.getTarget()->getHealth() << endl;
				i++;
			}
			else {
				e->hit(bullet.getDame());
				bList.erase(bList.begin() + i);
			}
		}

		time_point end = chrono::system_clock::now();

		chrono::microseconds timer = micro_cast(end - start);

		if (timer < micro(TIME_PER_TICK))
			this_thread::sleep_for(micro(TIME_PER_TICK) - timer); //sleep until next tick start
	}
}


void setUpEnemy(cgame& game) {
	cmap map = game.getMap();
	int NumOfPath = map.getNumOfPath();
	vector<cenemy*>& eList = game.getEnemy();
	int nEnemy[4], AllEnemy = 0;
	for (int i = 0; i < NumOfPath; i++) {
		nEnemy[i] = map.getEnemy(i);
		AllEnemy += nEnemy[i];
	}
	for (int i = 0; i < AllEnemy; i++) {
		eList.push_back(new cenemy());
		eList[i]->calPath(map.getEPath(i % NumOfPath));
	}
}

void NewGame(int n, cplayer& player) {
	cgame game;
	game.setPlayer(player);

	cmap& map = game.getMap();

	map.readMap(n);;
	setUpEnemy(game);
	
	game.getTower().push_back(map.getTPlaces()[1]);

	vector<cenemy*>& eList = game.getEnemy();

	//game.setIsExist1(true);
	thread t1(manageAllEnemy, ref(game), ref(eList));
	thread t2(manageTowerAndBullet, ref(game), ref(eList));

	//Main Loop for rendering
	while (!game.getIsExist1()) {
		/*for (auto x : game.getBullet())
			x.draw('*');
		for (auto x : game.getTower())
			x.draw();*/
		this_thread::sleep_for(micro(TIME_PER_FPS));
	}
	t1.join();
	t2.join();

}

int main() {
	cplayer p;
	NewGame(1,p);
	return 0;
}
