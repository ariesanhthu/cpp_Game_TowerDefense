
#include <stdlib.h>
#include <crtdbg.h>
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
#include <time.h>
using namespace std;

app_entry_point
{
	srand(time(0));
	towerdefense::Game::start();
	_CrtDumpMemoryLeaks();
	long lBreakAlloc = 0;
	if (lBreakAlloc > 0)
	{
		_CrtSetBreakAlloc(lBreakAlloc);
	}
	// game destroy code

	return 0;
}

