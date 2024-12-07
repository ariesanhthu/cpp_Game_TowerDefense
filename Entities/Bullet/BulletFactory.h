#pragma once

#ifndef __BULLET_FACTORY_h__
#define __BULLET_FACTORY_h__

#include <memory>

#include "BulletBase.h"
//#include "BulletBase.h"
//#include "BulletBase.h"
//#include "BulletBase.h"


class BulletFactory
{
public:
    static vector<BulletModel*> Models;
    static unique_ptr<BulletBase> createEnemy(const string type, cpoint pos, EnemyBase* target);
    static void createModels();
    static void deleteModels();
};

#endif