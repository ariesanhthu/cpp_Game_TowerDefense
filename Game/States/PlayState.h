#pragma once
#include "States/GameState.h"
#include "GameManage/GamePlayManage.h"

namespace towerdefense
{
    class PlayState : public GameState
    {
    private:
        //cplayer player;
        //GamePlayManage gameManager;

    public:
        PlayState() {}
        ~PlayState() {}

        void loadContent(int width, int height) override;
        void handleInput(HWND hwnd) override;
        void update(float delta) override;
        void render(HDC hdc) override;
    };
}
