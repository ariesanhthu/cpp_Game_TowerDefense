#pragma once
#ifndef __GAMEPLAY_MANAGE_h__
#define __GAMEPLAY_MANAGE_h__

#include <Bullet/BulletManager.h>
#include <Bullet/BulletFactory.h>
#include <Enemy/EnemyManager.h>
#include <Enemy/EnemyFactory.h>
#include <Tower/TowerManager.h>
#include <Tower/TowerFactory.h>
#include <UIElement.h>

class GamePlayManage 
{
private: 
	enum GameState {
		PLAY = 0,
		WIN = 1,
		LOSE = 2,
		PAUSE = 3,
	};


	int gameCode;
	int gameStatus = PLAY;
	int point = 0;

public:
	EnemyManager enemyManager;
	//BulletManager bulletManager;
	TowerManager towerManager;

	GamePlayManage() = default;

	GamePlayManage(int n) : gameCode(n) {}

	void setupEnemy(vector<vector<cpoint>> path);
	void setupTower();
	void startGame();
	void update(float delta);
	void destroy();

	void render(HDC hdc) {

		//OutputDebugStringA("BBBBBBBBBBBBBBBBBBBBBbbb\n");

		// luon ve
		enemyManager.renderEnemies(hdc);
		towerManager.renderTowers(hdc);
	}

	//setter
	void setGameCode(int );
	void setGameStatus(int );
	void setPoint(int );
	//getter
	int getGameCode();
	int getGameStatus();
	int getPoint();

	
};


#endif // !__GAMEPLAY_MANAGE__