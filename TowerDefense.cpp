/*
file xử dụng
game.h
game.cpp
TowerDefense.h
*/
#pragma once
//#include "PrecompiledHeader.h"
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")
#include "TowerDefense.h"
using namespace std;

app_entry_point
{
	towerdefense::Game::start();
	// game destroy code

	return 0;
}

