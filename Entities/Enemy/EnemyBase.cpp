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
void EnemyBase::update(){
	currentPosition = model->getPath(path)[index++];
}

void EnemyBase::hit(int n){
	health -= n;
}