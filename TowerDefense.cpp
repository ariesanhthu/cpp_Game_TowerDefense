/*
file xử dụng
game.h
game.cpp
TowerDefense.h
*/
#pragma once
//#include "PrecompiledHeader.h"
#include "TowerDefense.h"
using namespace std;
using namespace towerdefense;

app_entry_point {
	towerdefense::Game::start();
	return 0;
}

