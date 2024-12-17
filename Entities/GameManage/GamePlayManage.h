#pragma once
#ifndef __GAMEPLAY_MANAGE_h__
#define __GAMEPLAY_MANAGE_h__

#include <Bullet/BulletManager.h>
#include <Bullet/BulletFactory.h>
#include <Enemy/EnemyManager.h>
#include <Enemy/EnemyFactory.h>
#include <Tower/TowerManager.h>
#include <Tower/TowerFactory.h>

class GamePlayManage
{
public:
	EnemyManager enemyManager;
	//BulletManager bulletManager;
	TowerManager towerManager;

	int gameCode;
	int gameStatus; // 1 is win, 2 is lose, 0 is game conmtinue

	GamePlayManage() = default;
	GamePlayManage(int n) : gameCode(n) {};
	void setup(vector<vector<cpoint>> path);
	void startGame();
	void update();
	void destroy();

};


#endif // !__GAMEPLAY_MANAGE__