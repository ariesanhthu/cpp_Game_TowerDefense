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

app_entry_point
{
	int x = 250, y = 250;

	// game init code
	towerdefense::Game::setGameUpdate([&](float delta)
	{
		wchar_t charBuffer[256];
		swprintf(charBuffer, 256, L"delta: %f\n", delta);
		OutputDebugString(charBuffer);

		Renderer::SetPixel(10, 10, { 0, 0, 0 });

		Renderer::FillRectangle({ x, y, 30, 10 }, {255, 255, 255 });

		// ĐỌC NÚT VÀ DI CHUYỂN
		
		if (Input::isKeyPressed(DC_UP))
		{
			y -= 1;
		}
		else if (Input::isKeyPressed(DC_DOWN))
			y += 1;
		if (Input::isKeyPressed(DC_LEFT))
			x -= 1;
		else if (Input::isKeyPressed(DC_RIGHT))
			x += 1;
	}
	);

	Renderer::SetClearColor({ 0, 0, 0 });
	
	towerdefense::Game::start();
	// game destroy code

	return 0;
}

