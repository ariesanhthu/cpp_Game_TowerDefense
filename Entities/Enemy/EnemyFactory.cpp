#include "EnemyFactory.h"

vector<EnemyModel*> EnemyFactory::Models;

 shared_ptr<EnemyBase> EnemyFactory::createEnemy(const int type, int path) {
    auto& resource = ResourceManager::getInstance();
    resource.loadResources();
    
    if (type == 1) {
        return make_shared<EnemyBase>(resource.getResource("enemy5"), 0.8, Models[0], path
        );
    }
    else if (type == 2) {
        return make_shared<EnemyBase>(resource.getResource("enemy2"), 2.5, Models[1], path);
    }
    else if (type == 3) {
        return make_shared<EnemyBase>(resource.getResource("enemy3"), 2.5, Models[2], path);
    }// goblin nước - level 1 chỉ khác UI
    else if (type == 4) {
        return make_shared<EnemyBase>(resource.getResource("enemy4"), 0.8, Models[0], path);
    }
    else {
        throw invalid_argument("Unknown enemy type");
    }
}
 // TINH CHỈNH THÔNG SỐ SPEED VÀ HP
void EnemyFactory::createModels(vector<vector<cpoint>> path) {
    Models.push_back(new EnemyModel(4, 5));  // small 
    Models.push_back(new EnemyModel(5, 10)); // big
    Models.push_back(new EnemyModel(4, 30)); // boss
    Models[0]->calculatePath(path);
    Models[1]->calculatePath(path);
    Models[2]->calculatePath(path);
}

void EnemyFactory::deleteModels() {
    for (auto model : Models)
        delete model;
}