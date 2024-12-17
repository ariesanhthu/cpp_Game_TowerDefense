#include "TowerManager.h"

void TowerManager::addTower(TowerModel* model, cpoint pos) {
	//shared_ptr<TowerBase> tower = TowerFactory::createTower(1);
	//towers_.emplace_back(model, pos);
}
void TowerManager::addTower(shared_ptr<TowerBase> tower) {
	towers_.push_back(tower);
}
void TowerManager::renderTowers() {

}

void TowerManager::updateAllTower(std::vector<shared_ptr<EnemyBase>>& enemies_) {
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
			bullet->update();

			shared_ptr<EnemyBase> e = bullet->checkCollision();
			if (e != NULL) {
				e->hit(bullet->getDame());
				bullet->setVisible(false);
			}

		}
	}
}