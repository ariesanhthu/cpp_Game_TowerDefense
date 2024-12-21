#include "TowerModel.h"

TowerModel::TowerModel(){
	range = 30;
	rate = 1000;
	bulletModel = nullptr;
}
TowerModel::TowerModel(const TowerModel& other) {
	range = other.range;
	rate = other.rate;
	bulletModel = other.bulletModel;
}
TowerModel::TowerModel(int nRange, int nRate, BulletModel* nBulletModel) {
	range = nRange;
	rate = nRate;
	bulletModel = nBulletModel;
}

void TowerModel::setRange(int nRange){
	range = nRange;
}
void TowerModel::setRate(int nRate){
	rate = nRate;
}
void TowerModel::setBulletModel(BulletModel* nBulletModel){
	bulletModel = nBulletModel;
}

int TowerModel::getRange(){
	return range;
}
int TowerModel::getRate(){
	return rate;
}
BulletModel* TowerModel::getBulletModel(){
	return bulletModel;
}