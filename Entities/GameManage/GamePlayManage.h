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
	EnemyManager enemyManager;
	BulletManager bulletManager;
	TowerManager towerManager;

	int gameCode;

public:
	GamePlayManage() = default;
	GamePlayManage(int n) : gameCode(n) {};
	void setup();
	void startGame();
	void update();
	void destroy();

};


#endif // !__GAMEPLAY_MANAGE__