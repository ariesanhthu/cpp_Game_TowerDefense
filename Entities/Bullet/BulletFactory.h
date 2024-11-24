#pragma once

#ifndef __BULLET_FACTORY_h__
#define __BULLET_FACTORY_h__

#include <memory>

#include "BulletBase.h"
//#include "BulletBase.h"
//#include "BulletBase.h"
//#include "BulletBase.h"


#define SMALL 1
#define BIG 2
#define BOSS 3

class BulletFactory
{
public:
    static unique_ptr<BulletBase> createEnemy(const int type) {
        if (type == SMALL) {
            return make_unique<BulletBase>();
        }
        else if (type == BIG) {
            return make_unique<BulletBase>();
        }
        else if (type == BOSS) {
            return make_unique<BulletBase>();
        }
        else {
            throw invalid_argument("Unknown bullet type");
        }
    }
};

#endif