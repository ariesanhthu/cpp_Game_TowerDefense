#pragma once

#include <string>
#include "cpoint.h"
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

class SaveGame {
private:
	string userName; // primary key

	// enemy struct
	vector<cpoint> enemyPos;
	vector<int> enemyHealth;
	vector<int> enemyPathNumber;
	vector<int> enemyIndex;
	vector<int> enemyType;

	// manager
	int nOfPhase;
	vector<int> nOfEnemyEachPhase;
	int phase;
	int remainEnemy;
	int nOfEnemy;
	int spawnedEnemy;

	// tower struct
	vector<cpoint> towerPos;
	vector<int> towerType;


	// optional
	//vector<cpoint> bulletPos;


	// other
	int userHealth;
	int point;
	int mapCode;

public:
	SaveGame(
		string userName,

		vector<cpoint> enemyPos,
		vector<int> enemyHealth,
		vector<int> enemyPathNumber,
		vector<int> enemyIndex,
		vector<int> enemyType,


		vector<cpoint> towerPos,
		vector<int> towerType,
		//vector<cpoint> bulletPos,

		int nOfPhase,
		vector<int> nOfEnemyEachPhase,
		int phase,
		int remainEnemy,
		int nOfEnemy,
		int spawnedEnemy,

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
	void setEnemyIndex(vector<int> enemyIndex);
	vector<int> getEnemyIndex();
	void setTowerPos(vector<cpoint> towerPos);
	vector<cpoint> getTowerPos();
	//void setBulletPos(vector<cpoint> bulletPos);
	//vector<cpoint> getBulletPos();
	void setPoint(int point);
	int getPoint();
	void setMapCode(int mapCode);
	int getMapCode();
	void setUserHealth(int userHealth);
	int getUserHealth();

	void setTowerType(vector<int> type); 
	vector<int> getTowerType();
	void setEnemyType(vector<int> type);
	vector<int> getEnemyType();


	// manager
	int getNOfPhase();
	void setNOfPhase(int vae);

	std::vector<int> getNOfEnemyEachPhase();
	void setNOfEnemyEachPhase(std::vector<int> value);

	int getPhase();
	void setPhase(int value);

	int getRemainEnemy();
	void setRemainEnemy(int value);

	int getNOfEnemy();
	void setNOfEnemy(int value);

	int getSpawnedEnemy();
	void setSpawnedEnemy(int value);

	void writefile(int mapCode);
	void supportWriteFile(std::string filename);

	void debugSaving();
	SaveGame readfile();
};

class SaveGameSupport {
private: 
	std::vector<SaveGame> listGame = {};

public:
	SaveGameSupport();
	void writefile();
	std::vector<SaveGame> readfile();
	std::vector<SaveGame> loadFourLastestMapGame();
	std::vector<SaveGame> loadFourHighestScoreMap();
	SaveGame readMap(std::string filename);
	SaveGame readMapInfo(int x);
	void sortByScore();
};