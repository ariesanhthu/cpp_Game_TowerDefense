#include "EnemyManager.h"

//void EnemyManager::addEnemy(EnemyModel* model, int path) {
//    enemies_.emplace_back(model, path);
//}

int EnemyManager::getRandomInterval(int min, int max) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);
    return uni(rng);
}

void EnemyManager::addEnemy(shared_ptr<EnemyBase> e) {
    enemies_.push_back(e);
    //nOfEnemy++;
}

void EnemyManager::updateAllEnemy(float delta) {

    // phase control
    if (remainEnemy == 0 && spawnedEnemy >= nOfEnemy) {
        if (phase < nOfPhase) {
            nOfEnemy += nOfEnemyEachPhase[phase];
            phase++;
        }
        else {
            //game exit
            gameStatus = WIN;
        }
    }

    // Spawn interval
    remainEnemy = 0;

    chrono::system_clock::time_point now = chrono::system_clock::now();

    static int nextSpawnDelay = getRandomInterval(50000, 20000000);

    if (std::chrono::duration_cast<chrono::milliseconds> (now - lastSpawn) > chrono::milliseconds(1000 * enemySpawnInterval) &&  spawnedEnemy < nOfEnemy) {
        spawnedEnemy++;
        lastSpawn = now;
        nextSpawnDelay = getRandomInterval(50000, 20000000);
    }

    // update remain e
    int gameHP = gameHPDefaul;
    for (int i = 0; i < spawnedEnemy; i++) {
        if (enemies_[i]->getHealth() > 0) {

            if (enemies_[i]->update(delta))
                gameHP--;

            //enemies_[i]->update(delta);
            else
                remainEnemy++;
        }

    }

    if (gameHP <= 0) gameStatus = 2;
}

void EnemyManager::renderEnemies(HDC hdc) {
    //OutputDebugStringA("CCCCCCCCCCCCCCCCCCCCCCCc\n");
    if (gameStatus == PLAY) {
        for (auto& enemy : enemies_) {
            enemy->render(hdc);
        }
    }
}


void EnemyManager::readFile(ifstream& i) {
    
}

void EnemyManager::writeFile(ofstream& o) {

}

void EnemyManager::setup(vector<int> ar) {
    nOfPhase = ar[0];
    for (int i = 0; i < nOfPhase; i++) {
        nOfEnemyEachPhase.push_back(ar[i + 1]);
    }
}