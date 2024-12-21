#pragma once
#ifndef __BULLET_BASE_h__
#define __BULLET_BASE_h__

#include "cpoint.h"
#include "BulletModel.h"
#include "Enemy/EnemyBase.h"
#include "UIElement.h"

class BulletBase : public UIElement
{
protected:
    //model
	BulletModel* model;
	
	// private attribute
	cpoint currentPosition;
    shared_ptr<EnemyBase> target;

    bool visible = false;
public:
    BulletBase() = default;
    BulletBase(const BulletBase& other);
    BulletBase(BulletModel* nModel,cpoint pos, shared_ptr<EnemyBase> nTarget);

    BulletBase(const wchar_t* link, float factor, BulletModel* nModel, cpoint pos, shared_ptr<EnemyBase> nTarget);
    BulletBase(const wchar_t* link, float factor, shared_ptr<BulletModel> nModel, cpoint pos, shared_ptr<EnemyBase> nTarget) : BulletBase(link, factor, nModel.get(), pos, nTarget) {};

    //--------- animation constructor -------
    //EnemyBase(const std::vector<std::wstring>& imagePaths, float factor, EnemyModel* nModel, int npath);
    //---------------------------------------
    void setCurr(const cpoint& p);
    void setTarget(shared_ptr<EnemyBase> nTarget);
    void setVisible(bool vis);

    // get model attribute
    int getDame();
    int getSpeed();

    // get private attribute
    cpoint getCurr();
    shared_ptr<EnemyBase> getTarget();
    bool getVisible();
    // check collision
    shared_ptr<EnemyBase> checkCollision();

    // update position
    virtual void update();

    void render(HDC hdc) {
        if (image) {
            Graphic::DrawBitmap(image, { currentPosition.getX(), currentPosition.getY() }, hdc);
        }
    }

};


#endif