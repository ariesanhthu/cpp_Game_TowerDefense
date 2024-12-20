#pragma once

#include <string>
#include "cpoint.h"
#include <vector>

using namespace std;

class SaveGame {
private:
	string userName; // primary key

	vector<cpoint> enemyPos;
	vector<int> enemyHealth;
	vector<int> enemyPathNumber;

	vector<cpoint> towerPos;
	vector<cpoint> bulletPos;

	int userHealth;
	int point;
	int mapCode;

public:
	SaveGame(string userName,
		vector<cpoint> enemyPos,
		vector<int> enemyHealth,
		vector<int> enemyPathNumber,
		vector<cpoint> towerPos,
		vector<cpoint> bulletPos,
		int point,
		int mapCode,
		int userHealth
	);
	SaveGame();

	// get set
	void setUserName(string userName);
	string getUserName();
	void setEnemyPos(vector<cpoint> enemyPos);
	vector<cpoint> getEnemyPos();
	void setEnemyHealth(vector<int> enemyHealth);
	vector<int> getEnemyHealth();
	void setEnemyPathNumber(vector<int> enemyPathNumber);
	vector<int> getEnemyPathNumber();
	void setTowerPos(vector<cpoint> towerPos);
	vector<cpoint> getTowerPos();
	void setBulletPos(vector<cpoint> bulletPos);
	vector<cpoint> getBulletPos();
	void setPoint(int point);
	int getPoint();
	void setMapCode(int mapCode);
	int getMapCode();
	void setUserHealth(int userHealth);
	int getUserHealth();
};
