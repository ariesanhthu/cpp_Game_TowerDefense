#include "BulletModel.h"

BulletModel::BulletModel() {
	dame = 1;
	speed = 3;
}
BulletModel::BulletModel(int nDame, int nSpeed) {
	dame = nDame;
	speed = nSpeed;
}

//BulletModel::BulletModel(int nDame, int nSpeed , texture);

int BulletModel::getDame() {
	return dame;
}
int BulletModel::getSpeed() {
	return speed;
}