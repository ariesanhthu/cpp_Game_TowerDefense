#include "TowerFactory.h"

vector<shared_ptr<TowerModel>> TowerFactory::Models;

shared_ptr<TowerBase> TowerFactory::createTower(const int type, cpoint pos) {
     
    shared_ptr<TowerBase> tmp = nullptr;
   
    if (type == 0) {
        tmp = make_shared<TowerBase>(L"Assets/game/tower.bmp", 2, Models[0], pos, type);
        //return make_shared<TowerBase>(L"Assets/game/tured.bmp", 1, pos);
    }
    else if (type == 1) {
        tmp = make_unique<TowerBase>(L"Assets/game/tower3.png", 1.4, Models[1], pos, type);
    }
    else if (type == 2) {
        tmp = make_shared<TowerBase>(L"Assets/game/tured.bmp", 1, Models[2], pos, type);
    }    
    else {
        throw invalid_argument("Unknown bullet type");
    }

    tmp->setType(type);

    return tmp;
}

void TowerFactory::createModels() {
    // range, rate, loại đạn
    Models.push_back(make_shared<TowerModel>(100, 5, BulletFactory::Models[0].get()));
    Models.push_back(make_shared<TowerModel>(150, 5, BulletFactory::Models[1].get()));
    Models.push_back(make_shared<TowerModel>(200, 5, BulletFactory::Models[2].get()));
}
void TowerFactory::deleteModels() {
    //for (auto model : Models)
        //delete model;
    Models.clear();
}