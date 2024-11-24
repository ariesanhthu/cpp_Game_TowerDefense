#pragma once
#ifndef __ENEMY_FACTORY_h__
#define __ENEMY_FACTORY_h__

#include <memory>

#include "EnemyBase.h"


class EnemyFactory
{
public:
    static unique_ptr<EnemyBase> createEnemy(const int type) {
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