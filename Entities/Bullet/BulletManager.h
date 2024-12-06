#pragma once
#ifndef __BULLET_MANAGER_h__
#define __BULLET_MANAGER_h__

#include "BulletModel.h"
#include "BulletBase.h"

class BulletManager
{
public:
    void addBullet(BulletModel* model, cpoint pos, EnemyBase* target);
    void addBullet(BulletBase bullet);
    void renderBullets();

    void update();
private:
    std::vector<BulletBase> bulllets_;

};

#endif