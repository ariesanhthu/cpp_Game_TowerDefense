#include "SaveGame.h"

void SaveGame::setUserName(string userName) {
	this->userName = userName;
}
string SaveGame::getUserName() {
	return userName;
}
void SaveGame::setEnemyPos(vector<cpoint> enemyPos) {
	this->enemyPos = enemyPos;
}
vector<cpoint> SaveGame::getEnemyPos() {
	return enemyPos;
}
void SaveGame::setEnemyHealth(vector<int> enemyHealth) {
	this->enemyHealth = enemyHealth;
}
vector<int> SaveGame::getEnemyHealth() {
	return enemyHealth;
}
void SaveGame::setEnemyPathNumber(vector<int> enemyPathNumber) {
	this->enemyPathNumber = enemyPathNumber;
}
vector<int> SaveGame::getEnemyPathNumber() {
	return enemyPathNumber;
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
int SaveGame::getUserHealth() {
	return userHealth;
}
void SaveGame::setUserHealth(int userHealth) {
	this->userHealth = userHealth;
}
SaveGame::SaveGame(string userName,
	vector<cpoint> enemyPos,
	vector<int> enemyHealth,
	vector<int> enemyPathNumber,
	vector<cpoint> towerPos,
	vector<cpoint> bulletPos,
	int point,
	int mapCode,
	int userHealth) {
	this->userName = userName;
	this->enemyPos = enemyPos;
	this->enemyHealth = enemyHealth;
	this->enemyPathNumber = enemyPathNumber;
	this->towerPos = towerPos;
	this->bulletPos = bulletPos;
	this->point = point;
	this->mapCode = mapCode;
	this->userHealth = userHealth;
}
SaveGame::SaveGame() {
	this->userName = "guess";
	this->point = 0;
}
