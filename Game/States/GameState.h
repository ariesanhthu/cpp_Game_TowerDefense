#pragma once
#include <windows.h>

namespace towerdefense
{
    class GameState
    {
    public:
        virtual ~GameState() {}

        virtual void loadContent(int width, int height) = 0;
        virtual void handleInput(HWND hwnd) = 0;
        virtual void update(float delta) = 0;
        virtual void render(HDC hdc) = 0;
    };
}
