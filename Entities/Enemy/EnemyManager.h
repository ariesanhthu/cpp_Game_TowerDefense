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

    int nOfPhase; // số lượng phase
    vector <int> nOfEnemyEachPhase; // số lượng e mỗi phase
    int phase; // phase hiện tại 
    int remainEnemy;  // số lượng e còn lại trên màn hình
    int nOfEnemy = 0; // số lượng e 
    int spawnedEnemy = 0; // số lượng e đã spawn
	const int enemySpawnInterval = 1; // tốc độ spawn e
	chrono::system_clock::time_point lastSpawn; 
};

#endif