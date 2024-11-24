#pragma once
#ifndef __TOWER_BASE_h__
#define __TOWER_BASE_h__

#include <chrono>

#include "cpoint.h"
#include "TowerModel.h"

#define MILI_SEC std::chrono::milliseconds
#define MILI_SEC_CAST std::chrono::duration_cast<std::chrono::milliseconds>
#define TIME_POINT std::chrono::system_clock::time_point

class TowerBase
{
protected:
	TowerModel* model;

	cpoint currentPosition;
	MILI_SEC lastShoot;

public:
	TowerBase();
	TowerBase(TowerModel* nModel, cpoint pos);

	void setCurrentPosition(const cpoint& pos);
	cpoint getCurrentPosition();
};


#endif