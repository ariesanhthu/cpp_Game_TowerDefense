#include "EnemyManager.h"

void EnemyManager::addEnemy(EnemyModel* model, cpoint pos) {
    enemies_.emplace_back(model, pos);
}

void EnemyManager::updateAllEnemy() {
    for (EnemyBase& e : enemies_) {
        if (e.getHealth() > 0)
            e.update();
    }
}

void EnemyManager::renderEnemies() {
    for (auto& enemy : enemies_) {
        //enemy.render();
    }
}
