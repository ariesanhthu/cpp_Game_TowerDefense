#pragma once
#ifndef __TOWER_BASE_h__
#define __TOWER_BASE_h__

#include <chrono>

#include "cpoint.h"
#include "TowerModel.h"
#include "Bullet/BulletBase.h"
#include "Enemy/EnemyBase.h"

#define MILI_SEC std::chrono::milliseconds
#define MILI_SEC_CAST std::chrono::duration_cast<std::chrono::milliseconds>
#define TIME_POINT std::chrono::system_clock::time_point

class TowerBase
{
protected:
	TowerModel* model;

	cpoint currentPosition;
	TIME_POINT lastShoot;

public:
	TowerBase() = default;
	TowerBase(const TowerBase& other);
	TowerBase(TowerModel* nModel, cpoint pos);

	void setCurrentPosition(const cpoint& pos);
	cpoint getCurrentPosition();

	bool canShoot();
	bool canShoot(EnemyBase* target);

	virtual BulletBase shoot(EnemyBase* target);

};


#endif