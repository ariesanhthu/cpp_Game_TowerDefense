#include "PrecompiledHeader.h"
#include "constant.h"
using namespace std;

mutex gameMutex;

void manageAllEnemy(cgame& game, vector<cenemy*>& eList) {
	//vector<cenemy*>& eList = game.getEnemy();
	int eListSize = 0;
	int numberOfE = 0;
	int remainE = 0;
	int updatedE = 0;
	int enemyOfEachPhase = (eList.size() - game.getMap().getMapCode()) / 2; // number of e each phase
	int phase = 0;
	const int enemySpawnInterval = 1;
	time_point lastSpawn = chrono::system_clock::now();

	while (!game.getIsExist1()) {

		time_point start = chrono::system_clock::now();

		// phase control
		if (remainE == 0) {
			if (phase < 2) {
				eListSize += enemyOfEachPhase;
			}
			else if (phase < 3){
				eListSize += game.getMap().getMapCode();
			}
			else {
				game.setIsExist1(true);
				break;
			}
			phase++;
		}
		
		//dellay spawn
		if (micro_cast(start - lastSpawn) > micro(1000000 * enemySpawnInterval) && numberOfE < eListSize ) {
			numberOfE++;
			lastSpawn = chrono::system_clock::now();
		}

		// update all available enemy
		remainE = 0;
		updatedE = 0;
		for (cenemy* e : eList) {
			if (updatedE > numberOfE) break;
			updatedE++;
			if (e->getHealth() <= 0) continue;

			e->draw();
			//e->update();

			remainE++;
			if (e->isEnd()) game.setIsExist1(true);
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
	int can_shoot = 3;
	while (!game.getIsExist1()) {
		
		time_point start = chrono::system_clock::now();

		// update all available tower
		for (ctower& tower : tList) {
			if (tower.canShoot()) {
				for (cenemy* enemy : eList) {

					if (tower.getLocation().distance(enemy->getCurr()) < tower.getRange() && enemy->getHealth() > 0) {
						cbullet nBullet = tower.shoot(enemy);

						bList.push_back(nBullet);

				can_shoot--;
						break;
					}
				}
			}
		}

		//update all available bullet
		if (!bList.empty())
		/*for (cbullet& bullet: bList){*/
		for(vector<cbullet>::iterator it = bList.begin(); it != bList.end();){
			cbullet& bullet = *it;

			bullet.update();
			
			cenemy* e = bullet.checkCollision();
			if (e == NULL) {
				++it;
			}
			else {
				e->hit(bullet.getDame());
				it = bList.erase(it);
			}
			e = NULL;
			//++it;
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
	//for (int i = 0; i < NumOfPath; i++) {
	for (int i = 0; i < 4; i++) {
		nEnemy[i] = map.getEnemy(i);
		AllEnemy += nEnemy[i];
	}
	for (int i = 0; i < AllEnemy; i++) {
		eList.push_back(new cenemy());
		eList[i]->calPath(map.getEPath(i % NumOfPath));
	}

	//add boss
	/*for (int i = 0; i < game.getMap().getMapCode(); i++) {
		eList.push_back(new cenemy());
		eList[i]->calPath(map.getEPath(i % NumOfPath));
	}*/
}

void NewGame(int n, cplayer& player) {
	cgame game;
	game.setPlayer(player);

	cmap& map = game.getMap();

	map.readMap(n);;
	setUpEnemy(game);
	
	game.getTower().push_back(map.getTPlaces()[1]);
	game.getTower().push_back(map.getTPlaces()[3]);

	vector<cenemy*>& eList = game.getEnemy();

	//game.setIsExist1(true);

	thread t1(manageAllEnemy, ref(game), ref(eList));
	thread t2(manageTowerAndBullet, ref(game), ref(eList));

	//Main Loop for rendering
	while (!game.getIsExist1()) {
		/*for (cbullet x : game.getBullet())
			x.draw('*');*/
		for (ctower x : game.getTower())
			x.draw();
		this_thread::sleep_for(micro(TIME_PER_FPS));
	}

	t1.join();
	t2.join();

}

int main() {
	cplayer p;
	NewGame(2,p);
	return 0;
}
