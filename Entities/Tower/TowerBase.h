#pragma once
#ifndef __TOWER_BASE_h__
#define __TOWER_BASE_h__

#include <chrono>
#include <memory>

#include "cpoint.h"
#include "TowerModel.h"
#include "Bullet/BulletBase.h"
#include "Bullet/BulletFactory.h"
#include "Enemy/EnemyBase.h"
#include "UIElement.h"

#define MILI_SEC std::chrono::milliseconds
#define MILI_SEC_CAST std::chrono::duration_cast<std::chrono::milliseconds>
#define TIME_POINT std::chrono::system_clock::time_point

class TowerBase : public UIElement 
{
protected:
	TowerModel* model;

	cpoint currentPosition;
	TIME_POINT lastShoot;

	shared_ptr<BulletBase> bullet;

	int type;

public:
	TowerBase();
	TowerBase(const TowerBase& other);
	TowerBase(TowerModel* nModel, cpoint pos);
	
	TowerBase(const wchar_t* link, float factor, TowerModel* nModel, cpoint pos, int type);
	TowerBase(const wchar_t* link, float factor, shared_ptr<TowerModel> nModel, cpoint pos, int type) : TowerBase(link, factor, nModel.get(), pos, type) {};

	TowerBase(const wchar_t* link, float factor, cpoint pos);

	void setCurrentPosition(const cpoint& pos);
	cpoint getCurrentPosition();

	void setBullet(shared_ptr<BulletBase>);
	shared_ptr<BulletBase> getBullet();

	bool canShoot();
	bool canShoot(shared_ptr<EnemyBase> target);

	//virtual BulletBase shoot(shared_ptr<EnemyBase> target);
	virtual void shoot(shared_ptr<EnemyBase> target);

	int getType();
	void setType(const int x);

	void render(HDC hdc) {
		Graphic::DrawBitmap(image, { currentPosition.getX(), currentPosition.getY() }, hdc);
	}


	
};


#endif