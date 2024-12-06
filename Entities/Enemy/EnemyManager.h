#pragma once
#ifndef __ENEMY_MANAGER_h__
#define __ENEMY_MANAGER_h__

#include "EnemyModel.h"
#include "EnemyBase.h"
#include "chrono"

class EnemyManager
{
public:
    void addEnemy(EnemyModel* model, int path);

    void updateAllEnemy();

    void renderEnemies();

    void readFile(ifstream& i);

    void writeFile(ofstream& o);
private:
    std::vector<EnemyBase> enemies_;

    int nOfPhase;
    vector <int> nOfEnemyEachPhase;
    int phase;
    int remainEnemy;
    int nOfEnemy = 0;
    int spawnedEnemy = 0;
	const int enemySpawnInterval = 1;
	chrono::system_clock::time_point lastSpawn;
};

#endif