#include "TowerFactory.h"

vector<shared_ptr<TowerModel>> TowerFactory::Models;

shared_ptr<TowerBase> TowerFactory::createTower(const int type, cpoint pos) {
    if (type == 0) {
        return make_shared<TowerBase>(L"Assets/game/tower.bmp", 2, Models[0], pos, type);
        //return make_shared<TowerBase>(L"Assets/game/tured.bmp", 1, pos);
    }
    else if (type == 1) {
        return make_unique<TowerBase>(L"Assets/game/tower3.png", 1.4, Models[1], pos, type);
    }
    else if (type == 2) {
        return make_shared<TowerBase>(L"Assets/game/tured.bmp", 1, Models[2], pos, type);
    }
    
    else {
        throw invalid_argument("Unknown bullet type");
    }
}

void TowerFactory::createModels() {
    //
    Models.push_back(make_shared<TowerModel>(250, 1, BulletFactory::Models[0].get()));
    Models.push_back(make_shared<TowerModel>(200, 2, BulletFactory::Models[1].get()));
    Models.push_back(make_shared<TowerModel>(150, 3, BulletFactory::Models[2].get()));
}
void TowerFactory::deleteModels() {
    //for (auto model : Models)
        //delete model;
    Models.clear();
}