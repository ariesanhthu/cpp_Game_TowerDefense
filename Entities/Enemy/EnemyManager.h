#pragma once
#ifndef __ENEMY_MANAGER_h__
#define __ENEMY_MANAGER_h__

#include "EnemyModel.h"
#include "EnemyBase.h"
#include "chrono"
#include <random>

class EnemyManager
{
public:
    //void addEnemy(EnemyModel* model, int path);
    void addEnemy(shared_ptr<EnemyBase> e);

    void updateAllEnemy(float delta);

    int getStatus() { return gameStatus; }

    void renderEnemies(HDC hdc);

    void readFile(ifstream& i);

    void writeFile(ofstream& o);

    int getRandomInterval(int min, int max);

    void setup(vector<int> ar);

    std::vector<shared_ptr<EnemyBase>> enemies_;

private:

    int nOfPhase = 3;                       // số lượng phase
    vector <int> nOfEnemyEachPhase;     // số lượng e mỗi phase
    int phase = 0;                          // phase hiện tại 
    int remainEnemy = 0;                    // số lượng e còn lại trên màn hình
    int nOfEnemy = 0;                   // số lượng e 
    int spawnedEnemy = 0;               // số lượng e đã spawn
	const int enemySpawnInterval = 1;   // tốc độ spawn e
	chrono::system_clock::time_point lastSpawn; 

    enum GameStatus {
        PLAY = 0,
        WIN = 1,
        LOSE = 2
    };

    int gameStatus = PLAY;                 // 1 is no enemy left, 2 is enemy reaches the end
};

#endif