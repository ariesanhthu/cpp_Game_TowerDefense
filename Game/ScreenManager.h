#pragma once
#include <vector>
#include <memory>
#include "Graphic.h"
#include <vector>
#include "Observer.h"

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

    class MainScreen : public Screen {
    private:
        HBITMAP background = nullptr;             // Hình nền
        HBITMAP button = nullptr;                 // Danh sách các nút bấm
        HBITMAP button_down = nullptr;
        HBITMAP button_hover = nullptr;
        HBITMAP board = nullptr;
        HBITMAP map1opt = nullptr; 
        HBITMAP map2opt = nullptr; 
        HBITMAP map3opt = nullptr; 
        HBITMAP map4opt = nullptr; 
        HBITMAP opt_hover = nullptr;
        HBITMAP login = nullptr;
        HBITMAP login_down = nullptr;
        HBITMAP login_hover = nullptr;
        HBITMAP input = nullptr;
        HBITMAP loginText = nullptr;
        HBITMAP nameText = nullptr;
        HBITMAP passwordText = nullptr;

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
        bool isAboutUsPopup = false;

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

        POINT buttonSize = { 26, 29 };
        POINT sizeBoard = { 693, 447 };
        POINT optionSize = { 300, 168 };
        POINT loginSize = { 99, 43 };
        POINT inputSize = { 60, 11 };

    public:
        MainScreen();
        ~MainScreen();

        void loadContent(Graphic& graphic, int width, int height) override;
        void handleInput() override; 
        void update(float delta) override;
        void render(HDC hdc) override;
        //void resizeContent(int windowWidth, int windowHeight) override;
    };
}