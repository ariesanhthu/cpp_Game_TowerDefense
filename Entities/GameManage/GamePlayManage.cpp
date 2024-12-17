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
	

	if (enemyManager.getStatus() != PLAY) {
		gameStatus = enemyManager.getStatus();
	}
	else if (enemyManager.getStatus() == PLAY) {
		enemyManager.updateAllEnemy();
		//towerManager.updateAllTower(enemyManager.enemies_);
	}
}

void GamePlayManage::destroy() {
	EnemyFactory::deleteModels();
	BulletFactory::deleteModels();
	TowerFactory::deleteModels();
}