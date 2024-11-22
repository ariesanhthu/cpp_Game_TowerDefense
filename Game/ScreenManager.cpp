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
        {1280 / 10, 720 * 7 / 10},  // Play button
        {1280 / 10 * 3, 720 * 7 / 10},   // Pause button
        {1280 / 10 * 5, 720 * 7 / 10},   // Trophy button
        {1280 / 10 * 7, 720 * 7 / 10}, // Settings button
        {1280 / 10 * 9, 720 * 7 / 10} // Exit button
            };
    }

    // Destructor
    MainScreen::~MainScreen() {
        // Giải phóng tài nguyên
        DeleteObject(background);
        for (auto& button : buttons) {
            DeleteObject(button);
        }
    }

    // Load resources
    //void MainScreen::loadContent(Graphic& graphic) {
    //    // Tải hình nền
    //    background = graphic.LoadBitmapImage(L"Assets/map4.bmp", 4.0);

    //    // Tải các nút bấm
    //    buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", 4.0));
    //    buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", 4.0));
    //    buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", 4.0));
    //    buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", 4.0));
    //    buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", 4.0));
    //}
    void MainScreen::loadContent(Graphic& graphic, int width, int height) {
        // Tính toán tỉ lệ dựa trên kích thước màn hình
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3; // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        // Tải hình nền với tỉ lệ mới
        background = graphic.LoadBitmapImage(L"Assets/map4.bmp", scale);

        // Tải các nút bấm với tỉ lệ mới
        buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", scaleB));
        buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", scaleB));
        buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", scaleB));
        buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", scaleB));
        buttons.push_back(graphic.LoadBitmapImage(L"Assets/button_up.bmp", scaleB));

        // Cập nhật vị trí nút bấm theo tỉ lệ
        /*for (auto& pos : buttonPositions) {
            pos.x = static_cast<int>(pos.x * scaleB);
            pos.y = static_cast<int>(pos.y * scaleB);
        }*/
    }


    void MainScreen::handleInput() {
        // Giả sử bạn nhận được sự kiện chuột từ Windows Message Loop
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        // Kiểm tra xem chuột có nhấn vào nút nào không
        for (size_t i = 0; i < buttons.size(); ++i) {
            RECT buttonRect = {
                buttonPositions[i].x,
                buttonPositions[i].y,
                buttonPositions[i].x + 50, // Chiều rộng nút
                buttonPositions[i].y + 50 // Chiều cao nút
            };

            if (PtInRect(&buttonRect, cursorPos)) {
                // Xử lý nhấn nút (ví dụ: chuyển sang màn hình khác)
                if (i == 0) {
                    OutputDebugString(L"Play button clicked!\n");
                }
                else if (i == 4) {
                    OutputDebugString(L"Exit button clicked!\n");
                    PostQuitMessage(0); // Thoát chương trình
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
        for (size_t i = 0; i < buttons.size(); ++i) {
            POINT buttonPos = buttonPositions[i];
            Graphic::DrawBitmap(buttons[i], buttonPos, hdc); // Vẽ nút với tỉ lệ đã cập nhật
        }
    }

}