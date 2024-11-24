#pragma once
#ifndef __ENEMY_FACTORY_h__
#define __ENEMY_FACTORY_h__

#include <memory>

#include "EnemyBase.h"


class EnemyFactory
{
public:
    static unique_ptr<EnemyBase> createEnemy(const int type);
};

#endif