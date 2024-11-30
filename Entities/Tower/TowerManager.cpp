#include "TowerManager.h"

void TowerManager::addTower(TowerModel* model, cpoint pos) {
	towers_.emplace_back(model, pos);
}
void TowerManager::addTower(TowerBase tower) {
	towers_.emplace_back(tower);
}
void TowerManager::renderTowers() {

}

void TowerManager::updateAllTower(std::vector<EnemyBase>& enemies_, std::vector<BulletBase>& bulllets_) {
	for (TowerBase& tower : towers_) {
		if (tower.canShoot()) {
			for (EnemyBase& enemy : enemies_) {
				if (tower.canShoot(&enemy)) {
					BulletBase bullet = tower.shoot(&enemy);
					bulllets_.push_back(bullet);
					break;
				}
			}
		}
	}
}