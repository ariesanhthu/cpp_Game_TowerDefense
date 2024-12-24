#include "TowerManager.h" // Header định nghĩa TowerManager
//#include "EventManager.h"// Header của EventManager
//#include "GameEvent.h"    // Header của GameEvent
#include "AudioManager.h"


void TowerManager::addTower(TowerModel* model, cpoint pos) {

}
void TowerManager::addTower(shared_ptr<TowerBase> tower) {
	//towers_.push_back(tower);

	for (int i = 0; i < MaxOfEachType.size(); i++) {
		if (tower->getType() == i) {
			if (NOfEachType[i] < MaxOfEachType[i]) {
				towers_.push_back(tower);
				NOfEachType[i]++;
				break;
			}
		}
	}

}
void TowerManager::setNOfTowerType(vector<int> _NOfTowerType) {
	MaxOfEachType = _NOfTowerType;
	NOfEachType.resize(MaxOfEachType.size());
	for (auto i : NOfEachType) {
		i = 0;
	}
}

void TowerManager::renderTowers(HDC hdc) {
	for (auto t : towers_) {
		t->render(hdc);

		std::shared_ptr<BulletBase> bullet = t->getBullet();
		
		if (bullet->getVisible()) bullet->render(hdc);
	}
}

void TowerManager::updateAllTower(std::vector<shared_ptr<EnemyBase>>& enemies_, float delta) {
	for (auto& tower : towers_) {

		if (tower->canShoot() && !tower->getBullet()->getVisible()) {
			for (auto& enemy : enemies_) {

				if (tower->canShoot(enemy)) {

					tower->shoot(enemy);

					break;
				}
			}
		}

		// update bullet of tower
		if (tower->getBullet()->getVisible()) {
			shared_ptr<BulletBase> bullet = tower->getBullet();
			bullet->update(delta);

			shared_ptr<EnemyBase> e = bullet->checkCollision();
			if (e != NULL) {
				e->hit(bullet->getDame());
				bullet->setVisible(false);

				//  =========================== EVENT HIT =======================================

				/*auto& audioManager = towerdefense::AudioManager::getInstance();
				audioManager.playSoundEffect("explosion");*/

				/*auto& eventManager = towerdefense::EventManager::getInstance();
				eventManager.triggerEvent(GameEvent::Hit);*/
				

				//======================================================================================
			}

			tower->setBullet(bullet);
		}
	}
}

std::vector<std::shared_ptr<TowerBase>> TowerManager::getAllTower() const {
	return towers_;
}

std::vector<std::shared_ptr<BulletBase>> TowerManager::getAllBullet() const {
	std::vector<std::shared_ptr<BulletBase>> bullets;
	for (auto& t : towers_) {
		std::shared_ptr<BulletBase> bullet = t->getBullet();
		bullets.push_back(bullet);
	}
	return bullets;
}

void TowerManager::setLoadTower(std::vector<shared_ptr<TowerBase>> listtower) {
	for (int i = 0; i < towers_.size(); i++) {
		towers_[i]->setCurrentPosition(listtower[i]->getCurrentPosition());
	}
}

void TowerManager::setNOfTower(int x) {
	this->nOfTower = x;
}
int TowerManager::getNOfTower() {
	return nOfTower;
}

