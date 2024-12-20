#pragma once
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <mmsystem.h> 

#include "cplayer.h"
#include "cenemy.h"
#include "ctower.h"

#include "User/cFile.h"
#include "User/userManager.h"
#include "User/converted.h"

#include <UIElement.h>
#include <menuitem.h>
#include "Graphic.h"

#include "Screen/Screen.h"
#include "Screen/MapScreen.h"

#include "Screen/MainScreen.h"
#include "Screen/PlayScreen.h"

#include "GameManage/GamePlayManage.h"

using namespace std;

namespace towerdefense
{
    enum ScreenState {
        MAIN_SCREEN = 0,
        MAP_1 = 1,
        MAP_2 = 2,
        MAP_3 = 3,
        MAP_4 = 4,
    };

    class ScreenManager {
    private:
        std::shared_ptr<Screen> currentScreen = nullptr;

    public:
        ~ScreenManager() {
            OutputDebugStringA("~ScreenManager\n");
        }

        //void changeScreen(int num) 
        void changeScreen(shared_ptr<Screen> newScreen) 
        {
            //switch (num)
            //{
            //    case MAP_1:
            //    {
            //        //currentScreen = move(make_shared<PlayScreen1>());

            //    break;
            //    }
            //    case MAP_2:
            //    {
            //        currentScreen = std::move(std::make_shared<PlayScreen2>());
            //        break;
            //    }
            //    case MAP_3:
            //    {
            //        //currentScreen = move(make_shared<PlayScreen3>());
            //        break;
            //    }
            //    case MAP_4:
            //    {
            //        //currentScreen = move(make_shared<PlayScreen4>());
            //    }
            //case MAIN_SCREEN:
            //default:
            //        currentScreen = std::move(std::make_shared<MainScreen>());
            //    break;
            //}
            currentScreen = newScreen;
        }

        void loadContent(int width, int height) {
            currentScreen->loadContent(width, height);
        }
        void handleInput(HWND hwnd) {
            currentScreen->handleInput(hwnd);
        }
        void update(float delta) {
            currentScreen->update(delta);
        }
        void render(HDC hdc) {
            currentScreen->render(hdc);
        }
    };
}