#pragma once

#ifndef __BULLET_FACTORY_h__
#define __BULLET_FACTORY_h__

#include <memory>

#include "BulletBase.h"



class BulletFactory
{
public:
    static vector<BulletModel*> Models;
    static shared_ptr<BulletBase> createBullet(const string type, shared_ptr<EnemyBase> target, cpoint pos);
    static void createModels();
    static void deleteModels();
};

#endif