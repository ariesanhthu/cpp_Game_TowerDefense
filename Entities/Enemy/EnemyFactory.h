#pragma once
#ifndef __ENEMY_FACTORY_h__
#define __ENEMY_FACTORY_h__

#include <memory>

#include "EnemyBase.h"


class EnemyFactory
{
public:
    static unique_ptr<EnemyBase> createEnemy(const int type) {
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
};

#endif