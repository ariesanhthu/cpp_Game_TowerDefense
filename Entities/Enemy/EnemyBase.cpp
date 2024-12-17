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
EnemyBase::EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath, int nHealth) : UIElement(link, factor, {0, 0}) {
	model = nModel;
	health = nHealth;
	path = npath;
}

EnemyBase::EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath) : UIElement(link, factor, { 0, 0 }) {
	model = nModel;
	health = model->getDefaultHealth();
	path = npath;
	health = model->getDefaultHealth();
}

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

// file
void EnemyBase::writeFile(ostream& o) {
	o.write((char*)&health, sizeof(int));
	o.write((char*)&currentPosition, sizeof(cpoint));
	o.write((char*)&index, sizeof(int));
	o.write((char*)&path, sizeof(int));
}
void EnemyBase::readFile(istream& i) {
	i.read((char*)&health, sizeof(int));
	i.read((char*)&currentPosition, sizeof(cpoint));
	i.read((char*)&index, sizeof(int));
	i.read((char*)&path, sizeof(int));
}

//update
bool EnemyBase::update(float delta) {
	OutputDebugStringA("4444444444444\n");
	if (index < model->getPath(path).size() - 1 - model->getSpeed()) {
		currentPosition = model->getPath(path)[index += model->getSpeed()];

		// for test
		if (index >= model->getPath(path).size() - 5) {
			index = 0;
		}


		return false;
	}
	else {
		return true;
	}
}

void EnemyBase::hit(int n){
	if (health < n) isDead = 1;
	else health -= n;
}