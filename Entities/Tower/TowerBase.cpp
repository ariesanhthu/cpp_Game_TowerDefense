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

void TowerBase::setBullet(shared_ptr<BulletBase> bullet) {
	this->bullet = bullet;
}

shared_ptr<BulletBase> TowerBase::getBullet() {
	return bullet;
}

bool TowerBase::canShoot() {
	TIME_POINT now = chrono::system_clock::now();
	if (MILI_SEC(1000 / model->getRate()) < MILI_SEC_CAST(now - lastShoot)) {
		lastShoot = chrono::system_clock::now();
		return true;
	}
	return false;
}

bool TowerBase::canShoot(shared_ptr<EnemyBase> target) {
	if (canShoot()
		&& target->getHealth() > 0
		&& currentPosition.distance(target->getCurrentPosition()) <= model->getRange()
		)
		return true;
	return false;
}

//virtual method

//BulletBase TowerBase::shoot(shared_ptr<EnemyBase> target) {
//	lastShoot = chrono::system_clock::now();
//	return BulletBase(model->getBulletModel(), currentPosition, target);
//}

void TowerBase::shoot(shared_ptr<EnemyBase> target) {
	lastShoot = chrono::system_clock::now();
	bullet.get()->setCurr(this->currentPosition);
	bullet.get()->setTarget(target);
	bullet.get()->setVisible(true);
}