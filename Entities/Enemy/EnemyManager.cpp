#include "EnemyManager.h"

void EnemyManager::addEnemy(EnemyModel* model, cpoint pos) {
    enemies_.emplace_back(model, pos);
}

void EnemyManager::renderEnemies() {
    for (auto& enemy : enemies_) {
        //enemy.render();
    }
}