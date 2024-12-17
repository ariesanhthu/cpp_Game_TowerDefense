#pragma once
#ifndef __ENEMY_MODEL_h__
#define __ENEMY_MODEL_h__

#include <vector>
#include "cpoint.h"

class EnemyModel
{
private:
	int speed;
	int defaultHealth = 100;

	bool isMoving;
	// texture

	std::vector< std::vector<cpoint>> pathList;

public:
	EnemyModel();
	EnemyModel(int nSpeed, int hp);
	//BulletModel(int nSpeed , texture);

	void setSpeed(int nSpeed);
	void setDefaultHealth(int nHP);
	void setIsMove(bool b) { isMoving = b; }


	int getSpeed();
	int getDefaultHealth();
	bool getIsMove() { return isMoving; }
	vector<cpoint> getPath(int n);

	void calculatePath(std::vector< std::vector<cpoint>> pointsList);
	// getTexture();
};

#endif