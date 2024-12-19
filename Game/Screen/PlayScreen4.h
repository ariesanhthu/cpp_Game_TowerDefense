//#pragma once
//#include <vector>
//#include <memory>
//#include "Graphic.h"
//#include <string>
//#include "cplayer.h"
//#include "cenemy.h"
//#include "ctower.h"
//#include <chrono>
//#include <mmsystem.h> 
//#include <UIElement.h>
//#include <menuitem.h>
//#include "User/cFile.h"
//#include "User/userManager.h"
//#include "User/converted.h"
//#include "Screen/Screen.h"
//#include "GameManage/GamePlayManage.h"
//
//#include "Screen/MapScreen.h"
//
//using namespace std;
//
//
//namespace towerdefense
//{
//	class PlayScreen4 : public MapScreen {
//	private:
//	    vector<POINT> epath1 = {
//	        { -100, 160 },
//	        { 660, 160 },
//	        { 660, 800 },
//	    };
//
//	    vector<POINT> epath2 = {
//	        { 290, -100 },
//	        { 290, 400 },
//	        { 1200, 400 }
//	    };
//
//	public:
//	    PlayScreen4();
//	    ~PlayScreen4();
//
//	    void loadContent(int width, int height) override;
//	    void handleInput(HWND hwnd) override;
//	    void update(float delta) override;
//	    void render(HDC hdc) override;
//	};
//
//}