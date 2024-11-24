#pragma once
#ifndef __TOWER_FACTORY_h__
#define __TOWER_FACTORY_h__

#include <memory>

#include "TowerBase.h"


class TowerFactory
{
public:
    static unique_ptr<TowerBase> createEnemy(const int type) {
        //if (type == SMALL) {
            //return make_unique<Zombie>();
        //}
        //else if (type == BIG) {
        //return make_unique<Vampire>();
        //}
        //else if (type == BOSS) {
        //return make_unique<Ghost>();
        //}
        //else {
            //throw invalid_argument("Unknown bullet type");
        //}
    }
};
#endif

