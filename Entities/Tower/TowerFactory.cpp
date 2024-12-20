#include "TowerFactory.h"

vector<TowerModel*> TowerFactory::Models;

shared_ptr<TowerBase> TowerFactory::createTower(const int type, cpoint pos) {
    if (type == 0) {
        return make_shared<TowerBase>(L"Assets/game/tured.bmp", 1, pos);
    }
    else if (type == 1) {
        return make_shared<TowerBase>(L"Assets/game/tured.bmp", 1, Models[0], pos);
    }
   /* else if (type == 2) {
        return make_unique<TowerBase>();
    }
    else if (type == 3) {
        return make_unique<TowerBase>();
    }*/
    
    else {
        throw invalid_argument("Unknown bullet type");
    }
}

void TowerFactory::createModels() {
    //
    Models.push_back(new TowerModel(250, 1, BulletFactory::Models[0]));
}
void TowerFactory::deleteModels() {
    for (auto model : Models)
        delete model;
    Models.clear();
}