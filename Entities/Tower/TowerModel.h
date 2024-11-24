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
	TowerModel(int range, int rate, BulletModel* nBulletModel);

	void setRange();
	void setRate();
	void setBulletModel(BulletModel* nBulletModel);

	int getRange();
	int getRate();
	BulletModel* getBulletModel();
};


#endif