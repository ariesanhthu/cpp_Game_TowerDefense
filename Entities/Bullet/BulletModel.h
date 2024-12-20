#pragma once
#ifndef __BULLET_MODEL_h__
#define __BULLET_MODEL_h__


class BulletModel
{
private:
	int dame;
	int speed;
	// texture

public:
	BulletModel();
	BulletModel(int nDame, int nSpeed);
	//BulletModel(int nDame, int nSpeed , texture);
	
	int getDame();
	int getSpeed();

	// getTexture();
};

#endif