#include "GamePlayManage.h"

void GamePlayManage::setup(vector<vector<cpoint>> path) {
	//create Models
	EnemyFactory::createModels( path );
	BulletFactory::createModels();
	TowerFactory::createModels();

}
void GamePlayManage::startGame() {

}

void GamePlayManage::update(float delta) {
	//OutputDebugStringA("222222222222222222222222222222\n");
	if (enemyManager.getStatus() != PLAY) {
		gameStatus = enemyManager.getStatus();
	}
	else if (enemyManager.getStatus() == PLAY) {
		enemyManager.updateAllEnemy(delta);
		towerManager.updateAllTower(enemyManager.enemies_);
	}
}

void GamePlayManage::destroy() {
	EnemyFactory::deleteModels();
	BulletFactory::deleteModels();
	TowerFactory::deleteModels();
}