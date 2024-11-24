#pragma once
#ifndef __ENEMY_MODEL_h__
#define __ENEMY_MODEL_h__

#include <vector>
#include "cpoint.h"

class EnemyModel
{
private:
	int speed;
	int defaultHealth;
	// texture

	std::vector< std::vector<cpoint>> pathList;

public:
	EnemyModel();
	EnemyModel(int nSpeed, int hp);
	//BulletModel(int nSpeed , texture);

	void setSpeed(int nSpeed);
	void setDefaultHealth(int nHP);
	
	int getSpeed();
	int getDefaultHealth();

	vector<cpoint> getPath(int n);

	void calculatePath(std::vector< std::vector<cpoint>> pointsList);
	// getTexture();
};

#endif