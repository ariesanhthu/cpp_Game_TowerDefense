#pragma once
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <mmsystem.h> 

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

        void changeScreen(shared_ptr<Screen> newScreen) 
        {
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