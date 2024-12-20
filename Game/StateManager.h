#pragma once
#include <memory>
#include "States/GameState.h"

namespace towerdefense
{
    class StateManager
    {
    private:
        std::shared_ptr<GameState> currentState;

    public:
        void changeState(std::shared_ptr<GameState> newState)
        {
            currentState = newState;
        }

        void loadContent(int width, int height)
        {
            if (currentState)
            {
                currentState->loadContent(width, height);
            }
        }

        void handleInput(HWND hwnd)
        {
            if (currentState)
            {
                currentState->handleInput(hwnd);
            }
        }

        void update(float delta)
        {
            if (currentState)
            {
                currentState->update(delta);
            }
        }

        void render(HDC hdc)
        {
            if (currentState)
            {
                currentState->render(hdc);
            }
        }
    };
}
