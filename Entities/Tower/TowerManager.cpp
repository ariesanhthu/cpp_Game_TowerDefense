#include "TowerManager.h"

void TowerManager::addTower(TowerModel* model, cpoint pos) {

}
void TowerManager::addTower(shared_ptr<TowerBase> tower) {
	if (nOfTower --> 0)
		towers_.push_back(tower);
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

