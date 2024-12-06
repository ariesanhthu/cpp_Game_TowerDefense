#include "EnemyManager.h"

void EnemyManager::addEnemy(EnemyModel* model, int path) {
    enemies_.emplace_back(model, path);
}

void EnemyManager::updateAllEnemy() {
    if (remainEnemy == 0 && spawnedEnemy >= nOfEnemy) {
        if (phase < nOfPhase) {
            phase++;
            nOfEnemy += nOfEnemyEachPhase[phase];
        }
        else {
            //game exit
        }
    }
    remainEnemy = 0;
    chrono::system_clock::time_point now;
    if (    std::chrono::duration_cast<chrono::milliseconds> (now - lastSpawn) > chrono::milliseconds(1000 * enemySpawnInterval)
        &&  spawnedEnemy < nOfEnemy
    ) {

        spawnedEnemy++;
        lastSpawn = now;
    }

    for (int i = 0; i < spawnedEnemy; i++) {
        if (enemies_[i].getHealth() > 0) {
            enemies_[i].update();
            remainEnemy++;
        }
    }
}

void EnemyManager::renderEnemies() {
    for (auto& enemy : enemies_) {
        //enemy.render();
    }
}


void EnemyManager::readFile(ifstream& i) {
    
}

void EnemyManager::writeFile(ofstream& o) {

}