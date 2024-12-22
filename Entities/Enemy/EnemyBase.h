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
	int type;

	bool onRoad = false;
	

public:
	EnemyBase() = default;
	EnemyBase(EnemyModel* nModel, int path);
	EnemyBase(EnemyModel* nModel, int path, int nHealth);
	EnemyBase(const EnemyBase& other);

	EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath, int nHealth);
	EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath);

	void setIndex(int x);

	// CONSTRUCTOR WITH FRAME ANIMATION
	EnemyBase(const std::vector<std::wstring>& imagePaths, float factor, EnemyModel* nModel, int npath);
	EnemyBase(const std::vector<std::wstring>& imagePaths, float factor, shared_ptr<EnemyModel> nModel, int npath);
	/*~EnemyBase() {
		if (model) delete model;
 	}*/
	
	void setCurrentPosition(const cpoint& p);
	void setHealth(int hp);

	// get model attribute
	int getSpeed();
	//getTexture();

	int getPath();
	void setPath(int x);
	bool isOnRoad();

	void setType(const int x);
	int getType();


	//get private attribute
	cpoint getCurrentPosition();
	int getHealth();

	// file
	void writeFile(ostream& o);
	void readFile(istream& i);

	//update
	bool update(float delta);
	void hit(int n);

	void render(HDC hdc);
};

#endif