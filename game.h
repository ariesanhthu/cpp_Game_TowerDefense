#pragma once
#include <windows.h>
#include <string>
#include "Graphic.h"

// include menu class
// Thư sửa link folder sau 
#include "Menu/Menu.h"

// include map1, map2, map3, map4 later 
// #include "cgame.h"

namespace towerdefense {

    // enum screen để quản lý vị trí các trang
    // không biết đặt ở đâu là hợp lý
    enum screen {
        MENU = 10,
        LOGIN = 11,
        MAP1 = 1,
        MAP2 = 2,
        MAP3 = 3,
        MAP4 = 4
    };

    // window variable 
    const  int SCALE_FACTOR = 3;
    const  int CELL_SIZE = 1;            // Pixel size
    const  int GAME_WIDTH = 395 * 3;     // Width in cells
    const  int GAME_HEIGHT = 213 * 3;    // Height in cells
    const  int TIMER_INTERVAL = 30;      // Timer interval in milliseconds

    class Game {
        friend LRESULT CALLBACK WindowCallback(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        HINSTANCE hInstance;
        HWND windowHandle = 0;
        bool running = false;
        std::wstring windowTitle;
        int windowWidth = GAME_WIDTH * CELL_SIZE + 16;
        int windowHeight = GAME_HEIGHT * CELL_SIZE + 39;

        Graphic graphics; // Instance of the Graphic class

    public:
        Game();
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;


        ~Game();

        static Game& getInstance();
        static void start();
        static void setWindowProperties(const std::wstring& title, int width, int height);


        // trạng thái của screen
        static int ScreenCode;

    public: 
        // Menu là 1 biến của game 
        Menu* menu;

        // game1, game2, ... 
        // cgame game1;
        // cgame game2;

    private:
        void startWindow();

        void loadResources();
        void render(HDC hdc);
        void realeaseResource();
    };
}
