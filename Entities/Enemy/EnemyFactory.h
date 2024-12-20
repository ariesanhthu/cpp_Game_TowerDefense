#pragma once
#ifndef __ENEMY_FACTORY_h__
#define __ENEMY_FACTORY_h__

#include <memory>

#include "EnemyBase.h"

#include "ResourceManager.h"


class EnemyFactory
{
    static vector <shared_ptr<EnemyModel>> Models;
public:
    static  shared_ptr<EnemyBase> createEnemy(const int type, int path);
    static void createModels(vector<vector<cpoint>> path);
    static void deleteModels();
};

#endif