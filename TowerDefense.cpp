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

app_entry_point
{
	// game init code
	towerdefense::Game::setGameUpdate([&](float delta)
	{
		wchar_t charBuffer[256];
		swprintf(charBuffer, 256, L"delta: %f\n", delta);
		OutputDebugString(charBuffer);
	}
	);
	towerdefense::Game::start();
	// game destroy code

	return 0;
}

