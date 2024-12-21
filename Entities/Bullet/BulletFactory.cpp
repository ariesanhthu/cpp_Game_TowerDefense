#include "BulletFactory.h"

vector<shared_ptr< BulletModel>> BulletFactory::Models;

shared_ptr<BulletBase> BulletFactory::createBullet(const string type = "normal", shared_ptr<EnemyBase> target = NULL, cpoint pos = cpoint(0,0,0)) {
    if (type == "normal") {
        return make_unique<BulletBase>(L"Assets/game/bullet2-2.png", 2, Models[0], pos, target);
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
    Models.push_back(make_shared<BulletModel>(1, 15));
}
void BulletFactory::deleteModels() {
    //for (auto model : Models)
        //delete model;
    Models.clear();
}