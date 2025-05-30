#pragma once
#ifndef __TOWER_FACTORY_h__
#define __TOWER_FACTORY_h__

#include <memory>

#include "TowerBase.h"
#include "Bullet/BulletFactory.h"


class TowerFactory
{
public:
    static vector <shared_ptr<TowerModel>> Models;
    static std::shared_ptr<TowerBase> createTower(const int type, cpoint pos);
    static void createModels();
    static void deleteModels();
};
#endif

