#include "TowerManager.h"

void TowerManager::addTower(TowerModel* model, cpoint pos) {
	towers_.emplace_back(model, pos);
}
void TowerManager::addTower(TowerBase tower) {
	towers_.emplace_back(tower);
}
void TowerManager::renderTowers() {

}