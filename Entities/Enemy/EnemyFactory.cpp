#include "EnemyFactory.h"

vector<EnemyModel*> EnemyFactory::Models;

unique_ptr<EnemyBase> EnemyFactory::createEnemy(const int type, int path) {
    if (type == 1) {
        return make_unique<EnemyBase>(Models[0], path);
    }
    else if (type == 2) {
        return make_unique<EnemyBase>(Models[1], path);
    }
    else if (type == 3) {
        return make_unique<EnemyBase>(Models[2], path);
    }
    else {
        throw invalid_argument("Unknown enemy type");
    }
}

void EnemyFactory::createModels() {
    Models.push_back(new EnemyModel(4, 5));
    Models.push_back(new EnemyModel(5, 10));
    Models.push_back(new EnemyModel(6, 15));
}

void EnemyFactory::deleteModels() {
    for (auto model : Models)
        delete model;
}