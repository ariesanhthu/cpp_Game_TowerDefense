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
            {1280 / 10 * 9, 720 * 7 / 10},    // Exit button
            {1280 / 10 * 9, 720 * 7 / 100}      // about us
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

        loginPosition = { 1280 / 10 * 6, 720 * 7 / 100 };

        dummyDataName.resize(dummyData.size());
        dummyDataPoint.resize(dummyData.size());
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
        Graphic::ReleaseBitmap(login); 
        Graphic::ReleaseBitmap(login_down);
        Graphic::ReleaseBitmap(login_hover);
        Graphic::ReleaseBitmap(input);
        Graphic::ReleaseBitmap(loginText);
        Graphic::ReleaseBitmap(nameText);
        Graphic::ReleaseBitmap(passwordText);
        Graphic::ReleaseBitmap(inputtextbitmap);
        Graphic::ReleaseBitmap(continueTitle);
        Graphic::ReleaseBitmap(arrow);
        for (auto i : dummyDataName) {
            Graphic::ReleaseBitmap(i);
        }
        for (auto i : dummyDataPoint) {
            Graphic::ReleaseBitmap(i);
        }
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
        float scaleC = 5;                                   // scale cho input
        float scaleD = 10;                                   // sacle cho text login

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

        // login 
        login = graphic.LoadBitmapImage(L"Assets/button/login_up.bmp", scaleB); 
        login_down = graphic.LoadBitmapImage(L"Assets/button/login_down.bmp", scaleB);
        login_hover = graphic.LoadBitmapImage(L"Assets/button/selectBox2.bmp", scaleB);
        input = graphic.LoadBitmapImage(L"Assets/button/input2.bmp", scaleC);
        loginText = graphic.LoadCustomTest("LOGIN", scaleD);
        nameText = graphic.LoadCustomTest("USERNAME", scaleC);
        passwordText = graphic.LoadCustomTest("PASSWORD", scaleC);
        inputtextbitmap = graphic.LoadCustomTest(inputtext, scaleB);

        //continue 
        for (int i = 0; i < dummyData.size(); i++) {
            dummyDataName[i] = graphic.LoadCustomTest((string)dummyData[i].getName(), 3);
            dummyDataPoint[i] = graphic.LoadCustomTest(to_string(dummyData[i].getPoint()), 3);
        }
        continueTitle = graphic.LoadCustomTest("CONTINUE", scaleD);
        arrow = graphic.LoadBitmapImage(L"Assets/arrow.bmp", scaleC);

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

        // hover handling
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

            RECT LoginRect = {
                    loginPosition.x,
                    loginPosition.y,
                    loginPosition.x + loginSize.x * 3, // Button width
                    loginPosition.y + loginSize.y * 3 // Button height
            };
            if (PtInRect(&LoginRect, cursorPos)) {
                hover = 101;
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
        else if (menu == 2) {
            for (size_t i = 0; i < dummyData.size(); ++i) {
                RECT nameRect = {
                    firstplayerCoverPos.x - 100,  // Adjust x to match hover offset
                    firstplayerCoverPos.y + static_cast<int>(i) * 100,  // Top y
                    firstplayerCoverPos.x + 200,  // Width of the rectangle
                    firstplayerCoverPos.y + static_cast<int>(i) * 100 + 80  // Height of the rectangle
                };

                if (PtInRect(&nameRect, cursorPos)) {
                    hover = static_cast<int>(i);
                    break;
                }
            }
        }

        // on mouse click handling
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed

            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;

                if (menu == 0) {
                    for (size_t i = 0; i < buttonPositions.size(); ++i) {
                        RECT buttonRect = {
                            buttonPositions[i].x,
                            buttonPositions[i].y,
                            buttonPositions[i].x + buttonSize.x * 3, // Button width
                            buttonPositions[i].y + buttonSize.y * 3 // Button height
                        };

                        if (PtInRect(&buttonRect, cursorPos)) {
                            switch (i) {
                            case 0:
                                index = 0;
                                menu = 1;
                                isChoosemapPopup = true;
                                break;
                            case 1:
                                index = 1;
                                menu = 2;
                                isPopupEffect = true;
                                break;
                            case 2:
                                index = 2;
                                menu = 3;
                                break;
                            case 3:
                                index = 3;
                                menu = 4;
                                break;
                            case 4:
                                index = 4;
                                menu = 5;
                                PostQuitMessage(0); // Exit the program
                                break;
                            case 5:
                                index = 5;
                                menu = 6;
                                isPopupEffect = true;
                                break;
                            }
                        }
                    }
                    RECT LoginRect = {
                        loginPosition.x,
                        loginPosition.y,
                        loginPosition.x + loginSize.x * 3, // Button width
                        loginPosition.y + loginSize.y * 3// Button height
                    };
                    if (PtInRect(&LoginRect, cursorPos)) {
                        // if click login
                        menu = 101;
                        index = 101;
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
                        isChoosemapPopup = false;
                        currentpoint = initpoint;
                        menu = 0;
                    }
                    for (size_t i = 0; i < optionPositions.size(); ++i) {
                        RECT optionRect = {
                            optionPositions[i].x,
                            optionPositions[i].y,
                            optionPositions[i].x + optionSize.x, // Button width
                            optionPositions[i].y + optionSize.y // Button height
                        };

                        if (PtInRect(&optionRect, cursorPos)) {
                            // Button click detected

                            // sau nay xoa test
                            switch (i) {
                            case 0:
                                notify(MOVESETTOWERSTATE);
                                break;
                            case 1:
                                //OutputDebugString(L"Map");
                                break;
                            case 2:
                                //OutputDebugString(L"Map");
                                break;
                            case 3:
                                //OutputDebugString(L"Map");
                                break;
                            }
                        }
                    }
                }
                else if (menu == 2) {
                    RECT boardRect = {
                        endpoint.x,
                        endpoint.y,
                        endpoint.x + sizeBoard.x, // boardsize width
                        endpoint.y + sizeBoard.y // boardsize height
                    };
                    if (!PtInRect(&boardRect, cursorPos)) {
                        //isPopdown = true;
                        isChoosemapPopup = false;
                        currentpoint = initpoint;
                        menu = 0;
                    }
                }
                else if (menu == 3) {

                }
                else if (menu == 4) {

                }
                else if (menu == 5) {

                }
                else if (menu == 6) {
                    RECT boardRect = {
                        endpoint.x,
                        endpoint.y,
                        endpoint.x + sizeBoard.x, // boardsize width
                        endpoint.y + sizeBoard.y // boardsize height
                    };
                    if (!PtInRect(&boardRect, cursorPos)) {
                        //isPopdown = true;
                        isChoosemapPopup = false;
                        currentpoint = initpoint;
                        menu = 0;
                    }
                }
                else if (menu == 101) {
                    // board
                    RECT boardRect = {
                        endpoint.x,
                        endpoint.y,
                        endpoint.x + sizeBoard.x, // boardsize width
                        endpoint.y + sizeBoard.y // boardsize height
                    };
                    if (!PtInRect(&boardRect, cursorPos)) {
                        //isPopdown = true;
                        isChoosemapPopup = false;
                        currentpoint = initpoint;
                        menu = 0;
                    }

                    // name input 
                    RECT inputNameRect = {
                        inputNamePosition.x,
                        inputNamePosition.y,
                        inputNamePosition.x + inputSize.x * 5, // boardsize width
                        inputNamePosition.y + inputSize.y * 5 // boardsize height
                    };
                    if (PtInRect(&inputNameRect, cursorPos)) {
                        start_to_input = true;
                    }
                    if (!PtInRect(&inputNameRect, cursorPos)) {
                        start_to_input = false;
                    }
                }
            }
        }

        // input handle
        if (start_to_input) {
            // Check if a key is pressed 
            for (wchar_t ch = 'A'; ch <= 'Z'; ++ch) {
                if (GetAsyncKeyState(ch) & 0x8000) {
                    auto now = std::chrono::steady_clock::now();
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() >= debounceDelayMs) {
                        lastKeyPressTime = now; // Update the last key press time

                        // Max 15 characters
                        if (inputtext.size() <= 15) {
                            inputtext.push_back(ch);  // Add the character to inputText
                        }

                        Graphic::ReleaseBitmap(inputtextbitmap); // Release old bitmap
                        inputtextbitmap = Graphic::LoadCustomTest(inputtext, 3);
                    }
                }
            }

            for (wchar_t ch = '0'; ch <= '9'; ++ch) {
                if (GetAsyncKeyState(ch) & 0x8000) {
                    auto now = std::chrono::steady_clock::now();
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() >= debounceDelayMs) {
                        lastKeyPressTime = now;

                        if (inputtext.size() <= 15) {
                            inputtext.push_back(ch);
                        }

                        Graphic::ReleaseBitmap(inputtextbitmap);
                        inputtextbitmap = Graphic::LoadCustomTest(inputtext, 3);
                    }
                }
            }

            // Handle Backspace
            if (GetAsyncKeyState(VK_BACK) & 0x8000 && !inputtext.empty()) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() >= debounceDelayMs) {
                    lastKeyPressTime = now;
                    inputtext.pop_back();

                    Graphic::ReleaseBitmap(inputtextbitmap);
                    inputtextbitmap = Graphic::LoadCustomTest(inputtext, 3);
                }
            }

            // Handle Enter
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() >= debounceDelayMs) {
                    lastKeyPressTime = now;

                    // Handle Enter logic
                    
                    

                    inputtext.clear();
                    start_to_input = false;
                }
            }
        }

    }

    // Update logic (nếu có animation hoặc logic khác)
    void MainScreen::update(float delta) {
        int speed = 500;

        // Update board position
        if (isChoosemapPopup) {
            if (currentpoint.y > endpoint.y) {
                currentpoint.y -= static_cast<int>(speed * delta);

                if (currentpoint.y < endpoint.y) {
                    currentpoint.y = endpoint.y;
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

        if (isPopupEffect) {
            if (currentpoint.y > endpoint.y) {
                currentpoint.y -= static_cast<int>(speed * delta);

                if (currentpoint.y < endpoint.y) {
                    currentpoint.y = endpoint.y;
                    isPopupEffect = false;
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

                    // tao hieu ung nhan nut
                    //Sleep(100);
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

            if (index == 101) {
                Graphic::DrawBitmap(login_down, { loginPosition.x, loginPosition.y + 8 }, hdc);
                index = -1;
            }
            else {
                if (hover == 101) {
                    Graphic::DrawBitmap(login_hover, { loginPosition.x - 18, loginPosition.y - 18 }, hdc);
                }
                Graphic::DrawBitmap(login, loginPosition, hdc);
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
        else if (menu == 2) {
            // continue
            Graphic::DrawBitmap(board, currentpoint, hdc);
            if (!isPopupEffect) {
                Graphic::DrawBitmap(continueTitle, titleContinuePos, hdc);
                for (int i = 0; i < dummyData.size(); i++) {
                    POINT pos = firstplayerCoverPos;
                    pos.y += i * 100;
                    Graphic::DrawBitmap(input, pos, hdc);
                }
                for (int i = 0; i < dummyData.size(); i++) {
                    POINT pos = firstplayerCoverPos;
                    pos.x += 30; 
                    pos.y += i * 100 + 20;
                    Graphic::DrawBitmap(dummyDataName[i], pos, hdc);
                }
                for (int i = 0; i < dummyData.size(); i++) {
                    POINT pos = firstplayerCoverPos;
                    pos.x += 250;
                    pos.y += i * 100 + 20;
                    Graphic::DrawBitmap(dummyDataPoint[i], pos, hdc);
                }
                for (int i = 0; i < dummyData.size(); i++) {
                    if (hover == i) {
                        POINT pos = firstplayerCoverPos;
                        pos.x -= 100;
                        pos.y += i * 100;
                        Graphic::DrawBitmap(arrow, pos, hdc);
                    }
                }
            }
        } 
        else if (menu == 3) {
            // Leaderboard 

            // copy from continue

        }
        else if (menu == 4) {
            // display nothing
        }
        else if (menu == 6) {
            for (size_t i = 0; i < buttonPositions.size(); ++i) {
                POINT buttonPos = buttonPositions[i];
                Graphic::DrawBitmap(button, buttonPos, hdc); // Vẽ nút với tỉ lệ đã cập nhật
            }

            Graphic::DrawBitmap(board, currentpoint, hdc);
        }
        else if (menu == 101) {
            Graphic::DrawBitmap(board, endpoint, hdc);
            Graphic::DrawBitmap(input, inputNamePosition, hdc);
            Graphic::DrawBitmap(input, inputPasswordPosition, hdc);
            Graphic::DrawBitmap(loginText, loginTextPos, hdc);
            Graphic::DrawBitmap(nameText, nameTextPos, hdc);
            Graphic::DrawBitmap(passwordText, passwordTextPos, hdc);
            if (start_to_input) {
                if (inputtext != "") {
                    Graphic::DrawBitmap(inputtextbitmap, { nameTextPos.x + 230 , nameTextPos.y + 10 }, hdc);
                }
                
            }
        }
    }

    //========================================================================================================================//


    setTowerScreen::setTowerScreen() {

    }

    setTowerScreen::~setTowerScreen() {
        Graphic::ReleaseBitmap(background);
    }

    void setTowerScreen::loadContent(Graphic& graphic, int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleC = 5;                                   // scale cho input
        float scaleD = 10;                                   // sacle cho text login


        graphic.LoadBitmapImage(L"Assets/background/map1.bmp", scale);
    }

    void setTowerScreen::handleInput() {

    }

    void setTowerScreen::update(float delta) {

    }

    void setTowerScreen::render(HDC hdc) {
        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
    }
}


