﻿#pragma once
#include <vector>
#include <memory>
#include "Graphic.h"
#include <vector>
#include <string>
#include "cplayer.h"
#include "cenemy.h"
#include "ctower.h"
#include <chrono>
#include <mmsystem.h> 

using namespace std;
namespace towerdefense
{
    class Screen {
    public:

        // Dòng này làm MainScreen không destruct được
        //virtual ~Screen() = 0;
        virtual void loadContent(int width, int height) = 0;
        virtual void handleInput(HWND hwnd) = 0;
        virtual void update(float delta) = 0;
        virtual void render(HDC hdc) = 0;
        //virtual void resizeContent(int windowWidth, int windowHeight);
    };

    class ScreenManager {
    private:
        std::shared_ptr<Screen> currentScreen = nullptr;

    public:
        ~ScreenManager() {
            OutputDebugStringA("~ScreenManager\n");
        }

        void changeScreen(std::shared_ptr<Screen> newScreen) {
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

    class MainScreen : public Screen {
    private:
        // dung chung trong cac menu
        HBITMAP background       = nullptr;               // Hình nền
        HBITMAP catfam           = nullptr;
        
        // dung trong default menu
        //HBITMAP button = nullptr;                 // Danh sách các nút bấm
        //HBITMAP button_down = nullptr;


        // button  
        HBITMAP play             = nullptr;             // play
        HBITMAP cont             = nullptr;             // continue 
        HBITMAP lead             = nullptr;             // leaderboard
        HBITMAP setting          = nullptr;             // setting 
        HBITMAP exit             = nullptr;             // exit
        HBITMAP about            = nullptr;             // about us
        HBITMAP button_hover     = nullptr;

        // popup
        HBITMAP board = nullptr;

        // choose map
        HBITMAP map1opt          = nullptr; 
        HBITMAP map2opt          = nullptr; 
        HBITMAP map3opt          = nullptr; 
        HBITMAP map4opt          = nullptr; 
        HBITMAP opt_hover        = nullptr;


        // login
        HBITMAP login            = nullptr;
        HBITMAP login_down       = nullptr;
        HBITMAP login_hover      = nullptr;
        HBITMAP input            = nullptr;
        HBITMAP loginText        = nullptr;
        HBITMAP nameText         = nullptr;
        HBITMAP passwordText     = nullptr;

        // continue
        HBITMAP continueTitle    = nullptr;
        HBITMAP arrow            = nullptr;

        // continue with dummydata
        vector<cplayer> dummyData = { {"duck", 10}, {"thu", 12}, {"Hung", 44} };
        vector<HBITMAP> dummyDataName = { nullptr };
        vector<HBITMAP> dummyDataPoint = { nullptr };
        POINT firstplayerCoverPos = { 420, 200 };
        POINT titleContinuePos = { 390, 130 };

        // leaderboard 

        // setting 
        bool soundCheck          = false;
        HBITMAP TitleSetting     = nullptr;

        HBITMAP switchOff        = nullptr;
        HBITMAP switchOn         = nullptr;

        HBITMAP insVolBtn = nullptr;
        HBITMAP desVolBtn = nullptr;

        HBITMAP backgroundVol = nullptr; 
        HBITMAP foregroundVol = nullptr;

        POINT titlePos = { 400, 100 };
        POINT soundPos = { 270, 200 };

        POINT VolFirstPos = { 270, 300 };
        POINT VolDesPos = { 370, 300 };
        POINT VolInsPos = { 400, 300 };

        int volumeSize = 10;
        int currentVolume = 50;
        int percent = currentVolume / volumeSize;


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
        POINT optionSize = { 75, 42 };
        POINT loginSize = { 99, 43 };
        POINT inputSize = { 60, 11 };
        POINT sizeSound = { 25, 29 };
        POINT sizeVolBtn = { 14, 21 };
        POINT sizeEdit = { 7, 12 };


        // avoid double click
        std::chrono::steady_clock::time_point lastMouseClickTime;
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 200; // 200 ms debounce delay

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

    class MapScreen : public Screen {
    protected:
        // hbitmap
        HBITMAP background = nullptr;
        HBITMAP tower = nullptr;              // tower
        HBITMAP towerInitPlace = nullptr;     // Ô chứa tháp
        HBITMAP instructionBoard = nullptr;   // Bảng hướng dẫn 
        HBITMAP enemy1 = nullptr;              // enemy
        HBITMAP enemy2 = nullptr;              // enemy
        HBITMAP enemy3 = nullptr;              // enemy
        HBITMAP hamburger = nullptr;          // hamburger button
        HBITMAP play_or_pause = nullptr;      // nut play hoac pause
        HBITMAP hbullet = nullptr;            // bullet

        // instruction pos
        POINT instructionPos = { 800, 50 };
        POINT hamburgerPos = { 1200, 5 };
        bool displayBoard = true;

        // position init place of box
        POINT towerInitPos = { 25, 520 };
        
        // buton play or pause 
        POINT posbuttonplay = { 580, 570 };

        // delay hand variable
        std::chrono::steady_clock::time_point lastMouseClickTime;
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 200; // 200 ms debounce delay

        // enemy 
        std::vector<cenemy> enemylist;
        POINT Einit;              // enemy position

        // tower
        std::vector<ctower> towerlist;
        POINT Turretinit;         // tower position 

        // tower de chon di chuyen
        ctower Tpicking;
        POINT TcurrentPick;
        bool isPicking = false;

        // size
        POINT buttonSize = { 26, 29 };
        POINT boardSize = { 260, 180 };
        POINT towerSize = { 20, 30 };

        // support 


        /* =======================================

        FIXBIG

        ======================================= */

        bool checkValidPos(POINT pos) {
            return true;
        }
        bool isInRange(POINT pos, int range) {
            return range < sqrt((pos.x * pos.x + pos.y * pos.y));
        }

    public:
        //MapScreen();
        virtual ~MapScreen() {}

        virtual void loadContent(int width, int height) = 0;
        virtual void handleInput(HWND hwnd) = 0;
        virtual void update(float delta) = 0;
        virtual void render(HDC hdc) = 0;
    };

    class PlayScreen : public MapScreen {
    private:
        vector<POINT> epath = {
            {-100, 150},
            {390, 150},
            {390, 490},
            {1200, 490},
        };

    public:
        PlayScreen();
        ~PlayScreen();

        void loadContent(int width, int height) override;
        void handleInput(HWND hwnd) override;
        void update(float delta) override;
        void render(HDC hdc) override;
    };

    class PlayScreen2 : public MapScreen {
    private:
        vector<POINT> epath = {
            {-100, 115},
            {435, 115},
            {435, 330},
            {265, 330},
            {265, 515},
            {1200, 515},
        };

    public:
        PlayScreen2();
        ~PlayScreen2();

        void loadContent(int width, int height) override;
        void handleInput(HWND hwnd) override;
        void update(float delta) override;
        void render(HDC hdc) override;
    };

    class PlayScreen3 : public MapScreen {
    private:
        vector<POINT> epath1 = {
            {-100, 170},
            {460, 170},
            {460, 450},
            {1200, 450}
        };

        vector<POINT> epath2 = {
            { 280, 800 },
            { 280, 450 },
            { 1200, 450 }
        };

    public:
        PlayScreen3();
        ~PlayScreen3();

        void loadContent(int width, int height) override;
        void handleInput(HWND hwnd) override;
        void update(float delta) override;
        void render(HDC hdc) override;
    };

    class PlayScreen4 : public MapScreen {
    private:
        vector<POINT> epath1 = {
            { -100, 160 },
            { 660, 160 },
            { 660, 800 },
        };

        vector<POINT> epath2 = {
            { 290, -100 },
            { 290, 400 },
            { 1200, 400 }
        };

    public:
        PlayScreen4();
        ~PlayScreen4();

        void loadContent(int width, int height) override;
        void handleInput(HWND hwnd) override;
        void update(float delta) override;
        void render(HDC hdc) override;
    };
}