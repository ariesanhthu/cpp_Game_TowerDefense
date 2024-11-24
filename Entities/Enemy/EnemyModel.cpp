#include "EnemyModel.h"
EnemyModel::EnemyModel() {
	speed = 1;
	defaultHealth = 5;
}

EnemyModel::EnemyModel(int nSpeed, int hp) {
	speed = nSpeed;
	defaultHealth = hp;
}
//EnemyModel::EnemyModel(int nSpeed , texture);

void EnemyModel::setSpeed(int nSpeed){
	speed = nSpeed;
}
void EnemyModel::setDefaultHealth(int nHP) {
	defaultHealth = nHP;
}

int EnemyModel::getSpeed() {
	return speed;
}
int EnemyModel::getDefaultHealth() {
	return defaultHealth;
}

// getTexture();