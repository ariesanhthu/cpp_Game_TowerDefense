#pragma once
#ifndef __ENEMY_MODEL_h__
#define __ENEMY_MODEL_h__

class EnemyModel
{
private:
	int speed;
	// texture

public:
	EnemyModel();
	EnemyModel(int nSpeed);
	//BulletModel(int nSpeed , texture);

	int getSpeed();

	// getTexture();
};

#endif