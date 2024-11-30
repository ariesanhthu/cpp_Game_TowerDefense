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
	int path;
	int index = 0;

public:
	//EnemyBase();
	EnemyBase(EnemyModel* nModel, int path);
	EnemyBase(EnemyModel* nModel, int path, int nHealth);
	EnemyBase(const EnemyBase& other);
	
	void setCurrentPosition(const cpoint& p);
	void setHealth(int hp);

	// get model attribute
	int getSpeed();
	//getTexture();

	//get private attribute
	cpoint getCurrentPosition();
	int getHealth();

	// file
	void writeFile(ostream& o);
	void readFile(istream& i);

	//update
	void update();
	void hit( int n);
};

#endif