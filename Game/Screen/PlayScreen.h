#pragma once
#include <vector>
#include <memory>
#include "Graphic.h"
#include <string>
#include "cplayer.h"
#include "cenemy.h"
#include "ctower.h"
#include <chrono>
#include <mmsystem.h> 
#include <UIElement.h>
#include <menuitem.h>
#include "User/cFile.h"
#include "User/userManager.h"
#include "User/converted.h"

#include "Screen/Screen.h"
#include "GameManage/GamePlayManage.h"

#include "Screen/MapScreen.h"

using namespace std;
namespace towerdefense
{
    class PlayScreen2 : public MapScreen {
    public:
        PlayScreen2();
        ~PlayScreen2();

        void loadSpecificContent(int width, int height) override;
        //void loadContent(int width, int height) override;
        /*void handleSpecificInput(HWND hwnd) override;
        void updateSpecific(float delta) override;
        void renderSpecific(HDC hdc) override;*/  
        //void handleInput(HWND hwnd) override = 0;
        //void update(float delta) override;
        //void render(HDC hdc) override;
    };
    // -------------------------------------------------------------------------
    class PlayScreen3 : public MapScreen {
    public:
        PlayScreen3();
        ~PlayScreen3();

        void loadSpecificContent(int width, int height) override;
    };
    // -------------------------------------------------------------------------
}

