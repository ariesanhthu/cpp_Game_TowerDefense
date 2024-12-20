#include "EnemyFactory.h"

vector<EnemyModel*> EnemyFactory::Models;

 shared_ptr<EnemyBase> EnemyFactory::createEnemy(const int type, int path) {
    if (type == 1) {
        return make_shared<EnemyBase>(L"Assets/game/enemy5/enemy5-0.png", 0.8, Models[0], path);
    }
    else if (type == 2) {
        return make_shared<EnemyBase>(L"Assets/game/enemy2/enemy1-1.png", 2, Models[1], path);
    }
    else if (type == 3) {
        return make_shared<EnemyBase>(L"Assets/game/enemy3/enemy3-1.png", 2, Models[2], path);
    }
    else {
        throw invalid_argument("Unknown enemy type");
    }
}

void EnemyFactory::createModels(vector<vector<cpoint>> path) {
    Models.push_back(new EnemyModel(4, 5));  // small 
    Models.push_back(new EnemyModel(5, 10)); // big
    Models.push_back(new EnemyModel(6, 15)); // boss
    Models[0]->calculatePath(path);
    Models[1]->calculatePath(path);
    Models[2]->calculatePath(path);
}

void EnemyFactory::deleteModels() {
    for (auto model : Models)
        delete model;
    Models.clear();
}