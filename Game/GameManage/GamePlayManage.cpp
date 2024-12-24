#include "GamePlayManage.h"

void GamePlayManage::setupEnemy(vector<vector<cpoint>> path) {
	//create Models
	EnemyFactory::createModels( path );
	BulletFactory::createModels();
	TowerFactory::createModels();

}

void GamePlayManage::setupTower() {
	//create Models
	//EnemyFactory::createModels(path);
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
		towerManager.updateAllTower(enemyManager.getEnemy(), delta);

		point = 0;
		for (auto e : enemyManager.getEnemy()) {
			if (e->getHealth() <= 0) {
				point += 10;
			}
			
		}
		// ------------ CẬP NHẬT ĐIỂM TRỪ -------------------
		   // Máu đầy thì không trừ
		   // --------------------------------------------------
		int decPoint = enemyManager.getUserHP() % 5;
		if (decPoint > 0)
		{
			point -= ((5 - decPoint) * 10);
		}
	}
}

void GamePlayManage::destroy() {
	EnemyFactory::deleteModels();
	BulletFactory::deleteModels();
	TowerFactory::deleteModels();
}

//setter
void GamePlayManage::setGameCode(int code) {
	gameCode = code;
}
void GamePlayManage::setGameStatus(int status) {
	gameStatus = status;
}
void GamePlayManage::setPoint(int point) {
	this->point = point;
}
//getter
int GamePlayManage::getGameCode() {
	return gameCode;
}
int GamePlayManage::getGameStatus() {
	return gameStatus;
}
int GamePlayManage::getPoint() {
	return point;
}

