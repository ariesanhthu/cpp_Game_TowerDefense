#pragma once
#ifndef __TOWER_MODEL_h__
#define __TOWER_MODEL_h__

#include "Bullet/BulletModel.h"

class TowerModel
{
protected:
	int range;
	int rate;
	
	BulletModel* bulletModel;

public:
	TowerModel();
	TowerModel(const TowerModel& other);
	TowerModel(int range, int rate, BulletModel* nBulletModel);

	void setRange(int nRange);
	void setRate(int nRate);
	void setBulletModel(BulletModel* nBulletModel);

	int getRange();
	int getRate();
	BulletModel* getBulletModel();
};


#endif