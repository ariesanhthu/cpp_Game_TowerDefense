#include "GamePlayManage.h"

void GamePlayManage::setup() {
	//create Models
	EnemyFactory::createModels();
	BulletFactory::createModels();
	TowerFactory::createModels();

}
void GamePlayManage::startGame() {

}
void GamePlayManage::update() {

}

void GamePlayManage::destroy() {
	EnemyFactory::deleteModels();
	BulletFactory::deleteModels();
	TowerFactory::deleteModels();
}