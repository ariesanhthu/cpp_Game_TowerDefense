#pragma once

#include <string>
#include "cpoint.h"
#include <vector>

using namespace std;

class SaveGame {
private:
	int userName; // primary key
	vector<cpoint> enemyPos;
	vector<cpoint> towerPos;
	vector<cpoint> bulletPos;
	int point;
	int mapCode;

public:
	SaveGame(int userName, vector<cpoint> enemyPos, vector<cpoint> towerPos, vector<cpoint> bulletPos, int point, int mapCode);
	SaveGame();

	// get set
	void setUserName(int userName);
	int getUserName();
	void setEnemyPos(vector<cpoint> enemyPos);
	vector<cpoint> getEnemyPos();
	void setTowerPos(vector<cpoint> towerPos);
	vector<cpoint> getTowerPos();
	void setBulletPos(vector<cpoint> bulletPos);
	vector<cpoint> getBulletPos();
	void setPoint(int point);
	int getPoint();
	void setMapCode(int mapCode);
	int getMapCode();
};

