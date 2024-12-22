#include "BulletBase.h"

//BulletBase();
BulletBase::BulletBase(const BulletBase& other) {
	model = other.model;
	currentPosition = other.currentPosition;
}
BulletBase::BulletBase(BulletModel* nModel, cpoint pos, shared_ptr<EnemyBase> nTarget) {
	model = nModel;
	currentPosition = pos;
	target = nTarget;
}

BulletBase::BulletBase(const wchar_t* link, float factor, BulletModel* nModel, cpoint pos, shared_ptr<EnemyBase> nTarget) : UIElement(link, factor, {pos.getX(), pos.getY()}) 
{
	model = nModel;
	currentPosition = pos;
	target = nTarget;
}
//--------- animation constructor -------
BulletBase::BulletBase(const std::vector<std::wstring>& imagePaths, float factor, BulletModel* nModel, cpoint pos, shared_ptr<EnemyBase> nTarget) : UIElement(imagePaths, factor, { pos.getX(), pos.getY() })
{
	model = nModel;
	currentPosition = pos;
	target = nTarget;
}
//---------------------------------------
void BulletBase::setCurr(const cpoint& p) { 
	currentPosition = p; 
}
void BulletBase::setTarget(shared_ptr<EnemyBase> nTarget) { 
	target = nTarget; 
}
void BulletBase::setVisible(bool vis) {
	visible = vis;
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
shared_ptr<EnemyBase> BulletBase::getTarget() { 
	return target; 
}
bool BulletBase::getVisible() {
	return visible;
}

// check collision
shared_ptr<EnemyBase> BulletBase::checkCollision() {
	if (currentPosition.distance(target->getCurrentPosition()) < model->getSpeed()) {
		return target;
	}
	return NULL;
}

//virtual method
// update position
void BulletBase::update(float delta) { // cal next position of bullet
	//  -------------------- animation -------------------
	updateUI(delta);
	// ---------------------------------------------------

	cpoint e = target->getCurrentPosition();

	cpoint direction = e - currentPosition;
	float length = std::sqrt(static_cast<float>(direction.getX() * direction.getX() + direction.getY() * direction.getY()));
	cpoint normalizedDirection = direction.normalized(length , model->getSpeed());
	this->currentPosition = this->currentPosition + normalizedDirection;
}
