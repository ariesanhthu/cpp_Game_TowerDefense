#pragma once
#ifndef __TOWER_FACTORY_h__
#define __TOWER_FACTORY_h__

#include <memory>

#include "TowerBase.h"


class TowerFactory
{
public:
    static unique_ptr<TowerBase> createEnemy(const int type) {
        if (type == 1) {
            return make_unique<TowerBase>();
        }
        else if (type == 2) {
        return make_unique<TowerBase>();
        }
        else if (type == 3) {
        return make_unique<TowerBase>();
        }
        else {
            throw invalid_argument("Unknown bullet type");
        }
    }
};
#endif

