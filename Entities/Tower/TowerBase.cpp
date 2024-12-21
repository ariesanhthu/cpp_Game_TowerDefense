#include "TowerBase.h"

TowerBase::TowerBase(const TowerBase& other){
	bullet = BulletFactory::createBullet(0, NULL, cpoint(0, 0, 0));
	model = other.model;
	currentPosition = other.currentPosition;
	lastShoot = std::chrono::system_clock::now();
}
TowerBase::TowerBase(TowerModel* nModel, cpoint pos){
	bullet = BulletFactory::createBullet(0, NULL, cpoint(0, 0, 0));
	model = nModel;
	currentPosition = pos;
	lastShoot = std::chrono::system_clock::now();
}

TowerBase::TowerBase(const wchar_t* link, float factor, TowerModel* nModel, cpoint pos, int type) : UIElement(link, factor, { pos.getX(), pos.getY()}) {
	bullet = BulletFactory::createBullet(type, NULL, cpoint(0, 0, 0));
	model = nModel;
	currentPosition = pos;
	lastShoot = std::chrono::system_clock::now();
}

// rieng thang nay khong co
TowerBase::TowerBase(const wchar_t* link, float factor, cpoint pos) : model(nullptr), UIElement(link, factor, { pos.getX(), pos.getY() }) {
	currentPosition = pos;
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
	float dis = currentPosition.distance(target->getCurrentPosition());

	int range = model->getRange();

	if (target->getHealth() > 0 && dis <= range && target->getIndex() > 0) {
		//OutputDebugStringA("true shoot\n");
		return true;
	}
	//OutputDebugStringA("false shoot\n");

	return false;
}

//virtual method

//BulletBase TowerBase::shoot(shared_ptr<EnemyBase> target) {
//	lastShoot = chrono::system_clock::now();
//	return BulletBase(model->getBulletModel(), currentPosition, target);
//}

void TowerBase::shoot(shared_ptr<EnemyBase> target) {

	//OutputDebugStringA("true shoot\n");

	lastShoot = chrono::system_clock::now();
	bullet.get()->setCurr(this->currentPosition);
	bullet.get()->setTarget(target);
	bullet.get()->setVisible(true);
}
