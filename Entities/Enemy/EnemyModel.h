#pragma once
#ifndef __ENEMY_MODEL_h__
#define __ENEMY_MODEL_h__

class EnemyModel
{
private:
	int speed;
	int defaultHealth;
	// texture

public:
	EnemyModel();
	EnemyModel(int nSpeed, int hp);
	//BulletModel(int nSpeed , texture);

	void setSpeed(int nSpeed);
	void setDefaultHealth(int nHP);
	
	int getSpeed();
	int getDefaultHealth();

	// getTexture();
};

#endif