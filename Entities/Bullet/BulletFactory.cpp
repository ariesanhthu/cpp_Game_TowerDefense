#include "BulletFactory.h"

vector<BulletModel*> BulletFactory::Models;

unique_ptr<BulletBase> BulletFactory::createEnemy(const string type, cpoint pos, EnemyBase* target) {
    if (type == "normal") {
        return make_unique<BulletBase>(Models[0],pos, target);
    }
   /* else if (type == BIG) {
        return make_unique<BulletBase>(Models[1],pos, target);
    }
    else if (type == BOSS) {
        return make_unique<BulletBase>(Models[2],pos, target);
    }*/
    else {
        throw invalid_argument("Unknown bullet type");
    }
}

void BulletFactory::createModels() {
    Models.push_back(new BulletModel(1, 10));
}
void BulletFactory::deleteModels() {
    for (auto model : Models)
        delete model;
}