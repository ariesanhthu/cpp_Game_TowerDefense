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
        loadContent(1280, 720);
        customfont = Graphic::CreateCustomFont(24, L"pixelFont-7-8x14-sproutLands");

        float scaleX = static_cast<float>(1280) / 395.0f;   // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(720) / 213.0f;    // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        _background = std::make_shared<Item>(L"Assets/background/map4.bmp", scale, 0, 0);
        _catfam = std::make_shared<Item>(L"Assets/decor/nameLogo.png", 2, 0, 0);
        
        _play = std::make_shared<Button>(L"Assets/button/btnPlay.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[0]);
        _cont = std::make_shared<Button>(L"Assets/button/btnContinue.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[1]);
        _lead = std::make_shared<Button>(L"Assets/button/btnLeaderboard.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[2]);
        _sett = std::make_shared<Button>(L"Assets/button/btnSetting.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[3]);
        _exit = std::make_shared<Button>(L"Assets/button/btnExit.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[4]);
        _about = std::make_shared<Button>(L"Assets/button/aboutBtn.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[5]);        
        
        popup = std::make_shared<Popup>(L"Assets/board/board.bmp", 3, initpoint, endpoint);
        
        _map1 = std::make_shared<Option>(L"Assets/map_resize/map1_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsStart[0], optionPositionsEnd[0]);
        _map2 = std::make_shared<Option>(L"Assets/map_resize/map2_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsStart[1], optionPositionsEnd[1]);
        _map3 = std::make_shared<Option>(L"Assets/map_resize/map3_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsStart[2], optionPositionsEnd[2]);
        _map4 = std::make_shared<Option>(L"Assets/map_resize/map4_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsStart[3], optionPositionsEnd[3]);
        
        _login = std::make_shared<Button>(L"Assets/button/LoginBtn.png", L"Assets/button/selectBox2.bmp", 2, loginPosition);
        _inputName = std::make_shared<InputElement>(L"Name", inputNamePosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);
        _inputPassword = std::make_shared<InputElement>(L"Password", inputPasswordPosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);
        
        _register = std::make_shared<Button>(L"Assets/button/LoginBtn.png", L"Assets/button/selectBox2.bmp", 2, registerPosition);
        _inputNameReg = std::make_shared<InputElement>(L"Name", inputNamePosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);
        _inputPasswordReg = std::make_shared<InputElement>(L"Password", inputPasswordPosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);
        
        _gotoPage = std::make_shared<TextElement>(L"Goto Register Form", customfont, RGB(255, 255, 255), linkPos);
    }

    // Destructor
    MainScreen::~MainScreen() {
        // Giải phóng tài nguyên
        DeleteObject(customfont);

        OutputDebugStringA("~MainScreen\n");
    }
    int MainScreen::menu = 0;

    void MainScreen::loadContent(int width, int height) {
        // Tính toán tỉ lệ dựa trên kích thước màn hình
        //float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        //float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        //float scale  = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh     

        buttonPositions = {
            {1280 / 10 * 1, 720 * 7 / 10},   // Play button
            {1280 / 10 * 3, 720 * 7 / 10},   // Pause button
            {1280 / 10 * 5, 720 * 7 / 10},   // Trophy button
            {1280 / 10 * 7, 720 * 7 / 10},   // Settings button
            {1280 / 10 * 9, 720 * 7 / 10},   // Exit button
            {1280 / 10 * 9, 720 * 7 / 100}   // about us
        };
        loginPosition = { 1280 / 10 * 7 + 70, 720 * 7 / 100 };
        initpoint = { 182, 700 };
        endpoint = { 182, 42 };
        optionPositionsStart = {
            {initpoint.x + 80, initpoint.y + 80},
            {initpoint.x + 450, initpoint.y + 80},
            {initpoint.x + 80, initpoint.y + 320},
            {initpoint.x + 450, initpoint.y + 320},
        };
        optionPositionsEnd = {
            {endpoint.x + 80, endpoint.y + 80},
            {endpoint.x + 450, endpoint.y + 80},
            {endpoint.x + 80, endpoint.y + 320},
            {endpoint.x + 450, endpoint.y + 320},
        };
    }

    void MainScreen::handleInput(HWND hwnd) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        // nếu có hiện tượng click chuột
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;

                if (popup->getTriger()) {
                    if (!popup->isHoverInside(cursorPos)) {
                        menu = 0;
                        popup->setTriger(false);
                    }
                }
                else {
                    if (_play && _play->isHoverInside(cursorPos)) {
                        menu = 1;
                        popup->setTriger(true);
                        _map1->setTriger(true);
                        _map2->setTriger(true);
                        _map3->setTriger(true);
                        _map4->setTriger(true);
                    }
                    else if (_cont && _cont->isHoverInside(cursorPos)) {
                        menu = 2;
                        popup->setTriger(true);
                    }
                    else if (_lead && _lead->isHoverInside(cursorPos)) {
                        menu = 3; 
                        popup->setTriger(true);
                    }
                    else if (_sett && _sett->isHoverInside(cursorPos)) {
                        menu = 4; 
                        popup->setTriger(true);
                    }
                    else if (_exit && _exit->isHoverInside(cursorPos)) {
                        menu = 5; 
                        popup->setTriger(true);
                    }
                    else if (_about && _about->isHoverInside(cursorPos)) {
                        menu = 6;
                        popup->setTriger(true);
                    }
                    else if (_login && _login->isHoverInside(cursorPos)) {
                        menu = 101; 
                        popup->setTriger(true);
                    }
                }
            }
        }

        // nếu bật cờ popup thì popup
        if (popup->getTriger() == true) popup->startAnimation();
        else popup->setPosition(initpoint);
        
        if (_map1->getTriger() == true) _map1->startAnimation();
        else _map1->setPosition(optionPositionsStart[0]);

        if (_map2->getTriger() == true) _map2->startAnimation();
        else _map2->setPosition(optionPositionsStart[1]);

        if (_map3->getTriger() == true) _map3->startAnimation();
        else _map3->setPosition(optionPositionsStart[2]);

        if (_map4->getTriger() == true) _map4->startAnimation();
        else _map4->setPosition(optionPositionsStart[3]);

        
        if (menu == 0) {

        }
        else if (menu == 1) {
            if (_map1->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 1, 0);
            }
            else if (_map2->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
            }
        }
        else if (menu == 2) {
            // if click user 

            // loadgame 
        }
        else if (menu == 3) {

        }
        else if (menu == 4) {

        }
        else if (menu == 5) {
            PostQuitMessage(0);
        }
        else if (menu == 6) {

        }
        else if(menu == 101) {
            if (_inputName->isHoverInside(cursorPos)) {
                _inputName->setEdit(true);
            } 

            if (_inputName->isNotHoverInside(cursorPos)) {
                _inputName->setEdit(false);
            }

            if (_inputPassword->isHoverInside(cursorPos)) {
                _inputPassword->setEdit(true);
            }

            if (_inputPassword->isNotHoverInside(cursorPos)) {
                _inputPassword->setEdit(false);
            }

            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                    lastMouseClickTime = now;

                    std::string name = wstringToString(_inputName->getText());
                    for (int i = 0; i < name.length(); i++) {
                        name[i] = tolower(name[i]);
                    }
                    Guess.setName(name);

                    std::string password = wstringToString(_inputPassword->getText());
                    for (int i = 0; i < name.length(); i++) {
                        password[i] = tolower(password[i]);
                    }
                    Guess.setPassword(password);

                    if (Guess.hlogin()) {
                        Guess.authenticated = true;
                        _inputName->setText(L"");
                        _inputPassword->setText(L"");
                        OutputDebugStringW(_inputName->getText().c_str());
                        OutputDebugStringW(_inputPassword->getText().c_str());
                    }
                    else {
                        OutputDebugStringW(L"Fail");
                    }

                }
            }
        }

        if (_inputName->isEdit()) {
            _inputName->handleEdit();
        }

        if (_inputPassword->isEdit()) {
            _inputPassword->handleEdit();
        } 
    }

    // Update logic (nếu có animation hoặc logic khác)
    void MainScreen::update(float delta) {
        if (popup && !popup->isFinished()) {
            popup->update(delta);
        }
        if (_map1 && !_map1->isFinished()) {
            _map1->update(delta);
        }
        if (_map2 && !_map2->isFinished()) {
            _map2->update(delta);
        }
        if (_map3 && !_map3->isFinished()) {
            _map3->update(delta);
        }
        if (_map4 && !_map4->isFinished()) {
            _map4->update(delta);
        }
    }

    void MainScreen::render(HDC hdc) {
        _background->render(hdc);
        _catfam->render(hdc);
        
        _play->render(hdc);
        _cont->render(hdc);
        _lead->render(hdc);
        _sett->render(hdc);
        _exit->render(hdc);
        _about->render(hdc);
        _login->render(hdc);
        popup->render(hdc);
        
        if (menu == 0) {
            
        }
        else if (menu == 1) {
            if (_map1) {
                _map1->render(hdc);
            }
            if (_map2) {
                _map2->render(hdc);
            }
            if (_map3) {
                _map3->render(hdc);
            }
            if (_map4) {
                _map4->render(hdc);
            }
        }
        else if (menu == 2) {

            // render user item

        } 
        else if (menu == 3) {

        }
        else if (menu == 4) {

        }
        else if (menu == 5) {
            
        }
        else if (menu == 6) {
            
        }
        else if (menu == 101) {
            _gotoPage->render(hdc);
            _inputName->render(hdc); 
            _inputPassword->render(hdc);
        }
    }

    //========================================================================================================================//

    //PlayScreen::PlayScreen() {

    //    /*std::vector<saveGame> allgames = getGameList(); 
    //    saveGame loadGame;
    //    for (auto games : allgames) {
    //        if (games.gameId == 5) {
    //            loadGame = games;
    //            break;
    //        }
    //    }

    //    for (int i = 0; i < loadGame.listEnemy.size(); i++) {
    //        cenemy dummy;
    //        
    //        std::vector<POINT> otherPath = loadGame.listEnemy[i].path;
    //        dummy.setPath(otherPath);
    //        dummy.setHealth(loadGame.listEnemy[i].health + 100000);
    //        dummy.setCurr(loadGame.listEnemy[i].currentPosition);
    //        dummy.setIndex(loadGame.listEnemy[i].index);
    //        
    //        enemylist.push_back(dummy);
    //    }

    //    for (int i = 0; i < loadGame.listTower.size(); i++) {
    //        ctower tower; 
    //        tower.setLocation(loadGame.listTower[i].location);
    //        towerlist.push_back(tower);
    //    }*/

    //    for (int i = 0; i < 10; i++) {
    //        cenemy dummy;
    //        std::vector<POINT> otherPath = epath;
    //        
    //        otherPath[0].x -= (i != 9 ? (i * (rand() % 300 + 100)) : 9*500);

    //        dummy.setPath(otherPath);
    //        enemylist.push_back(dummy);
    //    }
    //    enemylist[9].setHealth(450);
    //    
    //    Turretinit = { 50, 565 };
    //}

    //PlayScreen::~PlayScreen() {
    //    Graphic::ReleaseBitmap(background);
    //    Graphic::ReleaseBitmap(tower);
    //    Graphic::ReleaseBitmap(towerInitPlace);
    //    Graphic::ReleaseBitmap(instructionBoard);

    //    //
    //    Graphic::ReleaseBitmap(enemy1);
    //    Graphic::ReleaseBitmap(enemy2);
    //    Graphic::ReleaseBitmap(enemy3);
    //    
    //    Graphic::ReleaseBitmap(hamburger);
    //    Graphic::ReleaseBitmap(play_or_pause);
    //    Graphic::ReleaseBitmap(hbullet);
    //    Graphic::ReleaseBitmap(WantToContinue);
    //    Graphic::ReleaseBitmap(yesBtn);
    //    Graphic::ReleaseBitmap(noBtn);
    //    Graphic::ReleaseBitmap(boardYesNo);


    //    OutputDebugStringA("~PlayScreen\n");
    //}

    //void PlayScreen::loadContent(int width, int height) {
    //    float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
    //    float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
    //    float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
    //    float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
    //    float scaleC = 5;                                   // scale cho input
    //    float scaleD = 10;                                  // sacle cho text login
    //    float scaleE = 2;
    //    
    //    background           = Graphic::LoadBitmapImage(L"Assets/background/map1.bmp", scale);
    //    towerInitPlace       = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
    //    instructionBoard     = Graphic::LoadBitmapImage(L"Assets/game/info/board1.png", 1);
    //    
    //    //ENEMY LOAD
    //    enemy1               = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
    //    enemy3               = Graphic::LoadBitmapImage(L"Assets/game/enemy3/enemy3-1.png", 2);

    //    ///////////////////////////////////////////////////////////////////////////////////////////

    //    hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
    //    play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
    //    
    //    hbullet              = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
    //    
    //    tower                = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
    //    
    //    // route handle
    //    WantToContinue = Graphic::LoadCustomTest("WANTTOCONTINUE", 4);
    //    yesBtn = Graphic::LoadBitmapImage(L"Assets/button/AcceptBtn.png", 4);
    //    noBtn = Graphic::LoadBitmapImage(L"Assets/button/RejectBtn.png", 4);
    //    boardYesNo = Graphic::LoadBitmapImage(L"Assets/board/board.bmp", 1.5);
    //    
    //}

    //void PlayScreen::handleInput(HWND hwnd) {
    //    POINT cursorPos;
    //    GetCursorPos(&cursorPos);
    //    ScreenToClient(GetActiveWindow(), &cursorPos);

    //    // Left mouse button pressed
    //    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
    //        auto now = std::chrono::steady_clock::now();
    //        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
    //            lastMouseClickTime = now;
    //            // if click the play 
    //            RECT playRect = {
    //                posbuttonplay.x,
    //                posbuttonplay.y,
    //                posbuttonplay.x + buttonSize.x * 1.8, // Button width
    //                posbuttonplay.y + buttonSize.y * 1.8 // Button height
    //            };
    //            /*
    //                HANDLE CLICK

    //                PAUSE GAME || PLAY GAME
    //            */
    //            if (PtInRect(&playRect, cursorPos)) {
    //                // if click play 
    //                if (manageFirstTime) {
    //                    //IsPlayGame = true;
    //                    statePlayingGame = PLAY;
    //                    manageFirstTime = false;
    //                    for (int i = 0; i < enemylist.size(); i++) {
    //                        enemylist[i].isMove = true;
    //                    }
    //                }
    //                else {
    //                    if (statePlayingGame == PLAY) {
    //                        displayYesNoBoard = true;
    //                        //IsPlayGame = false;
    //                        statePlayingGame = PAUSE;
    //                        for (int i = 0; i < enemylist.size(); i++) {
    //                            enemylist[i].isMove = false;
    //                        }
    //                    }
    //                }
    //                //}

    //                /*=========================================================================
    //                    PAUSE GAME
    //                  =========================================================================
    //                */
    //                if (displayYesNoBoard) {
    //                    // if yes
    //                    RECT yesRect = {
    //                        yesBtnPos.x,
    //                        yesBtnPos.y,
    //                        yesBtnPos.x + yesnoSize.x * 4, // Button width
    //                        yesBtnPos.y + yesnoSize.y * 4 // Button height
    //                    };

    //                    if (PtInRect(&yesRect, cursorPos)) {
    //                        displayYesNoBoard = false;
    //                        //IsPlayGame = true;
    //                        for (int i = 0; i < enemylist.size(); i++) {
    //                            enemylist[i].isMove = true;
    //                        }

    //                        statePlayingGame = PLAY;
    //                    }

    //                    // if no
    //                    RECT noRect = {
    //                        noBtnPos.x,
    //                        noBtnPos.y,
    //                        noBtnPos.x + yesnoSize.x * 4, // Button width
    //                        noBtnPos.y + yesnoSize.y * 4 // Button height
    //                    };
    //                    if (PtInRect(&noRect, cursorPos)) {

    //                        for (int i = 0; i < enemylist.size(); i++) {
    //                            enemylist[i].isMove = false;
    //                        }

    //                        //std::vector<saveGame> games = getGameList();

    //                        //saveGame newGame;

    //                        //newGame.gameId = 0;
    //                        //for (auto game : games) {
    //                        //    if (newGame.gameId <= game.gameId) {
    //                        //        newGame.gameId++;
    //                        //    }
    //                        //}
    //                        //for (auto enemy : enemylist) {
    //                        //    newGame.listEnemy.push_back({ enemy.getHealth(), enemy.getCurr(), enemy.getPath(), enemy.getIndex() });
    //                        //}
    //                        //for (auto tower : towerlist) {
    //                        //    newGame.listTower.push_back({ tower.getLocation() });
    //                        //}
    //                        //newGame.mapCode = mapCode;
    //                        //newGame.UserId = Guess.getId();


    //                        ///*vector<int> gameID = Guess.getListGame();
    //                        //gameID.push_back(newGame.gameId);
    //                        //Guess.setListGame(gameID);*/
    //                        ////OutputDebugStringA(std::to_string(newGame.UserId).c_str());

    //                        //appendGameToFile(newGame);


    //                        PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
    //                    }
    //                }

    //                // if click in hamburger display board 
    //                RECT hamburgerRect = {
    //                    hamburgerPos.x,
    //                    hamburgerPos.y,
    //                    hamburgerPos.x + buttonSize.x * 1.5, // Button width
    //                    hamburgerPos.y + buttonSize.y * 1.5 // Button height
    //                };
    //                if (PtInRect(&hamburgerRect, cursorPos)) {
    //                    displayBoard = !displayBoard;
    //                }


    //                /*
    //                    CHECK END GAME
    //                */
    //                // HANDLE INPUT BOARD WIN GAME
    //                if (statePlayingGame == WIN)
    //                {
    //                    // if yes
    //                    RECT yesRect = {
    //                        yesBtnPos.x,
    //                        yesBtnPos.y,
    //                        yesBtnPos.x + yesnoSize.x * 4, // Button width
    //                        yesBtnPos.y + yesnoSize.y * 4 // Button height
    //                    };

    //                    // GO TO THE NEXT LEVEL 
    //                    if (PtInRect(&yesRect, cursorPos)) {
    //                        PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
    //                    }

    //                    // if no
    //                    RECT noRect = {
    //                        noBtnPos.x,
    //                        noBtnPos.y,
    //                        noBtnPos.x + yesnoSize.x * 4, // Button width
    //                        noBtnPos.y + yesnoSize.y * 4 // Button height
    //                    };

    //                    // back to MAIN SCREEN
    //                    if (PtInRect(&noRect, cursorPos)) {
    //                        PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
    //                    }
    //                }
    //                else
    //                    // HANDLE INPUT BOARD LOSE GAME
    //                    if (statePlayingGame == LOSE)
    //                    {
    //                        // if yes
    //                        RECT yesRect = {
    //                            yesBtnPos.x,
    //                            yesBtnPos.y,
    //                            yesBtnPos.x + yesnoSize.x * 4, // Button width
    //                            yesBtnPos.y + yesnoSize.y * 4 // Button height
    //                        };
    //                    }
    //            }
    //        }

    //        bool mouseClicked = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

    //        static bool mouseReleased = true; // Trạng thái chuột đã nhả (tránh lặp sự kiện)
    //        if (mouseClicked && mouseReleased) {
    //            mouseReleased = false; // Đánh dấu chuột đã bấm

    //            if (!isPicking) {
    //                // Người dùng chưa "nhặt tháp", bắt đầu "nhặt tháp"
    //                RECT initTowerRect = {
    //                    Turretinit.x,
    //                    Turretinit.y,
    //                    Turretinit.x + towerSize.x * 2, // Chiều rộng nút
    //                    Turretinit.y + towerSize.y * 2  // Chiều cao nút
    //                };

    //                if (PtInRect(&initTowerRect, cursorPos)) {
    //                    isPicking = true;                // Chuyển sang trạng thái "nhặt tháp"
    //                    Tpicking.setLocation(cursorPos); // Đặt vị trí ban đầu theo con trỏ chuột
    //                }
    //                RECT yesRect = {
    //                            yesBtnPos.x,
    //                            yesBtnPos.y,
    //                            yesBtnPos.x + yesnoSize.x * 4, // Button width
    //                            yesBtnPos.y + yesnoSize.y * 4 // Button height
    //                };
    //                // GO TO THE NEXT LEVEL 
    //                if (PtInRect(&yesRect, cursorPos)) {
    //                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 1, 0);
    //                }

    //                // if no
    //                RECT noRect = {
    //                    noBtnPos.x,
    //                    noBtnPos.y,
    //                    noBtnPos.x + yesnoSize.x * 4, // Button width
    //                    noBtnPos.y + yesnoSize.y * 4 // Button height
    //                };

    //                // back to MAIN SCREEN
    //                if (PtInRect(&noRect, cursorPos)) {
    //                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
    //                }

    //            }

    //        }

    //        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
    //            // if hold tower 
    //            RECT initTowerRect = {
    //                Turretinit.x,
    //                Turretinit.y,
    //                Turretinit.x + towerSize.x * 2, // Button width
    //                Turretinit.y + towerSize.y * 2 // Button height
    //            };
    //            if (PtInRect(&initTowerRect, cursorPos)) {
    //                isPicking = true;
    //            }
    //            else {
    //                if (checkValidPos(Tpicking.getLocation())) {
    //                    towerlist.push_back(Tpicking); // Thêm vào danh sách nếu hợp lệ
    //                    isPicking = false;            // Kết thúc trạng thái "nhặt tháp"
    //                }
    //            }
    //        }

    //        if (!mouseClicked) {
    //            mouseReleased = true; // Đánh dấu chuột đã nhả
    //        }

    //        // Nếu đang "nhặt tháp", cập nhật vị trí theo con trỏ chuột
    //        if (isPicking) {
    //            Tpicking.setLocation(cursorPos);
    //        }

    //    }
    //}

    //void PlayScreen::update(float delta) {
    //    
    //    // KIỂM TRA TRẠNG THÁI GAME
    //    // CHỈ CẬP NHẬT TRẠNG THÁI MỚI NẾU STATE == PLAY
    //    if (statePlayingGame != PLAY) return;
    //    
    //    // CẬP NHẬT TRẠNG THÁI ENEMY

    //    for (auto& enemy : enemylist) {
    //        if (enemy.isMove && !enemy.isEnd()) {
    //            enemy.update(delta);
    //        }
    //    }

    //    // update state playing game (win,lose,countheart)
    //    //
    //    int countDead = 0;
    //    for (auto& enemy : enemylist) {
    //        if (enemy.isEnd()) {
    //            countHeart++;
    //        }
    //        if (enemy.isDead()) countDead++;
    //    }

    //    if (countDead + countHeart >= 10 && countHeart == 0)
    //    {
    //        statePlayingGame = WIN;
    //        return;
    //    }
    //    else countDead = 0;

    //    if (countHeart >= 1)
    //    {
    //        statePlayingGame = LOSE;
    //        return;
    //    }
    //    else countHeart = 0;
    //    //======================================================================
    //    
    //    /*enemylist.erase(
    //        std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
    //            return e.isDead() || e.isEnd();  
    //            }),
    //        enemylist.end()
    //    );*/

    //    // Towers shoot at the nearest enemy in range and update bullets
    //    for (auto& tower : towerlist) {
    //        cenemy* nearestEnemy = nullptr;
    //        float minDistanceSquared = tower.getRange() * tower.getRange();
    //        POINT towerPos = tower.getLocation();

    //        // Xác định bounding box của phạm vi tower
    //        RECT rangeRect = {
    //            towerPos.x - static_cast<int>(tower.getRange()),
    //            towerPos.y - static_cast<int>(tower.getRange()),
    //            towerPos.x + static_cast<int>(tower.getRange()),
    //            towerPos.y + static_cast<int>(tower.getRange())
    //        };

    //        for (auto& enemy : enemylist) {
    //            if (!enemy.isMove || enemy.isEnd()) continue;

    //            POINT enemyPos = enemy.getCurr();
    //            if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi

    //            int dx = enemyPos.x - towerPos.x;
    //            int dy = enemyPos.y - towerPos.y;
    //            float distanceSquared = static_cast<float>(dx * dx + dy * dy);

    //            if (distanceSquared < minDistanceSquared) {
    //                minDistanceSquared = distanceSquared;
    //                nearestEnemy = &enemy;
    //            }
    //        }

    //        if (nearestEnemy) {
    //            tower.shootAt(nearestEnemy);   
    //        }
    //        if (nearestEnemy) {
    //            int x = nearestEnemy->getHealth();
    //            if (x < 0) {
    //                guess.setPoint(guess.getPoint() + 10);
    //            }
    //        }

    //        tower.updateBullet();
    //    }
    //
    //
    //}

    //void PlayScreen::render(HDC hdc) {

    //    Graphic::DrawBitmap(background, { 0, 0 }, hdc);
    //    Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
    //    Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);

    //    Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);


    //    int numberEnemy = enemylist.size();

    //    for (int i = 0; i < numberEnemy - 1; i++)
    //        if (!enemylist[i].isDead() && !enemylist[i].isEnd())
    //            enemylist[i].render(enemy1, hdc);

    //    if (!enemylist[numberEnemy - 1].isDead() && !enemylist[numberEnemy - 1].isEnd())
    //        enemylist[numberEnemy - 1].render(enemy3, hdc);


    //    /*for (auto E : enemylist) {
    //        E.render(enemy1, hdc);
    //    }*/



    //    for (auto T : towerlist) {
    //        T.render(tower, hdc);

    //        cbullet b = T.getBullet();

    //        if (b.isActive()) {
    //            b.render(hbullet, hdc);
    //        }
    //    }

    //    // ve tower trong box
    //    Graphic::DrawBitmap(tower, Turretinit, hdc);

    //    // ve tower trong qua trinh di chuyen 
    //    if (isPicking) {
    //        Tpicking.render(tower, hdc);
    //    }

    //    // BẢNG HƯỚNG DẪN
    //    if (displayBoard) {
    //        Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
    //    }
    //    if (displayYesNoBoard) {
    //        Graphic::DrawBitmap(boardYesNo, boardYesNoPos, hdc);
    //        Graphic::DrawBitmap(WantToContinue, WantToContinuePos, hdc);
    //        Graphic::DrawBitmap(yesBtn, yesBtnPos, hdc);
    //        Graphic::DrawBitmap(noBtn, noBtnPos, hdc);
    //    }


    //    //----------------------------------------------
    //    // DRAW BOARD END GAME
    //    //----------------------------------------------
    //    if (statePlayingGame == LOSE)
    //    {
    //        Graphic::DrawBitmap(Graphic::LoadBitmapImage(L"Assets/game/info/BoardLose.png", 1.2), { 280, 60 }, hdc);
    //        Graphic::DrawBitmap(yesBtn, yesBtnPos, hdc);
    //        Graphic::DrawBitmap(noBtn, noBtnPos, hdc);
    //    }
    //    else
    //        if (statePlayingGame == WIN)
    //        {
    //            Graphic::DrawBitmap(Graphic::LoadBitmapImage(L"Assets/game/info/BoardWin.png", 1.2), { 280, 60 }, hdc);
    //            Graphic::DrawBitmap(yesBtn, yesBtnPos, hdc);
    //            Graphic::DrawBitmap(noBtn, noBtnPos, hdc);
    //        }
    //}
    
    //========================================================================================================================//

    PlayScreen2::PlayScreen2() {
        loadContent(1280, 720);

        float scaleX = static_cast<float>(1280) / 395.0f;   // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(720) / 213.0f;    // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        vector<vector<cpoint>> path;
        path.push_back(epath);

        manager.setup(path);

        int nofpath = 1;
        for (int i = 0; i < 10; i++) {
            manager.enemyManager.addEnemy(EnemyFactory::createEnemy(1, rand() % nofpath));
        }
        vector<int> mapSetup{3,5,4,1};
        manager.enemyManager.setup(mapSetup);

        //Turretinit = { 50, 565 };

        _background = std::make_shared<Item>(L"Assets/background/map2.bmp", scale, 0, 0);
        _instructionboard = std::make_shared<Item>(L"Assets/game/info/board2.png", 1.0f, instructionPos);
        _towerInitPlace = std::make_shared<Item>(L"Assets/game/BoardSetupTower.png", 1.5f, towerInitPos);
        _hamburger = std::make_shared<Button>(L"Assets/button/aboutBtn.png", L"Assets/button/selectbox.bmp", 2, hamburgerPos);
        _playOrPause = std::make_shared<Button>(L"Assets/button/btnPlay.png", L"Assets/button/selectbox.bmp", 2, posbuttonplay);

        _yesnoBoard = std::make_shared<Item>(L"Assets/board/board.bmp", 1.5, boardYesNoPos);
        _yesBtn = std::make_shared<Button>(L"Assets/button/AcceptBtn.png", L"Assets/button/selectbox.bmp", 3, yesBtnPos);
        _noBtn = std::make_shared<Button>(L"Assets/button/RejectBtn.png", L"Assets/button/selectbox.bmp", 3, noBtnPos);
    }

    PlayScreen2::~PlayScreen2() {
        //Graphic::ReleaseBitmap(background);
        //Graphic::ReleaseBitmap(tower);
        //Graphic::ReleaseBitmap(towerInitPlace);
        //Graphic::ReleaseBitmap(instructionBoard);

        //// Destroy enemy
        //Graphic::ReleaseBitmap(enemy1);
        //Graphic::ReleaseBitmap(enemy2);
        //Graphic::ReleaseBitmap(enemy3);
        //
        //Graphic::ReleaseBitmap(hamburger);
        //Graphic::ReleaseBitmap(play_or_pause);
        //Graphic::ReleaseBitmap(hbullet);


        OutputDebugStringA("~PlayScreen2\n");
    }

    void PlayScreen2::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        //float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
        //float scaleC = 5;                                   // scale cho input
        //float scaleD = 10;                                  // sacle cho text login
        //float scaleE = 2;

        /*background = Graphic::LoadBitmapImage(L"Assets/background/map2.bmp", scale);
        towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
        instructionBoard = Graphic::LoadBitmapImage(L"Assets/game/info/board2.png", 1);

        enemy1 = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
        enemy3 = Graphic::LoadBitmapImage(L"Assets/game/enemy3/enemy3-1.png", 2);
        
        hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
        play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
        hbullet = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 1);
        tower = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);*/

    }

    void PlayScreen2::handleInput(HWND hwnd) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);

        //if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
        //    auto now = std::chrono::steady_clock::now();
        //    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
        //        lastMouseClickTime = now;
        //        // if click the play 
        //        RECT playRect = {
        //            posbuttonplay.x,
        //            posbuttonplay.y,
        //            posbuttonplay.x + buttonSize.x * 1.8, // Button width
        //            posbuttonplay.y + buttonSize.y * 1.8 // Button height
        //        };
        //        /*
        //            HANDLE CLICK

        //            PAUSE GAME || PLAY GAME
        //        */
        //        if (PtInRect(&playRect, cursorPos)) {
        //            // if click play 

        //            for (int i = 0; i < enemylist.size(); i++) {
        //                enemylist[i].isMove = !enemylist[i].isMove;
        //            }
        //        }

        //        // if click in hamburger display board 
        //        RECT hamburgerRect = {
        //            hamburgerPos.x,
        //            hamburgerPos.y,
        //            hamburgerPos.x + buttonSize.x * 1.5, // Button width
        //            hamburgerPos.y + buttonSize.y * 1.5 // Button height
        //        };
        //        if (PtInRect(&hamburgerRect, cursorPos)) {
        //            displayBoard = !displayBoard;
        //        }
        //    }
        //}

        //if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        //    // if hold tower 
        //    RECT initTowerRect = {
        //        Turretinit.x,
        //        Turretinit.y,
        //        Turretinit.x + towerSize.x * 2, // Button width
        //        Turretinit.y + towerSize.y * 2 // Button height
        //    };
        //    if (PtInRect(&initTowerRect, cursorPos)) {
        //        isPicking = true;
        //    }
        //    else {
        //        isPicking = false;
        //    }
        //}

        //if (isPicking) {
        //    Tpicking.setLocation(cursorPos);
        //}
        //else {
        //    // neu vi tri thoa dieu kien thi them vao list tower
        //    if (checkValidPos(TcurrentPick)) {
        //        //towerlist.push_back(Tpicking);
        //        cpoint pos = { TcurrentPick.x, TcurrentPick.y };
        //        manager.towerManager.addTower(TowerFactory::createTower(1, pos));
        //    }
        //}

        if (_playOrPause->isClicked(cursorPos)) {
            if (manageFirstTime) {

                statePlayingGame = PLAY;

                manageFirstTime = false;
            }
            //else {
            //    _yesnoBoard->setTriger(true);
            //}
        }

        if (_hamburger->isClicked(cursorPos)) {
            bool t = _instructionboard->getTriger();
            _instructionboard->setTriger(!t);
        }
    }

    void PlayScreen2::update(float delta) {
        //if (statePlayingGame != PLAY) return;

        //if (manager.gameStatus == WIN) {
        //    statePlayingGame = WIN;
        //}
        //else if (manager.gameStatus == LOSE) {
        //    statePlayingGame = LOSE;
        //}
        //else if (manager.gameStatus == PLAY) {
        //    manager.update(delta);
        //    statePlayingGame = PLAY;
        //}
        //else if (manager.gameStatus == PAUSE) {
        //    // ........
        //}

        OutputDebugStringA("11111111111111111\n");
        manager.update(delta);
    }

    void PlayScreen2::render(HDC hdc) {
        //Graphic::DrawBitmap(background, { 0, 0 }, hdc);
        //Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
        //Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
        //if (displayBoard) {
        //    Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
        //}
        //Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);

        //for (auto E : enemylist) {
        //    E.render(enemy1, hdc);
        //}

        //for (auto T : towerlist) {
        //    T.render(tower, hdc);
        //    cbullet b = T.getBullet();
        //    if (b.isActive()) {
        //        b.render(hbullet, hdc);
        //    }
        //}

        //// ve tower trong box
        //Graphic::DrawBitmap(tower, Turretinit, hdc);

        //// ve tower trong qua trinh di chuyen 
        //if (isPicking) {
        //    Tpicking.render(tower, hdc);
        //}


        _background->render(hdc);
        _hamburger->render(hdc);
        _towerInitPlace->render(hdc);

        if (_instructionboard->getTriger()) {
            _instructionboard->render(hdc);
        }

        if (_yesnoBoard->getTriger()) {
            _yesnoBoard->render(hdc);
            _noBtn->render(hdc);
            _yesBtn->render(hdc);
        }
        
        // in hết        
        OutputDebugStringA("AAAAAAAAAAAAAAAAAa\n");
        manager.render(hdc);

        
        _playOrPause->render(hdc);

    }

    //========================================================================================================================//

    //PlayScreen3::PlayScreen3() {
    //    for (int i = 0; i < 10; i++) {
    //        cenemy dummy;
    //        std::vector<POINT> otherPath1 = epath1;
    //        std::vector<POINT> otherPath2 = epath2;

    //        otherPath1[0].x -= i * (rand() % 300 + 100);
    //        otherPath2[0].y += i * (rand() % 300 + 100);

    //        int choice = rand() % 2 + 1; 

    //        if (choice == 1) {
    //            dummy.setPath(otherPath1);
    //        }
    //        else if (choice == 2) {
    //            dummy.setPath(otherPath2);
    //        }

    //        enemylist.push_back(dummy);
    //    }

    //    Turretinit = { 50, 565 };
    //}

    //PlayScreen3::~PlayScreen3() {
    //    Graphic::ReleaseBitmap(background);
    //    Graphic::ReleaseBitmap(tower);
    //    Graphic::ReleaseBitmap(towerInitPlace);
    //    Graphic::ReleaseBitmap(instructionBoard);
    //    
    //    // Destroy Enemy
    //    Graphic::ReleaseBitmap(enemy1);
    //    Graphic::ReleaseBitmap(enemy2);
    //    Graphic::ReleaseBitmap(enemy3);
    //    
    //    //
    //    Graphic::ReleaseBitmap(hamburger);
    //    Graphic::ReleaseBitmap(play_or_pause);
    //    
    //    Graphic::ReleaseBitmap(hbullet);


    //    OutputDebugStringA("~PlayScreen2\n");
    //}

    //void PlayScreen3::loadContent(int width, int height) {
    //    float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
    //    float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
    //    float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
    //    float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
    //    float scaleC = 5;                                   // scale cho input
    //    float scaleD = 10;                                  // sacle cho text login
    //    float scaleE = 2;

    //    background = Graphic::LoadBitmapImage(L"Assets/background/map3.bmp", scale);
    //    towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
    //    instructionBoard = Graphic::LoadBitmapImage(L"Assets/game/info/board3.png", 1);
    //    enemy1 = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
    //    hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
    //    play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
    //    hbullet = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
    //    tower = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
    //}

    //void PlayScreen3::handleInput(HWND hwnd) {
    //    POINT cursorPos;
    //    GetCursorPos(&cursorPos);
    //    ScreenToClient(GetActiveWindow(), &cursorPos);

    //    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
    //        auto now = std::chrono::steady_clock::now();
    //        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
    //            lastMouseClickTime = now;
    //            // if click the play 
    //            RECT playRect = {
    //                posbuttonplay.x,
    //                posbuttonplay.y,
    //                posbuttonplay.x + buttonSize.x * 1.8, // Button width
    //                posbuttonplay.y + buttonSize.y * 1.8 // Button height
    //            };
    //            /*
    //                HANDLE CLICK

    //                PAUSE GAME || PLAY GAME
    //            */
    //            if (PtInRect(&playRect, cursorPos)) {
    //                // if click play 
    //                for (int i = 0; i < enemylist.size(); i++) {
    //                    enemylist[i].isMove = !enemylist[i].isMove;
    //                }
    //            }

    //            // if click in hamburger display board 
    //            RECT hamburgerRect = {
    //                hamburgerPos.x,
    //                hamburgerPos.y,
    //                hamburgerPos.x + buttonSize.x * 1.5, // Button width
    //                hamburgerPos.y + buttonSize.y * 1.5 // Button height
    //            };
    //            if (PtInRect(&hamburgerRect, cursorPos)) {
    //                displayBoard = !displayBoard;
    //            }
    //        }
    //    }

    //    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
    //        // if hold tower 
    //        RECT initTowerRect = {
    //            Turretinit.x,
    //            Turretinit.y,
    //            Turretinit.x + towerSize.x * 2, // Button width
    //            Turretinit.y + towerSize.y * 2 // Button height
    //        };
    //        if (PtInRect(&initTowerRect, cursorPos)) {
    //            isPicking = true;
    //        }
    //        else {
    //            isPicking = false;
    //        }
    //    }

    //    if (isPicking) {
    //        Tpicking.setLocation(cursorPos);
    //    }
    //    else {
    //        // neu vi tri thoa dieu kien thi them vao list tower
    //        if (checkValidPos(TcurrentPick)) {
    //            towerlist.push_back(Tpicking);
    //        }
    //    }
    //}

    //void PlayScreen3::update(float delta) {
    //    for (auto& enemy : enemylist) {
    //        if (enemy.isMove && !enemy.isEnd()) {
    //            enemy.update(delta);
    //        }
    //    }

    //    enemylist.erase(
    //        std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
    //            return e.isDead() || e.isEnd();
    //            }),
    //        enemylist.end()
    //    );

    //    // Towers shoot at the nearest enemy in range and update bullets
    //    for (auto& tower : towerlist) {
    //        cenemy* nearestEnemy = nullptr;
    //        float minDistanceSquared = tower.getRange() * tower.getRange();
    //        POINT towerPos = tower.getLocation();

    //        // Xác định bounding box của phạm vi tower
    //        RECT rangeRect = {
    //            towerPos.x - static_cast<int>(tower.getRange()),
    //            towerPos.y - static_cast<int>(tower.getRange()),
    //            towerPos.x + static_cast<int>(tower.getRange()),
    //            towerPos.y + static_cast<int>(tower.getRange())
    //        };

    //        for (auto& enemy : enemylist) {
    //            if (!enemy.isMove || enemy.isEnd()) continue;

    //            POINT enemyPos = enemy.getCurr();
    //            if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi

    //            int dx = enemyPos.x - towerPos.x;
    //            int dy = enemyPos.y - towerPos.y;
    //            float distanceSquared = static_cast<float>(dx * dx + dy * dy);

    //            if (distanceSquared < minDistanceSquared) {
    //                minDistanceSquared = distanceSquared;
    //                nearestEnemy = &enemy;
    //            }
    //        }

    //        if (nearestEnemy) {
    //            // tower.shootAt(nearestEnemy->getCurr());
    //            tower.shootAt(nearestEnemy);
    //            //POINT pos = tower.getBullet().getCurr();
    //            //if (pos.x)
    //            //nearestEnemy->takeDamage(tower.getBullet().getDamage());
    //        }

    //        tower.updateBullet();
    //    }
    //}

    //void PlayScreen3::render(HDC hdc) {
    //    Graphic::DrawBitmap(background, { 0, 0 }, hdc);
    //    Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
    //    Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
    //    if (displayBoard) {
    //        Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
    //    }
    //    Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);

    //    for (auto E : enemylist) {
    //        E.render(enemy1, hdc);
    //    }

    //    for (auto T : towerlist) {
    //        T.render(tower, hdc);
    //        cbullet b = T.getBullet();
    //        if (b.isActive()) {
    //            b.render(hbullet, hdc);
    //        }
    //    }

    //    // ve tower trong box
    //    Graphic::DrawBitmap(tower, Turretinit, hdc);

    //    // ve tower trong qua trinh di chuyen 
    //    if (isPicking) {
    //        Tpicking.render(tower, hdc);
    //    }



    //}

    //========================================================================================================================//

    //PlayScreen4::PlayScreen4() {
    //    for (int i = 0; i < 10; i++) {
    //        cenemy dummy;
    //        std::vector<POINT> otherPath1 = epath1;
    //        std::vector<POINT> otherPath2 = epath2;

    //        otherPath1[0].x -= i * (rand() % 300 + 100);
    //        otherPath2[0].y -= i * (rand() % 300 + 100);

    //        int choice = rand() % 2 + 1;

    //        if (choice == 1) {
    //            dummy.setPath(otherPath1);
    //        }
    //        else if (choice == 2) {
    //            dummy.setPath(otherPath2);
    //        }

    //        enemylist.push_back(dummy);
    //    }

    //    Turretinit = { 50, 565 };
    //}

    //PlayScreen4::~PlayScreen4() {
    //    Graphic::ReleaseBitmap(background);
    //    Graphic::ReleaseBitmap(tower);
    //    Graphic::ReleaseBitmap(towerInitPlace);
    //    Graphic::ReleaseBitmap(instructionBoard);

    //    // Destroy enemy
    //    Graphic::ReleaseBitmap(enemy1);
    //    Graphic::ReleaseBitmap(enemy2);
    //    Graphic::ReleaseBitmap(enemy3);
    //    
    //    Graphic::ReleaseBitmap(hamburger);
    //    Graphic::ReleaseBitmap(play_or_pause);
    //    Graphic::ReleaseBitmap(hbullet);


    //    OutputDebugStringA("~PlayScreen2\n");
    //}

    //void PlayScreen4::loadContent(int width, int height) {
    //    float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
    //    float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
    //    float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
    //    float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
    //    float scaleC = 5;                                   // scale cho input
    //    float scaleD = 10;                                  // sacle cho text login
    //    float scaleE = 2;

    //    background = Graphic::LoadBitmapImage(L"Assets/background/map4.bmp", scale);
    //    towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
    //    instructionBoard = Graphic::LoadBitmapImage(L"Assets/game/info/board4.png", 1);
    //    enemy1 = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
    //    hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
    //    play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
    //    hbullet = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
    //    tower = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
    //}

    //void PlayScreen4::handleInput(HWND hwnd) {
    //    POINT cursorPos;
    //    GetCursorPos(&cursorPos);
    //    ScreenToClient(GetActiveWindow(), &cursorPos);

    //    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
    //        auto now = std::chrono::steady_clock::now();
    //        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
    //            lastMouseClickTime = now;

    //            OutputDebugStringA((std::to_string(cursorPos.x) + " " + std::to_string(cursorPos.y) + "\n").c_str());
    //            // if click the play 
    //            RECT playRect = {
    //                posbuttonplay.x,
    //                posbuttonplay.y,
    //                posbuttonplay.x + buttonSize.x * 1.8, // Button width
    //                posbuttonplay.y + buttonSize.y * 1.8 // Button height
    //            };
    //            /*
    //                HANDLE CLICK

    //                PAUSE GAME || PLAY GAME
    //            */
    //            if (PtInRect(&playRect, cursorPos)) {
    //                // if click play 

    //                for (int i = 0; i < enemylist.size(); i++) {
    //                    enemylist[i].isMove = !enemylist[i].isMove;
    //                }
    //            }

    //            // if click in hamburger display board 
    //            RECT hamburgerRect = {
    //                hamburgerPos.x,
    //                hamburgerPos.y,
    //                hamburgerPos.x + buttonSize.x * 1.5, // Button width
    //                hamburgerPos.y + buttonSize.y * 1.5 // Button height
    //            };
    //            if (PtInRect(&hamburgerRect, cursorPos)) {
    //                displayBoard = !displayBoard;
    //            }
    //        }
    //    }

    //    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
    //        // if hold tower 
    //        RECT initTowerRect = {
    //            Turretinit.x,
    //            Turretinit.y,
    //            Turretinit.x + towerSize.x * 2, // Button width
    //            Turretinit.y + towerSize.y * 2 // Button height
    //        };
    //        if (PtInRect(&initTowerRect, cursorPos)) {
    //            isPicking = true;
    //        }
    //        else {
    //            isPicking = false;
    //        }
    //    }

    //    if (isPicking) {
    //        Tpicking.setLocation(cursorPos);
    //    }
    //    else {
    //        // neu vi tri thoa dieu kien thi them vao list tower
    //        if (checkValidPos(TcurrentPick)) {
    //            towerlist.push_back(Tpicking);
    //        }
    //    }
    //}

    //void PlayScreen4::update(float delta) {
    //    for (auto& enemy : enemylist) {
    //        if (enemy.isMove && !enemy.isEnd()) {
    //            enemy.update(delta);
    //        }
    //    }

    //    enemylist.erase(
    //        std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
    //            return e.isDead() || e.isEnd();
    //            }),
    //        enemylist.end()
    //    );

    //    // Towers shoot at the nearest enemy in range and update bullets
    //    for (auto& tower : towerlist) {
    //        cenemy* nearestEnemy = nullptr;
    //        float minDistanceSquared = tower.getRange() * tower.getRange();
    //        POINT towerPos = tower.getLocation();

    //        // Xác định bounding box của phạm vi tower
    //        RECT rangeRect = {
    //            towerPos.x - static_cast<int>(tower.getRange()),
    //            towerPos.y - static_cast<int>(tower.getRange()),
    //            towerPos.x + static_cast<int>(tower.getRange()),
    //            towerPos.y + static_cast<int>(tower.getRange())
    //        };

    //        for (auto& enemy : enemylist) {
    //            if (!enemy.isMove || enemy.isEnd()) continue;

    //            POINT enemyPos = enemy.getCurr();
    //            if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi

    //            int dx = enemyPos.x - towerPos.x;
    //            int dy = enemyPos.y - towerPos.y;
    //            float distanceSquared = static_cast<float>(dx * dx + dy * dy);

    //            if (distanceSquared < minDistanceSquared) {
    //                minDistanceSquared = distanceSquared;
    //                nearestEnemy = &enemy;
    //            }
    //        }

    //        if (nearestEnemy) {
    //            // tower.shootAt(nearestEnemy->getCurr());
    //            tower.shootAt(nearestEnemy);
    //            //POINT pos = tower.getBullet().getCurr();
    //            //if (pos.x)
    //            //nearestEnemy->takeDamage(tower.getBullet().getDamage());
    //        }

    //        tower.updateBullet();
    //    }
    //}

    //void PlayScreen4::render(HDC hdc) {
    //    Graphic::DrawBitmap(background, { 0, 0 }, hdc);
    //    Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
    //    Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
    //    if (displayBoard) {
    //        Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
    //    }
    //    Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);

    //    for (auto E : enemylist) {
    //        E.render(enemy1, hdc);
    //    }

    //    for (auto T : towerlist) {
    //        
    //        T.render(tower, hdc);
    //        cbullet b = T.getBullet();
    //        if (b.isActive()) {
    //            b.render(hbullet, hdc);
    //        }
    //    }

    //    // ve tower trong box
    //    Graphic::DrawBitmap(tower, Turretinit, hdc);

    //    // ve tower trong qua trinh di chuyen 
    //    if (isPicking) {
    //        Tpicking.render(tower, hdc);
    //    }



    //}
}


