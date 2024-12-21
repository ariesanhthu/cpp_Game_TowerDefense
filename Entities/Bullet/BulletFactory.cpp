#include "BulletFactory.h"

vector<shared_ptr< BulletModel>> BulletFactory::Models;

shared_ptr<BulletBase> BulletFactory::createBullet(const string type = "normal", shared_ptr<EnemyBase> target = NULL, cpoint pos = cpoint(0,0,0)) {
    if (type == "normal") {
        const vector<wstring> imagePaths = {
            L"Assets/game/bullet3/bullet3-1.png",
            L"Assets/game/bullet3/bullet3-2.png",
        };

        return make_shared<BulletBase>(imagePaths, 2, Models[0], pos, target);
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