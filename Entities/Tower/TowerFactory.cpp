#include "TowerFactory.h"

vector<TowerModel*> TowerFactory::Models;

unique_ptr<TowerBase> TowerFactory::createEnemy(const int type) {
    if (type == 1) {
        return make_unique<TowerBase>();
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
    Models.push_back(new TowerModel(30, 1,BulletFactory::Models[0]));
}
void TowerFactory::deleteModels() {
    for (auto model : Models)
        delete model;
}