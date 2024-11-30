#pragma once
#ifndef __GAMEPLAY_MANAGE_h__
#define __GAMEPLAY_MANAGE_h__

#include <Bullet/BulletManager.h>
#include <Enemy/EnemyManager.h>
#include <Tower/TowerManager.h>

class GamePlayManage
{
	EnemyManager enemyManager;
	BulletManager bulletManager;
	TowerManager towerManager;

public:
	void setup();
	void startGame();
	void update();
};


#endif // !__GAMEPLAY_MANAGE__