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
	EnemyBase();
	EnemyBase(EnemyModel* nModel, cpoint pos, int nHealth);
	//EnemyBase();
	
	void setCurrentPosition(const cpoint& p) { currentPosition = p; }
	void setHealth(const int hp) { health = hp; }

	// get model attribute
	int getSpeed();
	//getTexture();

	//get private attribute
	cpoint getCurrentPosition();
	int getHealth();

};

#endif