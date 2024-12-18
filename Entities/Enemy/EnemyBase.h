#pragma once
#ifndef __ENEMY_BASE_h__
#define __ENEMY_BASE_h__


#include "cpoint.h"
#include "EnemyModel.h"
#include "Graphic.h"
#include "UIElement.h"

class EnemyBase : public UIElement
{
protected:
	//model
	EnemyModel* model;

	// private attribute
	int path;
	cpoint currentPosition;
	int health;
	int index = 0;

	bool isDead = false;

public:
	EnemyBase() = default;
	EnemyBase(EnemyModel* nModel, int path);
	EnemyBase(EnemyModel* nModel, int path, int nHealth);
	EnemyBase(const EnemyBase& other);

	EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath, int nHealth);
	EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath);

	/*~EnemyBase() {
		if (model) delete model;
 	}*/
	
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
	bool update(float delta);
	void hit(int n);

	void render(HDC hdc) {
		if (health > 0) {  // Chỉ vẽ nếu không chết
			//OutputDebugStringA("DDDDDDDDDDDDDDDDDDDDDDDDDDd\n");
			//OutputDebugStringA((std::to_string(currentPosition.getX()) + " " + std::to_string(currentPosition.getY()) + "\n").c_str());
			Graphic::DrawBitmap(image, {currentPosition.getX(), currentPosition.getY()}, hdc);
		}
	}
};

#endif