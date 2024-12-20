#include "SaveGame.h"

void SaveGame::setUserName(int userName) {
	this->userName = userName;
}
int SaveGame::getUserName() {
	return userName;
}
void SaveGame::setEnemyPos(vector<cpoint> enemyPos) {
	this->enemyPos = enemyPos;
}
vector<cpoint> SaveGame::getEnemyPos() {
	return enemyPos;
}
void SaveGame::setTowerPos(vector<cpoint> towerPos) {
	this->towerPos = towerPos;
}
vector<cpoint> SaveGame::getTowerPos() {
	return towerPos;
}
void SaveGame::setBulletPos(vector<cpoint> bulletPos) {
	this->bulletPos = bulletPos;
}
vector<cpoint> SaveGame::getBulletPos() {
	return bulletPos;
}
void SaveGame::setPoint(int point) {
	this->point = point;
}
int SaveGame::getPoint() {
	return point;
}
void SaveGame::setMapCode(int mapCode) {
	this->mapCode = mapCode;
}
int SaveGame::getMapCode() {
	return mapCode;
}
SaveGame::SaveGame(int userName, vector<cpoint> enemyPos, vector<cpoint> towerPos, vector<cpoint> bulletPos, int point, int mapCode) {
	this->userName = userName;
	this->enemyPos = enemyPos;
	this->towerPos = towerPos;
	this->bulletPos = bulletPos;
	this->point = point;
	this->mapCode = mapCode;
}
SaveGame::SaveGame() {
	this->mapCode = 0;
	this->userName = 0;
	this->point = 0;
	enemyPos = vector<cpoint>();
	towerPos = vector<cpoint>();
	bulletPos = vector<cpoint>();
}
