#include "TowerManager.h"

void TowerManager::addTower(TowerModel* model, cpoint pos) {
	//shared_ptr<TowerBase> tower = TowerFactory::createTower(1);
	//towers_.emplace_back(model, pos);
}
void TowerManager::addTower(shared_ptr<TowerBase> tower) {
	towers_.push_back(tower);
}
void TowerManager::renderTowers(HDC hdc) {
	for (auto t : towers_) {
		t->render(hdc);

		std::shared_ptr<BulletBase> bullet = t->getBullet();
		
		if (bullet->getVisible()) bullet->render(hdc);
	}
}

void TowerManager::updateAllTower(std::vector<shared_ptr<EnemyBase>>& enemies_) {
	//OutputDebugStringA("33333333333333333333\n");
	for (auto& tower : towers_) {

		if (tower->canShoot() && !tower->getBullet()->getVisible()) {
			for (auto& enemy : enemies_) {
				
				/*OutputDebugStringA( 
					(
						"pos: " + std::to_string(enemy->getCurrentPosition().getX()) + " " + std::to_string(enemy->getCurrentPosition().getY()) + "\n" +
						"health: " + std::to_string(enemy->getHealth()) + "\n"
					).c_str() 
				);*/

				if (tower->canShoot(enemy)) {

					tower->shoot(enemy);
					OutputDebugStringA("d\n");

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