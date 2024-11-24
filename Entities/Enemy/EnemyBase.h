#pragma once
#ifndef __ENEMY_BASE_h__
#define __ENEMY_BASE_h__


#include "cpoint.h"
#include "EnemyModel.h"


class EnemyBase
{
protected:
	//model
	EnemyModel* model;

	// private attribute
	cpoint currentPosition;
	int health;

public:
	//EnemyBase();
	EnemyBase(EnemyModel* nModel, cpoint pos);
	EnemyBase(EnemyModel* nModel, cpoint pos, int nHealth);
	EnemyBase(const EnemyBase& other);
	
	void setCurrentPosition(const cpoint& p);
	void setHealth(int hp);

	// get model attribute
	int getSpeed();
	//getTexture();

	//get private attribute
	cpoint getCurrentPosition();
	int getHealth();

};

#endif