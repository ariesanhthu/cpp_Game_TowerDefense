#pragma once
#include <windows.h>
#include "User/SaveGameManager.h"
#include "User/UserManager.h"

#define WM_CUSTOM_LOAD_SCREEN (WM_USER + 1)

namespace towerdefense
{
    class Screen {
    public:
        //UserManager userManager; // list user
        //SaveGameManager saveGameManager; // list save game

        //virtual ~Screen();
        virtual void loadContent(int width, int height) = 0;
        virtual void handleInput(HWND hwnd) = 0;
        virtual void update(float delta) = 0;
        virtual void render(HDC hdc) = 0;
        //virtual void resizeContent(int windowWidth, int windowHeight);
    };

}
