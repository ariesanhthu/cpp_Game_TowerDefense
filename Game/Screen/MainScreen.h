#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Graphic.h"
#include <UIElement.h>

#include "cplayer.h"
#include "cenemy.h"
#include "ctower.h"
#include <chrono>

#include <mmsystem.h> 
#include <menuitem.h>

#include "User/cFile.h"
#include "User/userManager.h"
#include "User/converted.h"

#include "Screen/Screen.h"
#include "GameManage/GamePlayManage.h"

using namespace std;

namespace towerdefense
{

    class MainScreen : public Screen {
    private:
        std::vector<std::shared_ptr<UIElement>> uiElements;
        HFONT customfont;

        std::shared_ptr<Item> _background;
        std::shared_ptr<Item> _catfam;
        std::shared_ptr<Button> _play;
        std::shared_ptr<Button> _cont;
        std::shared_ptr<Button> _lead;
        std::shared_ptr<Button> _sett;
        std::shared_ptr<Button> _exit;
        std::shared_ptr<Button> _about;
        std::shared_ptr<Popup> popup;

        std::shared_ptr<Option> _map1;
        std::shared_ptr<Option> _map2;
        std::shared_ptr<Option> _map3;
        std::shared_ptr<Option> _map4;

        std::shared_ptr<Button> _login;
        std::shared_ptr<InputElement> _inputName;
        std::shared_ptr<InputElement> _inputPassword;

        std::shared_ptr<Button> _register;
        std::shared_ptr<InputElement> _inputNameReg;
        std::shared_ptr<InputElement> _inputPasswordReg;

        std::shared_ptr<TextElement> _gotoPage;


        POINT firstplayerCoverPos = { 420, 200 };
        POINT titleContinuePos = { 390, 130 };
        POINT backgroundPos = { 0, 0 };

        POINT titlePos = { 400, 100 };
        POINT soundPos = { 270, 200 };

        POINT VolFirstPos = { 270, 300 };
        POINT VolDesPos = { 370, 300 };
        POINT VolInsPos = { 400, 300 };

        int volumeSize = 10;
        int currentVolume = 50;
        int percent = currentVolume / volumeSize;

        vector<POINT> buttonPositions;                  // Vị trí các nút bấm
        vector<POINT> optionPositionsStart;            // Vi tri cac lua chon map
        vector<POINT> optionPositionsEnd;
        // Vẽ input box
        POINT loginPosition;
        POINT inputNamePosition = { 480, 250 };
        POINT inputPasswordPosition = { 480, 350 };
        POINT nameTextPos = { 270, 260 };
        POINT passwordTextPos = { 270, 360 };
        POINT loginTextPos = { 480, 150 };
        POINT registerPosition = { 480, 200 };
        POINT linkPos = { 270, 460 };

        // Thiết lập 3 vị trí để popup board
        POINT initpoint, endpoint;

        // menu = 0 -> default
        // menu = 1 -> choose map
        // menu = 2 -> continue
        // menu = 3 -> leaderboard
        // menu = 4 -> setting 
        // menu = 5 -> exit handling
        // menu = 6 -> about us
        // menu = 101 -> login
        static int menu;
        bool loginMenu = true;

        //size doi tuong
        POINT buttonSize = { 26, 29 };
        POINT sizeBoard = { 693, 447 };
        POINT optionSize = { 75, 42 };
        POINT loginSize = { 99, 43 };
        POINT inputSize = { 60, 11 };
        POINT sizeSound = { 25, 29 };
        POINT sizeVolBtn = { 14, 21 };
        POINT sizeEdit = { 7, 12 };

        // avoid double click
        mutable std::chrono::steady_clock::time_point lastMouseClickTime;  // mutable to modify in const method
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 300; // 200 ms debounce delay

        // support
        void SetVolume(int volumePercentage) {
            if (volumePercentage < 0) volumePercentage = 0;
            if (volumePercentage > 99) volumePercentage = 0;

            DWORD volume = (DWORD)(0xFFFF * (volumePercentage / 100.0f));
            DWORD volumeSetting = (volume & 0xFFFF) | (volume << 16);

            waveOutSetVolume(0, volumeSetting);
            currentVolume = volumePercentage;
        }

    public:
        MainScreen();
        ~MainScreen();

        void loadContent(int width, int height) override;
        void handleInput(HWND hwnd) override;
        void update(float delta) override;
        void render(HDC hdc) override;
        //void resizeContent(int windowWidth, int windowHeight) override;
    };

}