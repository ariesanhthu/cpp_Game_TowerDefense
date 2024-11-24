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
    BulletBase();
    BulletBase(BulletModel* nModel,cpoint pos, EnemyBase* nTarget);

    void setCurr(const cpoint& p) { currentPosition = p; }
    void setTarget(EnemyBase* nTarget) { target = nTarget; }

    // get model attribute
    int getDame() { return model->getDame(); }
    int getSpeed() { return model->getDame(); }

    // get private attribute
    cpoint getCurr() { return currentPosition; }
    EnemyBase* getTarget() { return target; }

    // check collision
    EnemyBase* checkCollision();

    // update position
    virtual void update();

};


#endif