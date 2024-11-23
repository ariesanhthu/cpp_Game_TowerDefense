#pragma once
#ifndef __menu_h__
#define __menu_h__

#include "constant.h"
#include "Graphic.h"

// xử lý tạo window mới hơi hard
//#include "Button.h"


#include <windows.h>
#include <vector>
#include <memory>

class Menu {
    Graphic graphics;

    // Responsive attributes
    POINT windowSize;

    // Parent window handle
    //HWND fatherWindow;

    // Menu codes for state tracking
    enum menuCode {
        DEFAULT = 0,
        CHOOSEMAP = 1,
        CONTINUE = 2,
        LEADERBOARD = 3,
        SETTING = 4,
        EXIT = 5,
    };

private:
    // Bitmap resources
    HBITMAP background;
    HBITMAP board;

    // Positions and sizes
    POINT sizeBackground = { 395, 213 };
    POINT sizeBoard = { 231, 149 };
    POINT sizeButton = { 78, 87 };


    POINT posBackground = { 0, 0 };
    POINT posBoard = { 182, 42 };

    // Buttons
    //std::vector<std::unique_ptr<Button>> buttons;

public:
    static int menuCodeStatus;

    Menu();
    ~Menu();

    //void setWindowFather(HWND hwnd);
    void setWindowRect(RECT rect);
    void loadResources();
    void render(HDC hdc);
    void releaseResource();
    //void handleMenuEvent(UINT message, WPARAM wParam, LPARAM lParam);
};

#endif // !__menu_h__
