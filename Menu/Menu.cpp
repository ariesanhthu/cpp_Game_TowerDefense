#include "Menu.h"
#include <string>

int Menu::menuCodeStatus = CHOOSEMAP;

Menu::Menu() : background(nullptr), board(nullptr) {}

Menu::~Menu() {
    releaseResource();
}

//void Menu::setWindowFather(HWND hwnd) {
//    this->fatherWindow = hwnd;
//}

void Menu::setWindowRect(RECT rect) {
    this->windowSize.x = rect.right - rect.left;
    this->windowSize.y = rect.bottom - rect.top;
}

void Menu::loadResources() {
    // Load main resources
    background = graphics.LoadBitmapImage(BMP_BACKGROUND_MAINSCREEN, 3);
    board = graphics.LoadBitmapImage(BMP_BOARD, 3);

    // Create buttons with appropriate bitmaps
    /*buttons.emplace_back(std::make_unique<Button>(fatherWindow, 101, POINT{ 100, 100 }, buttonSize));
    buttons.back()->setImages(BMP_BUTTON, BMP_SELECTING_BUTTON, BMP_ONCLICK_BUTTON, 1.0);
    buttons.back()->setCallback([]() {
        Menu::menuCodeStatus = CHOOSEMAP;
        MessageBox(nullptr, L"CHOOSEMAP clicked!", L"Info", MB_OK);
        });

    buttons.emplace_back(std::make_unique<Button>(fatherWindow, 102, POINT{ 100, 160 }, buttonSize));
    buttons.back()->setImages(BMP_BUTTON, BMP_SELECTING_BUTTON, BMP_ONCLICK_BUTTON, 1.0);
    buttons.back()->setCallback([]() {
        Menu::menuCodeStatus = CONTINUE;
        MessageBox(nullptr, L"CONTINUE clicked!", L"Info", MB_OK);
        });*/

    // Add more buttons as needed...
    /*for (auto& button : buttons) {
        button->create();
    }*/
}

void Menu::render(HDC hdc) {
    // Render the background
    graphics.DrawBitmap(background, posBackground, hdc);

    /*for (auto& button : buttons) {
        button->render(hdc);
    }*/

    switch (menuCodeStatus) {
    case DEFAULT:
        // Render buttons in their current state
        break;
    case CHOOSEMAP:
        graphics.DrawBitmap(board, posBoard, hdc);
        break;
    case CONTINUE:
        // Render continue screen elements
        break;
    default:
        break;
    }
}

void Menu::releaseResource() {
    // Release bitmap resources
    graphics.ReleaseBitmap(background);
    graphics.ReleaseBitmap(board);

    // Buttons are managed by smart pointers; no need for manual cleanup
}

//void Menu::handleMenuEvent(UINT message, WPARAM wParam, LPARAM lParam) {
//    for (auto& button : buttons) {
//        button->handleEvent(message, wParam, lParam);
//    }
//}
