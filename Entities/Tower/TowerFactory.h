#pragma once
#ifndef __TOWER_FACTORY_h__
#define __TOWER_FACTORY_h__

#include <memory>

#include "TowerBase.h"
#include "Bullet/BulletFactory.h"


class TowerFactory
{
public:
    static vector<TowerModel*> Models;
    static unique_ptr<TowerBase> createEnemy(const int type);
    static void createModels();
    static void deleteModels();
};
#endif

