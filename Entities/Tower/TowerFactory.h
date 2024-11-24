#pragma once
#ifndef __TOWER_FACTORY_h__
#define __TOWER_FACTORY_h__

#include <memory>

#include "TowerBase.h"


class TowerFactory
{
public:
    static unique_ptr<TowerBase> createEnemy(const int type);
};
#endif

