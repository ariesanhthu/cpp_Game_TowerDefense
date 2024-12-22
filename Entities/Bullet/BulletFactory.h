#pragma once

#ifndef __BULLET_FACTORY_h__
#define __BULLET_FACTORY_h__

#include <memory>

#include "BulletBase.h"



class BulletFactory
{
public:
    static vector < shared_ptr< BulletModel> > Models;
    static shared_ptr<BulletBase> createBullet(const int& type, shared_ptr<EnemyBase> target, cpoint pos);
    static void createModels();
    static void deleteModels();
};

#endif