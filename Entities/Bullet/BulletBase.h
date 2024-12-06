#pragma once
#ifndef __BULLET_BASE_h__
#define __BULLET_BASE_h__

#include "cpoint.h"
#include "BulletModel.h"
#include "Enemy/EnemyBase.h"

class BulletBase
{
protected:
    //model
	BulletModel* model;
	
	// private attribute
	cpoint currentPosition;
    EnemyBase* target;

public:
    //BulletBase();
    BulletBase(const BulletBase& other);
    BulletBase(BulletModel* nModel,cpoint pos, EnemyBase* nTarget);

    void setCurr(const cpoint& p);
    void setTarget(EnemyBase* nTarget);

    // get model attribute
    int getDame();
    int getSpeed();

    // get private attribute
    cpoint getCurr();
    EnemyBase* getTarget();

    // check collision
    EnemyBase* checkCollision();

    // update position
    virtual void update();

};


#endif