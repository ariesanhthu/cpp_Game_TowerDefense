#pragma once
#ifndef __ENEMY_MANAGER_h__
#define __ENEMY_MANAGER_h__

#include "BulletModel.h"
#include "BulletBase.h"

class BulletManager
{
public:
    void addBullet(BulletModel* model, cpoint pos);
    void addBullet(BulletBase bullet);
    void renderBullets();

private:
    std::vector<BulletBase> bulllets_;

};

#endif