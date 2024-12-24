#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Graphic.h"
#include <UIElement.h>
#include <chrono>

#include <mmsystem.h> 
#include <menuitem.h>

#include "Screen/Screen.h"
#include "GameManage/GamePlayManage.h"

#include "User/User.h";
#include "User/SaveGame.h"
#include "Utils.h"

#include "AudioManager.h"
#include "FontManager.h"
// --------------------------------------------------
//#include "User/SaveGameManager.h"
//#include "game.h"

#include "GameManager.h"

#include "User/Leaderboard.h"

using namespace std;

namespace towerdefense
{

    class MainScreen : public Screen {
    private:
        std::vector<std::shared_ptr<UIElement>> uiElements;
        HFONT customfont;
        HFONT Titlefont;

        // --------------- HOW TO PLAY -------------------
        //std::shared_ptr<Item> _boardHowToPlay;
        std::shared_ptr<Popup> _boardHowToPlay;
        POINT boardHowtoPlayPos = { 400, 100 };

        // -----------------------------------------------
        std::shared_ptr<Item> _background;
        std::shared_ptr<Item> _catfam;
        std::shared_ptr<Button> _play;
        std::shared_ptr<Button> _cont;
        std::shared_ptr<Button> _lead;
        std::shared_ptr<Button> _sett;
        std::shared_ptr<Button> _exit;
        std::shared_ptr<Button> _about;
        std::shared_ptr<Item> popup;

        std::shared_ptr<Button> _map1;
        std::shared_ptr<Button> _map2;
        std::shared_ptr<Button> _map3;
        std::shared_ptr<Button> _map4;

        std::shared_ptr<Button> _login;
        std::shared_ptr<InputElement> _inputName;
        std::shared_ptr<InputElement> _inputPassword;

        std::shared_ptr<Button> _register;
        std::shared_ptr<InputElement> _inputNameReg;
        std::shared_ptr<InputElement> _inputPasswordReg;

        std::shared_ptr<TextElement> _gotoPage;

        //std::vector<shared_ptr<ContinueElement>> _ListContinueItem;
        std::vector<std::shared_ptr<ContinueElement>> _FourContinueItem;

        
        std::shared_ptr<SaveGameSupport> supSaveGame;
        std::vector<SaveGame> listGame = {};
        std::vector<SaveGame> LoadList = {};
        std::vector<SaveGame> LeaderboardList = {};

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

        // ----------------- SETTING --------------------

        shared_ptr<TextElement> TitleSetting;
        //POINT titlePos = { 400, 100 };/ dùng chung

        // ----------------- audio --------------------
        // loa 
        shared_ptr<Item> _audioItem;
        shared_ptr<Item> _audioOffItem;
        POINT audioItemPos = { 300, 250 };

        // nút
        //shared_ptr<Button> _switchAudio;
        shared_ptr<Item> _switchOffAudio;
        shared_ptr<Item> _switchOnAudio;
        POINT switchAudioPos = { 650, 250 };
        //shared_ptr<Button> _switchOn = nullptr;

        // ----------------- volume --------------------
        // thanh volume
        shared_ptr<Item> _VolumeBar;
        shared_ptr<Item> _VolumeBarOn;
        POINT VolumeBarPos = { 300, 350 };
        POINT VolumeBarOnPos = { 300, 350 };

        shared_ptr<Item> _foregroundVol;

        // nút
        shared_ptr<Button> _arrowUpButton;
        shared_ptr<Button> _arrowDownButton;
        POINT arrowUpPos = { 750, 350 };
        POINT arrowDownPos = { 650, 350 };

        // ==================================================================



		// --------------------------------------------------
       /* std::shared_ptr<Button> _VolumeButton;
		std::shared_ptr<Button> _AudioButton;

        std::shared_ptr<Item> _VolBar;

        POINT VolumeButtonPos = { 500, 500 };
        POINT AudioButtonPos = { 0, 0 };*/

		// --------------------------------------------------
        POINT FirstContinueItem = { 300, 120 };

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

        // avoid double click
        mutable std::chrono::steady_clock::time_point lastMouseClickTime;  // mutable to modify in const method
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 300; // 200 ms debounce delay

        const wchar_t* maplink[5] = {
            L"",
            L"Assets/map_resize/map1_scaleDown.bmp",
            L"Assets/map_resize/map2_scaleDown.bmp",
            L"Assets/map_resize/map3_scaleDown.bmp",
            L"Assets/map_resize/map4_scaleDown.bmp",
        };

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