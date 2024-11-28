#pragma once
#include "ScreenManager.h"
#include "Graphic.h"
#include <vector>

//#include <fstream>

using namespace std;
namespace towerdefense
{
    // Constructor
    MainScreen::MainScreen() {
        // Xác định vị trí các nút bấm
        buttonPositions = {
            {1280 / 10 * 1, 720 * 7 / 10},   // Play button
            {1280 / 10 * 3, 720 * 7 / 10},   // Pause button
            {1280 / 10 * 5, 720 * 7 / 10},   // Trophy button
            {1280 / 10 * 7, 720 * 7 / 10},   // Settings button
            {1280 / 10 * 9, 720 * 7 / 10}    // Exit button
        };

        initpoint = { 182, 700 };
        currentpoint = initpoint;
        endpoint = { 182, 42 };

        optionPositions = {
            currentpoint,
            currentpoint,
            currentpoint,
            currentpoint
        };

    }

    // Destructor
    MainScreen::~MainScreen() {
        // Giải phóng tài nguyên

        Graphic::ReleaseBitmap(background);
        Graphic::ReleaseBitmap(button);
        Graphic::ReleaseBitmap(button_down);
        Graphic::ReleaseBitmap(button_hover);
        Graphic::ReleaseBitmap(board);
        Graphic::ReleaseBitmap(map1opt);
        Graphic::ReleaseBitmap(map2opt);
        Graphic::ReleaseBitmap(map3opt);
        Graphic::ReleaseBitmap(map4opt);
        Graphic::ReleaseBitmap(opt_hover);

        /*DeleteObject(background);
        DeleteObject(button)*/;
    }

    int MainScreen::index = -1;
    int MainScreen::hover = -1;
    int MainScreen::menu = 0;

    void MainScreen::loadContent(Graphic& graphic, int width, int height) {
        // Tính toán tỉ lệ dựa trên kích thước màn hình
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        // Tải hình nền với tỉ lệ mới

        background = graphic.LoadBitmapImage(L"Assets/background/map4.bmp", scale);

        // default button
        button = graphic.LoadBitmapImage(L"Assets/button/button_up.bmp", scaleB);
        button_down = graphic.LoadBitmapImage(L"Assets/button/button_down.bmp", scaleB);
        button_hover = graphic.LoadBitmapImage(L"Assets/button/selectBox.bmp", scaleB);
        
        //board
        board = graphic.LoadBitmapImage(L"Assets/board/board.bmp", scaleB);

        //Option 
        map1opt = graphic.LoadBitmapImage(L"Assets/map_resize/map1_scaleDown.bmp", scaleB);
        map2opt = graphic.LoadBitmapImage(L"Assets/map_resize/map2_scaleDown.bmp", scaleB);
        map3opt = graphic.LoadBitmapImage(L"Assets/map_resize/map3_scaleDown.bmp", scaleB);
        map4opt = graphic.LoadBitmapImage(L"Assets/map_resize/map4_scaleDown.bmp", scaleB);
        opt_hover = graphic.LoadBitmapImage(L"Assets/board/border.bmp", scaleB);

        // Cập nhật vị trí nút bấm theo tỉ lệ
        /*for (auto& pos : buttonPositions) {
            pos.x = static_cast<int>(pos.x * scaleB);
            pos.y = static_cast<int>(pos.y * scaleB);
        }*/
    }

