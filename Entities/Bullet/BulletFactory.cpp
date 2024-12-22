#include "BulletFactory.h"

vector<shared_ptr< BulletModel>> BulletFactory::Models;

shared_ptr<BulletBase> BulletFactory::createBullet(const int& type, shared_ptr<EnemyBase> target = NULL, cpoint pos = cpoint(0,0,0)) {
    if (type == 0) {
        const vector<wstring> imagePaths = {
            L"Assets/game/bullet2/bullet2.png",
            L"Assets/game/bullet2/bullet2-2.png",
        };

        return make_shared<BulletBase>(imagePaths, 2, Models[0], pos, target);
    }
    else if (type == 1) {
        const vector<wstring> imagePaths = {
            L"Assets/game/bullet3/bullet3-1.png",
            L"Assets/game/bullet3/bullet3-2.png",
        };
        return make_shared<BulletBase>(imagePaths, 2, Models[1], pos, target);
    }
    else if (type == 2) {
        const vector<wstring> imagePaths = {
            L"Assets/game/bullet3/bullet3-1.png",
            L"Assets/game/bullet3/bullet3-2.png",
        };
        return make_shared<BulletBase>(imagePaths, 2, Models[2], pos, target);
    }
    else {
        throw invalid_argument("Unknown bullet type");
    }
}

void BulletFactory::createModels() {
    Models.push_back(make_shared<BulletModel>(1, 15));
    Models.push_back(make_shared<BulletModel>(1, 20));
    Models.push_back(make_shared<BulletModel>(1, 30));
}
void BulletFactory::deleteModels() {
    //for (auto model : Models)
        //delete model;
    Models.clear();
}