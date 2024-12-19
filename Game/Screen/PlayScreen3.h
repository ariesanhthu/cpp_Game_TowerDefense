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
////#include "Screen/PlayScreen2.h"
//#include "Screen/MapScreen.h"
//
//using namespace std;
//
//
//namespace towerdefense
//{
//class PlayScreen3 : public MapScreen {
//    private:
//        vector<POINT> epath1 = {
//            {-100, 170},
//            {460, 170},
//            {460, 450},
//            {1200, 450}
//        };
//
//        vector<POINT> epath2 = {
//            { 280, 800 },
//            { 280, 450 },
//            { 1200, 450 }
//        };
//
//    public:
//        PlayScreen3();
//        ~PlayScreen3();
//
//        void loadContent(int width, int height) override;
//        void handleInput(HWND hwnd) override;
//        void update(float delta) override;
//        void render(HDC hdc) override;
//    };
//
//}