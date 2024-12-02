#pragma once
#include <vector>
#include <memory>
#include "Graphic.h"
#include <vector>
#include <string>
#include "cplayer.h"
#include "cenemy.h"
#include "ctower.h"
#include <chrono>

using namespace std;
namespace towerdefense
{
    class Screen {
    public:

        // Dòng này làm MainScreen không destruct được
        //virtual ~Screen() = 0;
        virtual void loadContent(Graphic& graphic, int width, int height) = 0;
        virtual void handleInput() = 0;
        virtual void update(float delta) = 0;
        virtual void render(HDC hdc) = 0;
        //virtual void resizeContent(int windowWidth, int windowHeight);
    };

    class ScreenManager {
    private:
        std::shared_ptr<Screen> currentScreen = nullptr;

    public:
        ~ScreenManager() {}

        void changeScreen(std::shared_ptr<Screen> newScreen) {
            currentScreen = newScreen;
        }

        void loadContent(Graphic& graphic, int width, int height) {
            currentScreen->loadContent(graphic, width, height);
        }
        void handleInput() {
            currentScreen->handleInput();
        }
        void update(float delta) {
            currentScreen->update(delta);
        }
        void render(HDC hdc) {
            currentScreen->render(hdc);
        }
    };

    class MainScreen : public Screen {
    private:
        // dung chung trong cac menu
        HBITMAP background = nullptr;             // Hình nền
        // dung trong default menu
        HBITMAP button = nullptr;                 // Danh sách các nút bấm
        HBITMAP button_down = nullptr;
        HBITMAP button_hover = nullptr;
        // popup
        HBITMAP board = nullptr;
        // choose map
        HBITMAP map1opt = nullptr; 
        HBITMAP map2opt = nullptr; 
        HBITMAP map3opt = nullptr; 
        HBITMAP map4opt = nullptr; 
        HBITMAP opt_hover = nullptr;
        // login
        HBITMAP login = nullptr;
        HBITMAP login_down = nullptr;
        HBITMAP login_hover = nullptr;
        HBITMAP input = nullptr;
        HBITMAP loginText = nullptr;
        HBITMAP nameText = nullptr;
        HBITMAP passwordText = nullptr;
        // continue
        HBITMAP continueTitle = nullptr;
        HBITMAP arrow = nullptr;

        // continue with dummydata
        vector<cplayer> dummyData = { {"duck", 10}, {"thu", 12}, {"Hung", 44} };
        vector<HBITMAP> dummyDataName = { nullptr };
        vector<HBITMAP> dummyDataPoint = { nullptr };
        POINT firstplayerCoverPos = { 420, 200 };
        POINT titleContinuePos = { 390, 130 };

        vector<POINT> buttonPositions;           // Vị trí các nút bấm
        vector<POINT> optionPositions;            // Vi tri cac lua chon map
        
        // Vẽ input box
        POINT loginPosition;
        POINT inputNamePosition = { 480, 250 };
        POINT inputPasswordPosition = { 480, 350 };
        POINT loginTextPos = { 480, 150 };
        POINT nameTextPos = { 270, 260 };
        POINT passwordTextPos = { 270, 360 };

        // Thiết lập 3 vị trí để popup board
        POINT initpoint, currentpoint, endpoint; 
        bool isChoosemapPopup = false;
        bool isPopupEffect = false;

        // string nhap tu input
        HBITMAP inputtextbitmap = nullptr;
        bool start_to_input = false;
        string inputtext = "YOURNAME";

        // index = 0 -> choose map menu 
        // index = 1 -> continue menu
        // index = 2 -> leaderboard menu 
        // index = 3 -> setting menu
        // index = 4 -> exit handling
        // index = 5 -> about us menu 
        // index = 101 -> login 
        static int index;
        static int hover;
        // menu = 0 -> default
        // menu = 1 -> choose map
        // menu = 2 -> continue
        // menu = 3 -> leaderboard
        // menu = 4 -> setting 
        // menu = 5 -> exit handling
        // menu = 6 -> about us
        // menu = 101 -> login
        static int menu; 

        //size doi tuong
        POINT buttonSize = { 26, 29 };
        POINT sizeBoard = { 693, 447 };
        POINT optionSize = { 300, 168 };
        POINT loginSize = { 99, 43 };
        POINT inputSize = { 60, 11 };


        // avoid double click
        std::chrono::steady_clock::time_point lastMouseClickTime;
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 200; // 200 ms debounce delay

    public:
        MainScreen();
        ~MainScreen();

        void loadContent(Graphic& graphic, int width, int height) override;
        void handleInput() override; 
        void update(float delta) override;
        void render(HDC hdc) override;
        //void resizeContent(int windowWidth, int windowHeight) override;
    };

    class PlayScreen : public Screen {
    private: 
        vector<POINT> epath = {
            {-10, 150},
            {390, 150},
            {390, 490},
            {1200, 490},
        };

        // hbitmap
        HBITMAP background = nullptr;
        HBITMAP tower = nullptr;              // tower
        HBITMAP towerInitPlace = nullptr;     // Ô chứa tháp
        HBITMAP instructionBoard = nullptr;   // Bảng hướng dẫn 
        HBITMAP enemy = nullptr;              // enemy
        HBITMAP hamburger = nullptr;          // hamburger button
        HBITMAP play_or_pause = nullptr;      // nut play hoac pause

        // instruction pos
        POINT instructionPos = { 730, 50 };
        POINT hamburgerPos = { 1200, 5 };
        bool displayBoard = true;

        // position init place of box
        POINT towerInitPos = { 10, 550 };
        
        // buton play or pause 
        POINT posbuttonplay = { 350, 570 };

        // delay hand variable
        std::chrono::steady_clock::time_point lastMouseClickTime;
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 300; // 200 ms debounce delay

        // enemy 
        std::vector<cenemy> enemylist;
        POINT Einit;              // enemy position

        // tower
        std::vector<ctower> towerlist;
        std::vector<POINT> Tcurrent;
        POINT Turretinit;                       // tower position 

        // tower de chon di chuyen
        ctower Tpicking; 
        POINT TcurrentPick;
        bool isPicking = false;

        // size
        POINT buttonSize = { 26, 29 };
        POINT boardSize = { 260, 180 };
        POINT towerSize = { 20,30 };

        // support 
        /*
            FIX BUGGGGGGGGGGGGGGGGG
            check vị trí đặt tháp
        */
        bool checkValidPos(POINT pos) {
            return true;
        }

    public:
        PlayScreen();
        ~PlayScreen();

        void loadContent(Graphic& graphic, int width, int height) override;
        void handleInput() override;
        void update(float delta) override;
        void render(HDC hdc) override;
    };
}