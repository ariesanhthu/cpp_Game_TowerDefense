#include "BulletBase.h"

//BulletBase();
BulletBase::BulletBase(const BulletBase& other) {
	model = other.model;
	currentPosition = other.currentPosition;
}
BulletBase::BulletBase(BulletModel* nModel, cpoint pos, EnemyBase* nTarget) {
	model = nModel;
	currentPosition = pos;
	target = nTarget;
}

void BulletBase::setCurr(const cpoint& p) { 
	currentPosition = p; 
}
void BulletBase::setTarget(EnemyBase* nTarget) { 
	target = nTarget; 
}

// get model attribute
int BulletBase::getDame() { 
	return model->getDame(); 
}
int BulletBase::getSpeed() {
	return model->getDame(); 
}

// get private attribute
cpoint BulletBase::getCurr() { 
	return currentPosition;
}
EnemyBase* BulletBase::getTarget() { 
	return target; 
}

// check collision
EnemyBase* BulletBase::checkCollision() {
	if (currentPosition.distance(target->getCurrentPosition()) < model->getSpeed()) {
		return target;
	}
	return NULL;
}

//virtual method
// update position
void BulletBase::update() { // cal next position of bullet
	cpoint e = target->getCurrentPosition();

	cpoint derection = e - currentPosition;
	cpoint normalizedDirection = derection.normalized();
	this->currentPosition = this->currentPosition + normalizedDirection * model->getSpeed();
}
