#include "EnemyFactory.h"

unique_ptr<EnemyBase> EnemyFactory::createEnemy(const int type) {
    if (type == 1) {
        return make_unique<EnemyBase>();
    }
    else if (type == 2) {
        return make_unique<EnemyBase>();
    }
    else if (type == 3) {
        return make_unique<EnemyBase>();
    }
    else {
        throw invalid_argument("Unknown bullet type");
    }
}