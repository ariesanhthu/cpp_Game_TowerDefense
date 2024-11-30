#pragma once
#ifndef __ENEMY_MANAGER_h__
#define __ENEMY_MANAGER_h__

#include "EnemyModel.h"
#include "EnemyBase.h"

class EnemyManager
{
public:
    void addEnemy(EnemyModel* model,cpoint pos);

    void updateAllEnemy();

    void renderEnemies();

private:
    std::vector<EnemyBase> enemies_;

};

#endif