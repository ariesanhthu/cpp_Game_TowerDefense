#include "EnemyBase.h"

EnemyBase::EnemyBase(const EnemyBase& other) {
	model = other.model;
	currentPosition = other.currentPosition;
	health = other.health;
}

EnemyBase::EnemyBase(EnemyModel* nModel, cpoint pos) {
	model = nModel;
	currentPosition = pos;
	health = model->getDefaultHealth();
}

EnemyBase::EnemyBase(EnemyModel* nModel, cpoint pos, int nHealth) {
	model = nModel;
	currentPosition = pos;
	health = nHealth;
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
