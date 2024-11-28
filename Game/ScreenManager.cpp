#pragma once
#include "ScreenManager.h"
#include "Graphic.h"
#include <vector>



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
    }

    // Destructor
    MainScreen::~MainScreen() {
        // Giải phóng tài nguyên

        Graphic::ReleaseBitmap(background);
        Graphic::ReleaseBitmap(button);
        Graphic::ReleaseBitmap(button_down);
        Graphic::ReleaseBitmap(button_hover);


        /*DeleteObject(background);
        DeleteObject(button)*/;
    }

    int MainScreen::index = -1;
    int MainScreen::hover = -1;

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
        button_hover = graphic.LoadBitmapImage(L"Assets/button/select.bmp", scaleB);

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

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
            for (size_t i = 0; i < buttonPositions.size(); ++i) {
                RECT buttonRect = {
                    buttonPositions[i].x,
                    buttonPositions[i].y,
                    buttonPositions[i].x + buttonSize.x * 3, // Button width
                    buttonPositions[i].y + buttonSize.y * 3 // Button height
                };

                if (PtInRect(&buttonRect, cursorPos)) {
                    // Button click detected
                    hover = i;
                    switch (i) {
                    case 0: // Play button
                        index = 0;
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


    }


    // Update logic (nếu có animation hoặc logic khác)
    void MainScreen::update(float delta) {
        // Cập nhật trạng thái màn hình (nếu cần)
        
    }

    void MainScreen::render(HDC hdc) {
        // Vẽ hình nền với kích thước đã thay đổi
        Graphic::DrawBitmap(background, { 0, 0 }, hdc);

        // Vẽ các nút bấm theo tỉ lệ
        for (size_t i = 0; i < buttonPositions.size(); ++i) {
            POINT buttonPos = buttonPositions[i];
            if (i == index) {
                buttonPos.y += 8;
                Graphic::DrawBitmap(button_down, buttonPos, hdc);
                index = -1;
            }
            if (i == hover) {
                buttonPos.y += 8;
                Graphic::DrawBitmap(button_hover, buttonPos, hdc);
                hover = -1;
            }
            else {
                Graphic::DrawBitmap(button, buttonPos, hdc); // Vẽ nút với tỉ lệ đã cập nhật
            }
        }
    }

}