#pragma once
#ifndef __ENEMY_BASE_h__
#define __ENEMY_BASE_h__


#include "cpoint.h"
#include "EnemyModel.h"
#include "Graphic.h"


class EnemyBase
{
protected:
	//model
	EnemyModel* model;

	// private attribute
	int path;
	cpoint currentPosition;
	int health;
	int index = 0;

	bool isDead;

public:
	EnemyBase() = default;
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
	bool update();
	void hit( int n);

	void render(HBITMAP element, HDC hdc) {
		if (!isDead) {  // Chỉ vẽ nếu không chết
			Graphic::DrawBitmap(element, {currentPosition.getX(), currentPosition.getY()}, hdc);
		}
	}
};

#endif