    void MainScreen::handleInput() {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        hover = -1;

        if (menu == 0) {
            for (size_t i = 0; i < buttonPositions.size(); ++i) {
                RECT buttonRect = {
                    buttonPositions[i].x,
                    buttonPositions[i].y,
                    buttonPositions[i].x + buttonSize.x * 3, // Button width
                    buttonPositions[i].y + buttonSize.y * 3  // Button height
                };

                if (PtInRect(&buttonRect, cursorPos)) {
                    hover = static_cast<int>(i);
                    break;
                }
            } 
        }
        else if (menu == 1) {
            for (size_t i = 0; i < optionPositions.size(); ++i) {
                RECT buttonRect = {
                    optionPositions[i].x,
                    optionPositions[i].y,
                    optionPositions[i].x + optionSize.x, // Button width
                    optionPositions[i].y + optionSize.y  // Button height
                };

                if (PtInRect(&buttonRect, cursorPos)) {
                    hover = static_cast<int>(i);
                    break;
                }
            }
        }

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
            if (menu == 0) {
                for (size_t i = 0; i < buttonPositions.size(); ++i) {
                    RECT buttonRect = {
                        buttonPositions[i].x,
                        buttonPositions[i].y,
                        buttonPositions[i].x + buttonSize.x * 3, // Button width
                        buttonPositions[i].y + buttonSize.y * 3 // Button height
                    };

                    if (PtInRect(&buttonRect, cursorPos)) {
                        // Button click detected
                        switch (i) {
                        case 0: // Play button
                            index = 0;
                            menu = 1;
                            isPopup = true;
                            break;
                        case 1: // Pause button
                            index = 1;
                            break;
                        case 2: // Trophy button
                            index = 2;
                            break;
                        case 3: // Settings button
                            index = 3;
                            break;
                        case 4: // Exit button
                            index = 4;
                            PostQuitMessage(0); // Exit the program
                            break;
                        }
                    }
                }
            }
            else if (menu == 1) {
                RECT boardRect = {
                    endpoint.x,
                    endpoint.y,
                    endpoint.x + sizeBoard.x, // boardsize width
                    endpoint.y + sizeBoard.y // boardsize height
                };
                if (!PtInRect(&boardRect, cursorPos)) {
                    //isPopdown = true;
                    isPopup = false;
                    currentpoint = initpoint;
                    menu = 0;
                }
                for (size_t i = 0; i < buttonPositions.size(); ++i) {
                    RECT optionRect = {
                        buttonPositions[i].x,
                        buttonPositions[i].y,
                        buttonPositions[i].x + optionSize.x, // Button width
                        buttonPositions[i].y + optionSize.y // Button height
                    };

                    if (PtInRect(&optionRect, cursorPos)) {
                        // Button click detected

                        // sau nay xoa test
                        switch (i) {
                        case 0: // Play button
                            OutputDebugString(L"Map");
                            break;
                        case 1: // Pause button
                            OutputDebugString(L"Map");
                            break;
                        case 2: // Trophy button
                            OutputDebugString(L"Map");
                            break;
                        case 3: // Settings button
                            OutputDebugString(L"Map");
                            break;
                        }
                    }
                }
            }
        }
    }


    // Update logic (nếu có animation hoặc logic khác)
    void MainScreen::update(float delta) {
        int speed = 200; // Speed in pixels per second

        // Update board position
        if (isPopup) {
            if (currentpoint.y > endpoint.y) {
                currentpoint.y -= static_cast<int>(speed * delta);

                if (currentpoint.y < endpoint.y) {
                    currentpoint.y = endpoint.y; // Snap to the endpoint to prevent overshooting
                }

                // Update option positions relative to the board
                for (size_t i = 0; i < optionPositions.size(); ++i) {
                    if (i == 0) {
                        optionPositions[i].x = currentpoint.x + 80; 
                        optionPositions[i].y = currentpoint.y + 80; 
                    }
                    else if (i == 1) {
                        optionPositions[i].x = currentpoint.x + 450;
                        optionPositions[i].y = currentpoint.y + 80;
                    }
                    else if (i == 2) {
                        optionPositions[i].x = currentpoint.x + 80;
                        optionPositions[i].y = currentpoint.y + 320;
                    }
                    else if (i == 3) {
                        optionPositions[i].x = currentpoint.x + 450;
                        optionPositions[i].y = currentpoint.y + 320;
                    }
                }
            }
        }
        else {
            if (currentpoint.y < initpoint.y) {
                currentpoint.y += static_cast<int>(speed * delta);

                if (currentpoint.y > initpoint.y) {
                    currentpoint.y = initpoint.y; // Snap to the initial position
                }

                // Reset option positions
                for (size_t i = 0; i < optionPositions.size(); ++i) {
                    optionPositions[i].y = currentpoint.y + 30 + (i * 60);
                }
            }
        }
    }


    void MainScreen::render(HDC hdc) {
        // Vẽ hình nền với kích thước đã thay đổi

        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
        if (menu == 0) {
            // Vẽ các nút bấm theo tỉ lệ
            for (size_t i = 0; i < buttonPositions.size(); ++i) {
                POINT buttonPos = buttonPositions[i];
                if (i == index) {
                    buttonPos.y += 8;
                    Graphic::DrawBitmap(button_down, buttonPos, hdc);
                    index = -1;
                }
                else {
                    if (i == hover) {
                        POINT buttonPosHover = buttonPositions[i];
                        buttonPosHover.y -= 21;
                        buttonPosHover.x -= 18;
                        Graphic::DrawBitmap(button_hover, buttonPosHover, hdc);
                        hover = -1;
                    }
                    Graphic::DrawBitmap(button, buttonPos, hdc); // Vẽ nút với tỉ lệ đã cập nhật
                }
            }
        }
        else if (menu == 1) {
            //Graphic::DrawBitmap(background, { 0, 0 }, hdc);
            for (size_t i = 0; i < buttonPositions.size(); ++i) {
                POINT buttonPos = buttonPositions[i];
                Graphic::DrawBitmap(button, buttonPos, hdc); // Vẽ nút với tỉ lệ đã cập nhật
            }

            Graphic::DrawBitmap(board, currentpoint, hdc);

            for (size_t i = 0; i < optionPositions.size(); i++) {
                POINT pos = optionPositions[i];

                if (i == hover) Graphic::DrawBitmap(opt_hover, {pos.x - 3, pos.y - 3}, hdc);

                if (i == 0) Graphic::DrawBitmap(map1opt, pos, hdc);
                else if (i == 1) Graphic::DrawBitmap(map2opt, pos, hdc);
                else if (i == 2) Graphic::DrawBitmap(map3opt, pos, hdc);
                else if (i == 3) Graphic::DrawBitmap(map4opt, pos, hdc);
            }
        }
    }
}