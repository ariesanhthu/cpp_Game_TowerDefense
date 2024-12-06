#pragma once
#include "ScreenManager.h"
#include "Graphic.h"
#include <vector>
#include <stdlib.h>

#include <fstream>

#define WM_CUSTOM_LOAD_SCREEN (WM_USER + 1)

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

        loginPosition = { (int)(1280 / 10 * 7.5), 720 * 7 / 100 };

        dummyDataName.resize(dummyData.size());
        dummyDataPoint.resize(dummyData.size());
    }

    // Destructor
    MainScreen::~MainScreen() {
        // Giải phóng tài nguyên
        Graphic::ReleaseBitmap(background);
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
        Graphic::ReleaseBitmap(play);
        Graphic::ReleaseBitmap(setting);
        Graphic::ReleaseBitmap(lead);
        Graphic::ReleaseBitmap(cont);
        Graphic::ReleaseBitmap(exit);
        Graphic::ReleaseBitmap(about);
        Graphic::ReleaseBitmap(catfam);
        Graphic::ReleaseBitmap(switchOff);
        Graphic::ReleaseBitmap(switchOn);
        Graphic::ReleaseBitmap(TitleSetting);
        Graphic::ReleaseBitmap(insVolBtn);
        Graphic::ReleaseBitmap(desVolBtn);
        Graphic::ReleaseBitmap(backgroundVol);
        Graphic::ReleaseBitmap(foregroundVol);

        for (auto i : dummyDataName) {
            Graphic::ReleaseBitmap(i);
        }
        for (auto i : dummyDataPoint) {
            Graphic::ReleaseBitmap(i);
        }

        OutputDebugStringA("~MainScreen\n");
    }

    int MainScreen::index = -1;
    int MainScreen::hover = -1;
    int MainScreen::menu  = 0;

    void MainScreen::loadContent(int width, int height) {
        // Tính toán tỉ lệ dựa trên kích thước màn hình
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale  = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleC = 5;                                   // scale cho input
        float scaleD = 10;                                   // sacle cho text login

        // Tải hình nền với tỉ lệ mới

        background              = Graphic::LoadBitmapImage(L"Assets/background/map4.bmp", scale);
        catfam                  = Graphic::LoadBitmapImage(L"Assets/decor/nameLogo.png", 2);

        // default button
        play                    = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 2); 
        cont                    = Graphic::LoadBitmapImage(L"Assets/button/btnContinue.png", 2); 
        lead                    = Graphic::LoadBitmapImage(L"Assets/button/btnLeaderboard.png", 2); 
        setting                 = Graphic::LoadBitmapImage(L"Assets/button/btnSetting.png", 2); 
        exit                    = Graphic::LoadBitmapImage(L"Assets/button/btnExit.png", 2); 
        about                   = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2); 
        button_hover            = Graphic::LoadBitmapImage(L"Assets/button/selectBox.bmp", 2);
        
        //board
        board                   = Graphic::LoadBitmapImage(L"Assets/board/board.bmp", scaleB);

        //Option 
        map1opt                 = Graphic::LoadBitmapImage(L"Assets/map_resize/map1_scaleDown.bmp", scaleB);
        map2opt                 = Graphic::LoadBitmapImage(L"Assets/map_resize/map2_scaleDown.bmp", scaleB);
        map3opt                 = Graphic::LoadBitmapImage(L"Assets/map_resize/map3_scaleDown.bmp", scaleB);
        map4opt                 = Graphic::LoadBitmapImage(L"Assets/map_resize/map4_scaleDown.bmp", scaleB);
        opt_hover               = Graphic::LoadBitmapImage(L"Assets/board/border.bmp", scaleB);

        // login 
        login                   = Graphic::LoadBitmapImage(L"Assets/button/loginBtn.png", 2); 
        login_down              = Graphic::LoadBitmapImage(L"Assets/button/loginBtnDown.png", 2);
        login_hover             = Graphic::LoadBitmapImage(L"Assets/button/selectBox2.bmp", 2);
        input                   = Graphic::LoadBitmapImage(L"Assets/button/input2.bmp", scaleC);
        loginText               = Graphic::LoadCustomTest("LOGIN", scaleD);
        nameText                = Graphic::LoadCustomTest("USERNAME", scaleC);
        passwordText            = Graphic::LoadCustomTest("PASSWORD", scaleC);
        inputtextbitmap         = Graphic::LoadCustomTest(inputtext, scaleB);

        // setting
        TitleSetting            = Graphic::LoadBitmapImage(L"Assets/setting/TitleSetting.bmp", 5);
        switchOff               = Graphic::LoadBitmapImage(L"Assets/decor/catWin0.png", 2);
        switchOn                = Graphic::LoadBitmapImage(L"Assets/decor/catWin1.png", 2);
        insVolBtn               = Graphic::LoadBitmapImage(L"Assets/setting/arrowUp.png", 2);   
        desVolBtn               = Graphic::LoadBitmapImage(L"Assets/setting/arrowDown.png", 2);    
        backgroundVol           = Graphic::LoadBitmapImage(L"Assets/setting/volumn.png", 2); 
        foregroundVol           = Graphic::LoadBitmapImage(L"Assets/setting/volumnOn.png", 2); 

        //continue 
        for (int i = 0; i < dummyData.size(); i++) {
            dummyDataName[i]    = Graphic::LoadCustomTest((string)dummyData[i].getName(), 3);
            dummyDataPoint[i]   = Graphic::LoadCustomTest(to_string(dummyData[i].getPoint()), 3);
        }
        continueTitle           = Graphic::LoadCustomTest("CONTINUE", scaleD);
        arrow                   = Graphic::LoadBitmapImage(L"Assets/arrow.bmp", scaleC);

        // Cập nhật vị trí nút bấm theo tỉ lệ
        /*for (auto& pos : buttonPositions) {
            pos.x = static_cast<int>(pos.x * scaleB);
            pos.y = static_cast<int>(pos.y * scaleB);
        }*/
    }

    void MainScreen::handleInput(HWND hwnd) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        // hover handling
        hover = -1;
        if (menu == 0) {
            for (int  i = 0; i < buttonPositions.size(); ++i) {
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
                    loginPosition.x + loginSize.x * 2, // Button width
                    loginPosition.y + loginSize.y * 2 // Button height
            };
            if (PtInRect(&LoginRect, cursorPos)) {
                hover = 101;
            }

        }
        else if (menu == 1) {
            for (int  i = 0; i < optionPositions.size(); ++i) {
                RECT buttonRect = {
                    optionPositions[i].x,
                    optionPositions[i].y,
                    optionPositions[i].x + optionSize.x * 3, // Button width
                    optionPositions[i].y + optionSize.y * 3 // Button height
                };

                if (PtInRect(&buttonRect, cursorPos)) {
                    hover = static_cast<int>(i);
                    break;
                }
            }
        }
        else if (menu == 2) {
            for (int  i = 0; i < dummyData.size(); ++i) {
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
                    for (int  i = 0; i < buttonPositions.size(); ++i) {
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
                                isPopupEffect = true;
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
                    for (int  i = 0; i < optionPositions.size(); ++i) {
                        RECT optionRect = {
                            optionPositions[i].x,
                            optionPositions[i].y,
                            optionPositions[i].x + optionSize.x * 3, // Button width
                            optionPositions[i].y + optionSize.y * 3  // Button height
                        };

                        if (PtInRect(&optionRect, cursorPos)) {
                            // Button click detected

                            
                            switch (i) {
                            case 0:
                                /*notify(MOVESETTOWERSTATE);*/
                                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 1, 0);
                                break;
                            case 1:
                                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
                                break;
                            case 2:
                                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 3, 0);
                                //OutputDebugString(L"Map");
                                break;
                            case 3:
                                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 4, 0);
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
                        isChoosemapPopup = false;
                        currentpoint = initpoint;
                        menu = 0;
                    }
                }
                else if (menu == 3) {
                    // leaderboard
                }
                else if (menu == 4) {
                    RECT boardRect = {
                        endpoint.x,
                        endpoint.y,
                        endpoint.x + sizeBoard.x, // boardsize width
                        endpoint.y + sizeBoard.y // boardsize height
                    };
                    if (!PtInRect(&boardRect, cursorPos)) {
                        //isPopdown = true;
                        isPopupEffect = false;
                        currentpoint = initpoint;
                        menu = 0;
                    }

                    RECT soundRect = {
                        soundPos.x,
                        soundPos.y,
                        soundPos.x + sizeSound.x * 2,
                        soundPos.y + sizeSound.y * 2
                    };
                    if (PtInRect(&soundRect, cursorPos)) {
                        if (!soundCheck) {
                            if (!PlaySoundW(L"Assets/test.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP | SND_LOOP)) {
                                MessageBox(hwnd, L"sound err", L"sound err", MB_OK);
                            } 
                            soundCheck = true;
                        }
                        else {
                            PlaySoundW(NULL, NULL, 0);
                            soundCheck = false;
                        }
                    }

                    RECT left = {
                        VolDesPos.x,
                        VolDesPos.y,
                        VolDesPos.x + sizeEdit.x * 3, // boardsize width
                        VolDesPos.y + sizeEdit.y * 3 // boardsize height
                    };
                    if (PtInRect(&left, cursorPos)) {
                        if (currentVolume == 0) currentVolume = 99;
                        currentVolume -= 9;
                        percent = currentVolume / volumeSize;
                        SetVolume(currentVolume);
                    }
                    RECT right = {
                        VolInsPos.x,
                        VolInsPos.y,
                        VolInsPos.x + sizeEdit.x * 3, // boardsize width
                        VolInsPos.y + sizeEdit.y * 3// boardsize height
                    };
                    if (PtInRect(&right, cursorPos)) {
                        if (currentVolume == 99) currentVolume = 0;
                        currentVolume += 9;
                        percent = currentVolume / volumeSize;
                        SetVolume(currentVolume);
                    }

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
                for (int  i = 0; i < optionPositions.size(); ++i) {
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
        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
        Graphic::DrawBitmap(catfam, { 0, 0 }, hdc);
        if (menu == 0) {
            for (int i = 0; i < buttonPositions.size(); ++i) {
                POINT buttonPos = buttonPositions[i];
                if (i == index) {
                    buttonPos.y += 8;

                    /* =====================
                    
                    FIX BUG CLICK 
                    
                    ====================== */ 

                    //Graphic::DrawBitmap(button_down, buttonPos, hdc);
                    index = -1;
                }
                else {
                    if (i == hover) {
                        POINT buttonPosHover = buttonPositions[i];
                        buttonPosHover.x -= 12;
                        buttonPosHover.y -= 14;
                        Graphic::DrawBitmap(button_hover, buttonPosHover, hdc);
                        hover = -1;
                    }

                    switch (i) {
                    case 0: 
                        Graphic::DrawBitmap(play, buttonPos, hdc); 
                        break;
                    case 1:
                        Graphic::DrawBitmap(cont, buttonPos, hdc); 
                        break;
                    case 2:
                        Graphic::DrawBitmap(lead, buttonPos, hdc); 
                        break;
                    case 3:
                        Graphic::DrawBitmap(setting, buttonPos, hdc); 
                        break;
                    case 4:
                        Graphic::DrawBitmap(exit, buttonPos, hdc); 
                        break;
                    case 5: 
                        Graphic::DrawBitmap(about, buttonPos, hdc);
                        break;
                    }
                }
            }

            if (index == 101) {
                Graphic::DrawBitmap(login_down, { loginPosition.x, loginPosition.y + 8 }, hdc);
                index = -1;
            }
            else {
                if (hover == 101) {
                    Graphic::DrawBitmap(login_hover, { loginPosition.x - 14, loginPosition.y - 7 }, hdc);
                }
                Graphic::DrawBitmap(login, loginPosition, hdc);
            }
        }
        else if (menu == 1) {
            //Graphic::DrawBitmap(background, { 0, 0 }, hdc);
            for (int  i = 0; i < buttonPositions.size(); ++i) {
                POINT buttonPos = buttonPositions[i];
                switch (i) {
                case 0:
                    Graphic::DrawBitmap(play, buttonPos, hdc);
                    break;
                case 1:
                    Graphic::DrawBitmap(cont, buttonPos, hdc);
                    break;
                case 2:
                    Graphic::DrawBitmap(lead, buttonPos, hdc);
                    break;
                case 3:
                    Graphic::DrawBitmap(setting, buttonPos, hdc);
                    break;
                case 4:
                    Graphic::DrawBitmap(exit, buttonPos, hdc);
                    break;
                case 5:
                    Graphic::DrawBitmap(about, buttonPos, hdc);
                    break;
                }
            }

            Graphic::DrawBitmap(board, currentpoint, hdc);

            for (int  i = 0; i < optionPositions.size(); i++) {
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

            // do not have user this time 
        }
        else if (menu == 4) {
            // setting 
            for (int i = 0; i < buttonPositions.size(); ++i) {
                POINT buttonPos = buttonPositions[i];
                switch (i) {
                case 0:
                    Graphic::DrawBitmap(play, buttonPos, hdc);
                    break;
                case 1:
                    Graphic::DrawBitmap(cont, buttonPos, hdc);
                    break;
                case 2:
                    Graphic::DrawBitmap(lead, buttonPos, hdc);
                    break;
                case 3:
                    Graphic::DrawBitmap(setting, buttonPos, hdc);
                    break;
                case 4:
                    Graphic::DrawBitmap(exit, buttonPos, hdc);
                    break;
                case 5:
                    Graphic::DrawBitmap(about, buttonPos, hdc);
                    break;
                }
            }

            Graphic::DrawBitmap(board, currentpoint, hdc);

            if (!isPopupEffect) {
                Graphic::DrawBitmap(TitleSetting, titlePos, hdc);
                
                if (soundCheck) {
                    Graphic::DrawBitmap(switchOn, soundPos, hdc); 
                }
                else {
                    Graphic::DrawBitmap(switchOff, soundPos, hdc);
                }

                Graphic::DrawBitmap(backgroundVol, VolFirstPos, hdc);

                for (int i = 0; i < percent; i++) {
                    POINT pos = VolFirstPos;
                    pos.x += i * 10;
                    Graphic::DrawBitmap(foregroundVol, pos, hdc);
                }

                Graphic::DrawBitmap(insVolBtn, VolInsPos, hdc);
                Graphic::DrawBitmap(desVolBtn, VolDesPos, hdc);
            }
        }
        else if (menu == 5) {
            // handle exit so do notthing here
        }
        else if (menu == 6) {
            for (int  i = 0; i < buttonPositions.size(); ++i) {
                POINT buttonPos = buttonPositions[i];
                switch (i) {
                case 0:
                    Graphic::DrawBitmap(play, buttonPos, hdc);
                    break;
                case 1:
                    Graphic::DrawBitmap(cont, buttonPos, hdc);
                    break;
                case 2:
                    Graphic::DrawBitmap(lead, buttonPos, hdc);
                    break;
                case 3:
                    Graphic::DrawBitmap(setting, buttonPos, hdc);
                    break;
                case 4:
                    Graphic::DrawBitmap(exit, buttonPos, hdc);
                    break;
                case 5:
                    Graphic::DrawBitmap(about, buttonPos, hdc);
                    break;
                }
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

    PlayScreen::PlayScreen() {
        // Initialize dummy enemies
        for (int i = 0; i < 10; i++) {
            cenemy dummy;
            std::vector<POINT> otherPath = epath;
            
            otherPath[0].x -= (i != 9 ? (i * (rand() % 300 + 100)) : 9*500);

            dummy.setPath(otherPath);
            enemylist.push_back(dummy);
        }

        enemylist[9].setHealth(450);

        Turretinit = { 50, 565 };
    }

    PlayScreen::~PlayScreen() {
        Graphic::ReleaseBitmap(background);
        Graphic::ReleaseBitmap(tower);
        Graphic::ReleaseBitmap(towerInitPlace);
        Graphic::ReleaseBitmap(instructionBoard);

        //
        Graphic::ReleaseBitmap(enemy1);
        Graphic::ReleaseBitmap(enemy2);
        Graphic::ReleaseBitmap(enemy3);
        
        Graphic::ReleaseBitmap(hamburger);
        Graphic::ReleaseBitmap(play_or_pause);
        Graphic::ReleaseBitmap(hbullet);
        Graphic::ReleaseBitmap(WantToContinue);
        Graphic::ReleaseBitmap(yesBtn);
        Graphic::ReleaseBitmap(noBtn);
        Graphic::ReleaseBitmap(boardYesNo);


        OutputDebugStringA("~PlayScreen\n");
    }

    void PlayScreen::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleC = 5;                                   // scale cho input
        float scaleD = 10;                                  // sacle cho text login
        float scaleE = 2;
        
        background           = Graphic::LoadBitmapImage(L"Assets/background/map1.bmp", scale);
        towerInitPlace       = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
        instructionBoard     = Graphic::LoadBitmapImage(L"Assets/game/info/board1.png", 1);
        
        //ENEMY LOAD
        enemy1               = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
        enemy3               = Graphic::LoadBitmapImage(L"Assets/game/enemy3/enemy3-1.png", 2);
        ///////////////////////////////////////////////////////////////////////////////////////////

        hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
        play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
        
        hbullet              = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
        
        tower                = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
        
        // route handle
        WantToContinue = Graphic::LoadCustomTest("WANTTOCONTINUE", 4);
        yesBtn = Graphic::LoadBitmapImage(L"Assets/button/AcceptBtn.png", 4);
        noBtn = Graphic::LoadBitmapImage(L"Assets/button/RejectBtn.png", 4);
        boardYesNo = Graphic::LoadBitmapImage(L"Assets/board/board.bmp", 1.5);
        
    }

    void PlayScreen::handleInput(HWND hwnd) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;
                // if click the play 
                RECT playRect = {
                    posbuttonplay.x,
                    posbuttonplay.y,
                    posbuttonplay.x + buttonSize.x * 1.8, // Button width
                    posbuttonplay.y + buttonSize.y * 1.8 // Button height
                };
                /*
                    HANDLE CLICK

                    PAUSE GAME || PLAY GAME
                */
                if (PtInRect(&playRect, cursorPos)) {
                    // if click play 
                    if (manageFirstTime) {
                        IsPlayGame = true;
                        manageFirstTime = false;
                        for (int i = 0; i < enemylist.size(); i++) {
                            enemylist[i].isMove = true;
                        }
                    }
                    else {
                        if (IsPlayGame) {
                            displayYesNoBoard = true;
                            IsPlayGame = false;
                            for (int i = 0; i < enemylist.size(); i++) {
                                enemylist[i].isMove = false;
                            }
                        }
                    }
                }


                if (displayYesNoBoard) {
                    // if yes
                    RECT yesRect = {
                        yesBtnPos.x,
                        yesBtnPos.y,
                        yesBtnPos.x + yesnoSize.x * 4, // Button width
                        yesBtnPos.y + yesnoSize.y * 4 // Button height
                    };
                    if (PtInRect(&yesRect, cursorPos)) {
                        displayYesNoBoard = false;
                        IsPlayGame = true;
                        for (int i = 0; i < enemylist.size(); i++) {
                            enemylist[i].isMove = true;
                        }
                    }

                    // if no
                    RECT noRect = {
                        noBtnPos.x,
                        noBtnPos.y,
                        noBtnPos.x + yesnoSize.x * 4, // Button width
                        noBtnPos.y + yesnoSize.y * 4 // Button height
                    };
                    if (PtInRect(&noRect, cursorPos)) {
                        PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                    }
                }
                
                // if click in hamburger display board 
                RECT hamburgerRect = {
                    hamburgerPos.x,
                    hamburgerPos.y,
                    hamburgerPos.x + buttonSize.x * 1.5, // Button width
                    hamburgerPos.y + buttonSize.y * 1.5 // Button height
                };
                if (PtInRect(&hamburgerRect, cursorPos)) {
                    displayBoard = !displayBoard;
                }
            }
        }

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            // if hold tower 
            RECT initTowerRect = {
                Turretinit.x,
                Turretinit.y,
                Turretinit.x + towerSize.x * 2, // Button width
                Turretinit.y + towerSize.y * 2 // Button height
            };
            if (PtInRect(&initTowerRect, cursorPos)) {
                isPicking = true;
            }
            else {
                isPicking = false;
            }
        }

        if (isPicking) {
            Tpicking.setLocation(cursorPos);    
        }
        else {
            // neu vi tri thoa dieu kien thi them vao list tower
            if (checkValidPos(TcurrentPick)) {
                towerlist.push_back(Tpicking);
            }
        }
    }

    void PlayScreen::update(float delta) {
        for (auto& enemy : enemylist) {
            if (enemy.isMove && !enemy.isEnd()) {
                enemy.update(delta);
            }
        }

        /*enemylist.erase(
            std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
                return e.isDead() || e.isEnd();  
                }),
            enemylist.end()
        );*/

        // Towers shoot at the nearest enemy in range and update bullets
        for (auto& tower : towerlist) {
            cenemy* nearestEnemy = nullptr;
            float minDistanceSquared = tower.getRange() * tower.getRange();
            POINT towerPos = tower.getLocation();

            // Xác định bounding box của phạm vi tower
            RECT rangeRect = {
                towerPos.x - static_cast<int>(tower.getRange()),
                towerPos.y - static_cast<int>(tower.getRange()),
                towerPos.x + static_cast<int>(tower.getRange()),
                towerPos.y + static_cast<int>(tower.getRange())
            };

            for (auto& enemy : enemylist) {
                if (!enemy.isMove || enemy.isEnd()) continue;

                POINT enemyPos = enemy.getCurr();
                if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi

                int dx = enemyPos.x - towerPos.x;
                int dy = enemyPos.y - towerPos.y;
                float distanceSquared = static_cast<float>(dx * dx + dy * dy);

                if (distanceSquared < minDistanceSquared) {
                    minDistanceSquared = distanceSquared;
                    nearestEnemy = &enemy;
                }
            }

            if (nearestEnemy) {
                // tower.shootAt(nearestEnemy->getCurr());
                tower.shootAt(nearestEnemy);
                //POINT pos = tower.getBullet().getCurr();
                //if (pos.x)
                //nearestEnemy->takeDamage(tower.getBullet().getDamage());
            }

            tower.updateBullet();
        }
    }

    void PlayScreen::render(HDC hdc) {

        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
        Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
        Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
        if (displayBoard) {
            Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
        }
        Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);

        int numberEnemy = enemylist.size();

        for (int i = 0; i < numberEnemy - 1; i++)
            if(!enemylist[i].isDead() && !enemylist[i].isEnd())
                enemylist[i].render(enemy1, hdc);
        
        if(!enemylist[numberEnemy - 1].isDead() && !enemylist[numberEnemy - 1].isEnd())
            enemylist[numberEnemy - 1].render(enemy3, hdc);
        
        
        /*for (auto E : enemylist) {
            E.render(enemy1, hdc);
        }*/
        
        

        for (auto T : towerlist) {
            T.render(tower, hdc);
            cbullet b = T.getBullet(); 
            if (b.isActive()) {
                b.render(hbullet, hdc);
            }
        }

        // ve tower trong box
        Graphic::DrawBitmap(tower, Turretinit, hdc);

        // ve tower trong qua trinh di chuyen 
        if (isPicking) {
            Tpicking.render(tower, hdc);
        }

        if (displayYesNoBoard) {
            Graphic::DrawBitmap(boardYesNo, boardYesNoPos, hdc);
            Graphic::DrawBitmap(WantToContinue, WantToContinuePos, hdc);
            Graphic::DrawBitmap(yesBtn, yesBtnPos, hdc);
            Graphic::DrawBitmap(noBtn, noBtnPos, hdc);
        }

    }

    //========================================================================================================================//

    PlayScreen2::PlayScreen2() {
        for (int i = 0; i < 10; i++) {
            cenemy dummy;
            std::vector<POINT> otherPath = epath;

            otherPath[0].x -= i * (rand() % 300 + 100);

            dummy.setPath(otherPath);
            enemylist.push_back(dummy);
        }

        Turretinit = { 50, 565 };
    }

    PlayScreen2::~PlayScreen2() {
        Graphic::ReleaseBitmap(background);
        Graphic::ReleaseBitmap(tower);
        Graphic::ReleaseBitmap(towerInitPlace);
        Graphic::ReleaseBitmap(instructionBoard);

        // Destroy enemy
        Graphic::ReleaseBitmap(enemy1);
        Graphic::ReleaseBitmap(enemy2);
        Graphic::ReleaseBitmap(enemy3);
        
        Graphic::ReleaseBitmap(hamburger);
        Graphic::ReleaseBitmap(play_or_pause);
        Graphic::ReleaseBitmap(hbullet);


        OutputDebugStringA("~PlayScreen2\n");
    }

    void PlayScreen2::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleC = 5;                                   // scale cho input
        float scaleD = 10;                                  // sacle cho text login
        float scaleE = 2;

        background = Graphic::LoadBitmapImage(L"Assets/background/map2.bmp", scale);
        towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
        background = Graphic::LoadBitmapImage(L"Assets/background/map1.bmp", scale);
        towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
        instructionBoard = Graphic::LoadBitmapImage(L"Assets/game/info/board2.png", 1);

        enemy1 = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
        enemy3 = Graphic::LoadBitmapImage(L"Assets/game/enemy3/enemy3-1.png", 2);
        
        hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
        play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);// btnContinue.png
        hbullet = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 1);
        tower = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
    }

    void PlayScreen2::handleInput(HWND hwnd) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;
                // if click the play 
                RECT playRect = {
                    posbuttonplay.x,
                    posbuttonplay.y,
                    posbuttonplay.x + buttonSize.x * 1.8, // Button width
                    posbuttonplay.y + buttonSize.y * 1.8 // Button height
                };
                /*
                    HANDLE CLICK

                    PAUSE GAME || PLAY GAME
                */
                if (PtInRect(&playRect, cursorPos)) {
                    // if click play 

                    for (int i = 0; i < enemylist.size(); i++) {
                        enemylist[i].isMove = !enemylist[i].isMove;
                    }
                }

                // if click in hamburger display board 
                RECT hamburgerRect = {
                    hamburgerPos.x,
                    hamburgerPos.y,
                    hamburgerPos.x + buttonSize.x * 1.5, // Button width
                    hamburgerPos.y + buttonSize.y * 1.5 // Button height
                };
                if (PtInRect(&hamburgerRect, cursorPos)) {
                    displayBoard = !displayBoard;
                }
            }
        }

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            // if hold tower 
            RECT initTowerRect = {
                Turretinit.x,
                Turretinit.y,
                Turretinit.x + towerSize.x * 2, // Button width
                Turretinit.y + towerSize.y * 2 // Button height
            };
            if (PtInRect(&initTowerRect, cursorPos)) {
                isPicking = true;
            }
            else {
                isPicking = false;
            }
        }

        if (isPicking) {
            Tpicking.setLocation(cursorPos);
        }
        else {
            // neu vi tri thoa dieu kien thi them vao list tower
            if (checkValidPos(TcurrentPick)) {
                towerlist.push_back(Tpicking);
            }
        }
    }

    void PlayScreen2::update(float delta) {
        for (auto& enemy : enemylist) {
            if (enemy.isMove && !enemy.isEnd()) {
                enemy.update(delta);
            }
        }

        enemylist.erase(
            std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
                return e.isDead() || e.isEnd();
                }),
            enemylist.end()
        );

        // Towers shoot at the nearest enemy in range and update bullets
        for (auto& tower : towerlist) {
            cenemy* nearestEnemy = nullptr;
            float minDistanceSquared = tower.getRange() * tower.getRange();
            POINT towerPos = tower.getLocation();

            // Xác định bounding box của phạm vi tower
            RECT rangeRect = {
                towerPos.x - static_cast<int>(tower.getRange()),
                towerPos.y - static_cast<int>(tower.getRange()),
                towerPos.x + static_cast<int>(tower.getRange()),
                towerPos.y + static_cast<int>(tower.getRange())
            };

            for (auto& enemy : enemylist) {
                if (!enemy.isMove || enemy.isEnd()) continue;

                POINT enemyPos = enemy.getCurr();
                if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi

                int dx = enemyPos.x - towerPos.x;
                int dy = enemyPos.y - towerPos.y;
                float distanceSquared = static_cast<float>(dx * dx + dy * dy);

                if (distanceSquared < minDistanceSquared) {
                    minDistanceSquared = distanceSquared;
                    nearestEnemy = &enemy;
                }
            }

            if (nearestEnemy) {
                // tower.shootAt(nearestEnemy->getCurr());
                tower.shootAt(nearestEnemy);
                //POINT pos = tower.getBullet().getCurr();
                //if (pos.x)
                //nearestEnemy->takeDamage(tower.getBullet().getDamage());
            }

            tower.updateBullet();
        }
    }

    void PlayScreen2::render(HDC hdc) {
        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
        Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
        Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
        if (displayBoard) {
            Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
        }
        Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);

        for (auto E : enemylist) {
            E.render(enemy1, hdc);
        }

        for (auto T : towerlist) {
            T.render(tower, hdc);
            cbullet b = T.getBullet();
            if (b.isActive()) {
                b.render(hbullet, hdc);
            }
        }

        // ve tower trong box
        Graphic::DrawBitmap(tower, Turretinit, hdc);

        // ve tower trong qua trinh di chuyen 
        if (isPicking) {
            Tpicking.render(tower, hdc);
        }



    }

    //========================================================================================================================//

    PlayScreen3::PlayScreen3() {
        for (int i = 0; i < 10; i++) {
            cenemy dummy;
            std::vector<POINT> otherPath1 = epath1;
            std::vector<POINT> otherPath2 = epath2;

            otherPath1[0].x -= i * (rand() % 300 + 100);
            otherPath2[0].y += i * (rand() % 300 + 100);

            int choice = rand() % 2 + 1; 

            if (choice == 1) {
                dummy.setPath(otherPath1);
            }
            else if (choice == 2) {
                dummy.setPath(otherPath2);
            }

            enemylist.push_back(dummy);
        }

        Turretinit = { 50, 565 };
    }

    PlayScreen3::~PlayScreen3() {
        Graphic::ReleaseBitmap(background);
        Graphic::ReleaseBitmap(tower);
        Graphic::ReleaseBitmap(towerInitPlace);
        Graphic::ReleaseBitmap(instructionBoard);
        
        // Destroy Enemy
        Graphic::ReleaseBitmap(enemy1);
        Graphic::ReleaseBitmap(enemy2);
        Graphic::ReleaseBitmap(enemy3);
        
        //
        Graphic::ReleaseBitmap(hamburger);
        Graphic::ReleaseBitmap(play_or_pause);
        
        Graphic::ReleaseBitmap(hbullet);


        OutputDebugStringA("~PlayScreen2\n");
    }

    void PlayScreen3::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleC = 5;                                   // scale cho input
        float scaleD = 10;                                  // sacle cho text login
        float scaleE = 2;

        background = Graphic::LoadBitmapImage(L"Assets/background/map3.bmp", scale);
        towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
        instructionBoard = Graphic::LoadBitmapImage(L"Assets/game/info/board3.png", 1);
        enemy1 = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
        hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
        play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
        hbullet = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
        tower = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
    }

    void PlayScreen3::handleInput(HWND hwnd) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;
                // if click the play 
                RECT playRect = {
                    posbuttonplay.x,
                    posbuttonplay.y,
                    posbuttonplay.x + buttonSize.x * 1.8, // Button width
                    posbuttonplay.y + buttonSize.y * 1.8 // Button height
                };
                /*
                    HANDLE CLICK

                    PAUSE GAME || PLAY GAME
                */
                if (PtInRect(&playRect, cursorPos)) {
                    // if click play 
                    for (int i = 0; i < enemylist.size(); i++) {
                        enemylist[i].isMove = !enemylist[i].isMove;
                    }
                }

                // if click in hamburger display board 
                RECT hamburgerRect = {
                    hamburgerPos.x,
                    hamburgerPos.y,
                    hamburgerPos.x + buttonSize.x * 1.5, // Button width
                    hamburgerPos.y + buttonSize.y * 1.5 // Button height
                };
                if (PtInRect(&hamburgerRect, cursorPos)) {
                    displayBoard = !displayBoard;
                }
            }
        }

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            // if hold tower 
            RECT initTowerRect = {
                Turretinit.x,
                Turretinit.y,
                Turretinit.x + towerSize.x * 2, // Button width
                Turretinit.y + towerSize.y * 2 // Button height
            };
            if (PtInRect(&initTowerRect, cursorPos)) {
                isPicking = true;
            }
            else {
                isPicking = false;
            }
        }

        if (isPicking) {
            Tpicking.setLocation(cursorPos);
        }
        else {
            // neu vi tri thoa dieu kien thi them vao list tower
            if (checkValidPos(TcurrentPick)) {
                towerlist.push_back(Tpicking);
            }
        }
    }

    void PlayScreen3::update(float delta) {
        for (auto& enemy : enemylist) {
            if (enemy.isMove && !enemy.isEnd()) {
                enemy.update(delta);
            }
        }

        enemylist.erase(
            std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
                return e.isDead() || e.isEnd();
                }),
            enemylist.end()
        );

        // Towers shoot at the nearest enemy in range and update bullets
        for (auto& tower : towerlist) {
            cenemy* nearestEnemy = nullptr;
            float minDistanceSquared = tower.getRange() * tower.getRange();
            POINT towerPos = tower.getLocation();

            // Xác định bounding box của phạm vi tower
            RECT rangeRect = {
                towerPos.x - static_cast<int>(tower.getRange()),
                towerPos.y - static_cast<int>(tower.getRange()),
                towerPos.x + static_cast<int>(tower.getRange()),
                towerPos.y + static_cast<int>(tower.getRange())
            };

            for (auto& enemy : enemylist) {
                if (!enemy.isMove || enemy.isEnd()) continue;

                POINT enemyPos = enemy.getCurr();
                if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi

                int dx = enemyPos.x - towerPos.x;
                int dy = enemyPos.y - towerPos.y;
                float distanceSquared = static_cast<float>(dx * dx + dy * dy);

                if (distanceSquared < minDistanceSquared) {
                    minDistanceSquared = distanceSquared;
                    nearestEnemy = &enemy;
                }
            }

            if (nearestEnemy) {
                // tower.shootAt(nearestEnemy->getCurr());
                tower.shootAt(nearestEnemy);
                //POINT pos = tower.getBullet().getCurr();
                //if (pos.x)
                //nearestEnemy->takeDamage(tower.getBullet().getDamage());
            }

            tower.updateBullet();
        }
    }

    void PlayScreen3::render(HDC hdc) {
        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
        Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
        Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
        if (displayBoard) {
            Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
        }
        Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);

        for (auto E : enemylist) {
            E.render(enemy1, hdc);
        }

        for (auto T : towerlist) {
            T.render(tower, hdc);
            cbullet b = T.getBullet();
            if (b.isActive()) {
                b.render(hbullet, hdc);
            }
        }

        // ve tower trong box
        Graphic::DrawBitmap(tower, Turretinit, hdc);

        // ve tower trong qua trinh di chuyen 
        if (isPicking) {
            Tpicking.render(tower, hdc);
        }



    }

    //========================================================================================================================//

    PlayScreen4::PlayScreen4() {
        for (int i = 0; i < 10; i++) {
            cenemy dummy;
            std::vector<POINT> otherPath1 = epath1;
            std::vector<POINT> otherPath2 = epath2;

            otherPath1[0].x -= i * (rand() % 300 + 100);
            otherPath2[0].y -= i * (rand() % 300 + 100);

            int choice = rand() % 2 + 1;

            if (choice == 1) {
                dummy.setPath(otherPath1);
            }
            else if (choice == 2) {
                dummy.setPath(otherPath2);
            }

            enemylist.push_back(dummy);
        }

        Turretinit = { 50, 565 };
    }

    PlayScreen4::~PlayScreen4() {
        Graphic::ReleaseBitmap(background);
        Graphic::ReleaseBitmap(tower);
        Graphic::ReleaseBitmap(towerInitPlace);
        Graphic::ReleaseBitmap(instructionBoard);

        // Destroy enemy
        Graphic::ReleaseBitmap(enemy1);
        Graphic::ReleaseBitmap(enemy2);
        Graphic::ReleaseBitmap(enemy3);
        
        Graphic::ReleaseBitmap(hamburger);
        Graphic::ReleaseBitmap(play_or_pause);
        Graphic::ReleaseBitmap(hbullet);


        OutputDebugStringA("~PlayScreen2\n");
    }

    void PlayScreen4::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        float scaleC = 5;                                   // scale cho input
        float scaleD = 10;                                  // sacle cho text login
        float scaleE = 2;

        background = Graphic::LoadBitmapImage(L"Assets/background/map4.bmp", scale);
        towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
        instructionBoard = Graphic::LoadBitmapImage(L"Assets/game/info/board4.png", 1);
        enemy1 = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
        hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
        play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
        hbullet = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
        tower = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
    }

    void PlayScreen4::handleInput(HWND hwnd) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;

                OutputDebugStringA((std::to_string(cursorPos.x) + " " + std::to_string(cursorPos.y) + "\n").c_str());
                // if click the play 
                RECT playRect = {
                    posbuttonplay.x,
                    posbuttonplay.y,
                    posbuttonplay.x + buttonSize.x * 1.8, // Button width
                    posbuttonplay.y + buttonSize.y * 1.8 // Button height
                };
                /*
                    HANDLE CLICK

                    PAUSE GAME || PLAY GAME
                */
                if (PtInRect(&playRect, cursorPos)) {
                    // if click play 

                    for (int i = 0; i < enemylist.size(); i++) {
                        enemylist[i].isMove = !enemylist[i].isMove;
                    }
                }

                // if click in hamburger display board 
                RECT hamburgerRect = {
                    hamburgerPos.x,
                    hamburgerPos.y,
                    hamburgerPos.x + buttonSize.x * 1.5, // Button width
                    hamburgerPos.y + buttonSize.y * 1.5 // Button height
                };
                if (PtInRect(&hamburgerRect, cursorPos)) {
                    displayBoard = !displayBoard;
                }
            }
        }

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            // if hold tower 
            RECT initTowerRect = {
                Turretinit.x,
                Turretinit.y,
                Turretinit.x + towerSize.x * 2, // Button width
                Turretinit.y + towerSize.y * 2 // Button height
            };
            if (PtInRect(&initTowerRect, cursorPos)) {
                isPicking = true;
            }
            else {
                isPicking = false;
            }
        }

        if (isPicking) {
            Tpicking.setLocation(cursorPos);
        }
        else {
            // neu vi tri thoa dieu kien thi them vao list tower
            if (checkValidPos(TcurrentPick)) {
                towerlist.push_back(Tpicking);
            }
        }
    }

    void PlayScreen4::update(float delta) {
        for (auto& enemy : enemylist) {
            if (enemy.isMove && !enemy.isEnd()) {
                enemy.update(delta);
            }
        }

        enemylist.erase(
            std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
                return e.isDead() || e.isEnd();
                }),
            enemylist.end()
        );

        // Towers shoot at the nearest enemy in range and update bullets
        for (auto& tower : towerlist) {
            cenemy* nearestEnemy = nullptr;
            float minDistanceSquared = tower.getRange() * tower.getRange();
            POINT towerPos = tower.getLocation();

            // Xác định bounding box của phạm vi tower
            RECT rangeRect = {
                towerPos.x - static_cast<int>(tower.getRange()),
                towerPos.y - static_cast<int>(tower.getRange()),
                towerPos.x + static_cast<int>(tower.getRange()),
                towerPos.y + static_cast<int>(tower.getRange())
            };

            for (auto& enemy : enemylist) {
                if (!enemy.isMove || enemy.isEnd()) continue;

                POINT enemyPos = enemy.getCurr();
                if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi

                int dx = enemyPos.x - towerPos.x;
                int dy = enemyPos.y - towerPos.y;
                float distanceSquared = static_cast<float>(dx * dx + dy * dy);

                if (distanceSquared < minDistanceSquared) {
                    minDistanceSquared = distanceSquared;
                    nearestEnemy = &enemy;
                }
            }

            if (nearestEnemy) {
                // tower.shootAt(nearestEnemy->getCurr());
                tower.shootAt(nearestEnemy);
                //POINT pos = tower.getBullet().getCurr();
                //if (pos.x)
                //nearestEnemy->takeDamage(tower.getBullet().getDamage());
            }

            tower.updateBullet();
        }
    }

    void PlayScreen4::render(HDC hdc) {
        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
        Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
        Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
        if (displayBoard) {
            Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
        }
        Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);

        for (auto E : enemylist) {
            E.render(enemy1, hdc);
        }

        for (auto T : towerlist) {
            
            T.render(tower, hdc);
            cbullet b = T.getBullet();
            if (b.isActive()) {
                b.render(hbullet, hdc);
            }
        }

        // ve tower trong box
        Graphic::DrawBitmap(tower, Turretinit, hdc);

        // ve tower trong qua trinh di chuyen 
        if (isPicking) {
            Tpicking.render(tower, hdc);
        }



    }


}


