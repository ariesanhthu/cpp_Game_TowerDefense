#include "EnemyBase.h"

EnemyBase::EnemyBase(const EnemyBase& other) {
	model = other.model;
	currentPosition = other.currentPosition;
	health = other.health;
	path = other.path;
}

EnemyBase::EnemyBase(EnemyModel* nModel, int nPath) {
	model = nModel;
	health = model->getDefaultHealth();
	path = nPath;
}

EnemyBase::EnemyBase(EnemyModel* nModel, int nPath, int nHealth) {
	model = nModel;
	health = nHealth;
	path = nPath;
}
//EnemyBase();

void EnemyBase::setCurrentPosition(const cpoint& p) { 
	currentPosition = p; 
}
void EnemyBase::setHealth(int hp) { 
	health = hp; 
}

// get model attribute
int EnemyBase::getSpeed() {
	return model->getSpeed();
}
//getTexture();

//get private attribute
cpoint EnemyBase::getCurrentPosition() {
	return currentPosition;
}
int EnemyBase::getHealth() {
	return health;
}
