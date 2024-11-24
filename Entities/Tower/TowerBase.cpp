#include "TowerBase.h"

TowerBase::TowerBase(const TowerBase& other){
	model = other.model;
	currentPosition = other.currentPosition;
	lastShoot = std::chrono::system_clock::now();
}
TowerBase::TowerBase(TowerModel* nModel, cpoint pos){
	model = nModel;
	currentPosition = pos;
	lastShoot = std::chrono::system_clock::now();
}

void TowerBase::setCurrentPosition(const cpoint& pos){
	currentPosition = pos;
}
cpoint TowerBase::getCurrentPosition(){
	return currentPosition;
}

bool TowerBase::canShoot() {
	TIME_POINT now = chrono::system_clock::now();
	if (MILI_SEC(1000 / model->getRate()) < MILI_SEC_CAST(now - lastShoot)) {
		lastShoot = chrono::system_clock::now();
		return true;
	}
	return false;
}

bool TowerBase::canShoot(EnemyBase* target) {
	if (canShoot()
		&& target->getHealth() > 0
		&& currentPosition.distance(target->getCurrentPosition()) <= model->getRange()
		)
		return true;
	return false;
}

//virtual method
BulletBase TowerBase::shoot(EnemyBase* target) {
	lastShoot = chrono::system_clock::now();
	return BulletBase(model->getBulletModel(), currentPosition, target);
}