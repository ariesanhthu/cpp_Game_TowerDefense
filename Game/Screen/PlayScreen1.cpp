//#include "PlayScreen1.h"
//using namespace std;
//
//namespace towerdefense
//{
//    //========================================================================================================================//
//
//    PlayScreen1::PlayScreen1() {
//
//        /*std::vector<saveGame> allgames = getGameList(); 
//        saveGame loadGame;
//        for (auto games : allgames) {
//            if (games.gameId == 5) {
//                loadGame = games;
//                break;
//            }
//        }
//
//        for (int i = 0; i < loadGame.listEnemy.size(); i++) {
//            cenemy dummy;
//            
//            std::vector<POINT> otherPath = loadGame.listEnemy[i].path;
//            dummy.setPath(otherPath);
//            dummy.setHealth(loadGame.listEnemy[i].health + 100000);
//            dummy.setCurr(loadGame.listEnemy[i].currentPosition);
//            dummy.setIndex(loadGame.listEnemy[i].index);
//            
//            enemylist.push_back(dummy);
//        }
//
//        for (int i = 0; i < loadGame.listTower.size(); i++) {
//            ctower tower; 
//            tower.setLocation(loadGame.listTower[i].location);
//            towerlist.push_back(tower);
//        }*/
//
//        for (int i = 0; i < 10; i++) {
//            cenemy dummy;
//            std::vector<POINT> otherPath = epath;
//            
//            otherPath[0].x -= (i != 9 ? (i * (rand() % 300 + 100)) : 9*500);
//
//            dummy.setPath(otherPath);
//            enemylist.push_back(dummy);
//        }
//        enemylist[9].setHealth(450);
//        
//        Turretinit = { 50, 565 };
//    }
//
//    PlayScreen1::~PlayScreen1() {
//        Graphic::ReleaseBitmap(background);
//        Graphic::ReleaseBitmap(tower);
//        Graphic::ReleaseBitmap(towerInitPlace);
//        Graphic::ReleaseBitmap(instructionBoard);
//
//        //
//        Graphic::ReleaseBitmap(enemy1);
//        Graphic::ReleaseBitmap(enemy2);
//        Graphic::ReleaseBitmap(enemy3);
//        
//        Graphic::ReleaseBitmap(hamburger);
//        Graphic::ReleaseBitmap(play_or_pause);
//        Graphic::ReleaseBitmap(hbullet);
//        Graphic::ReleaseBitmap(WantToContinue);
//        Graphic::ReleaseBitmap(yesBtn);
//        Graphic::ReleaseBitmap(noBtn);
//        Graphic::ReleaseBitmap(boardYesNo);
//
//
//        OutputDebugStringA("~PlayScreen1\n");
//    }
//
//    void PlayScreen1::loadContent(int width, int height) {
//        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
//        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
//        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
//        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
//        float scaleC = 5;                                   // scale cho input
//        float scaleD = 10;                                  // sacle cho text login
//        float scaleE = 2;
//        
//        background           = Graphic::LoadBitmapImage(L"Assets/background/map1.bmp", scale);
//        towerInitPlace       = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
//        instructionBoard     = Graphic::LoadBitmapImage(L"Assets/game/info/board1.png", 1);
//        
//        //ENEMY LOAD
//        enemy1               = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
//        enemy3               = Graphic::LoadBitmapImage(L"Assets/game/enemy3/enemy3-1.png", 2);
//
//        ///////////////////////////////////////////////////////////////////////////////////////////
//
//        hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
//        play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
//        
//        hbullet              = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
//        
//        tower                = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
//        
//        // route handle
//        WantToContinue = Graphic::LoadCustomTest("WANTTOCONTINUE", 4);
//        yesBtn = Graphic::LoadBitmapImage(L"Assets/button/AcceptBtn.png", 4);
//        noBtn = Graphic::LoadBitmapImage(L"Assets/button/RejectBtn.png", 4);
//        boardYesNo = Graphic::LoadBitmapImage(L"Assets/board/board.bmp", 1.5);
//        
//    }
//
//    void PlayScreen1::handleInput(HWND hwnd) {
//        POINT cursorPos;
//        GetCursorPos(&cursorPos);
//        ScreenToClient(GetActiveWindow(), &cursorPos);
//
//        // Left mouse button pressed
//        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
//            auto now = std::chrono::steady_clock::now();
//            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
//                lastMouseClickTime = now;
//                // if click the play 
//                RECT playRect = {
//                    posbuttonplay.x,
//                    posbuttonplay.y,
//                    posbuttonplay.x + buttonSize.x * 1.8, // Button width
//                    posbuttonplay.y + buttonSize.y * 1.8 // Button height
//                };
//                /*
//                    HANDLE CLICK
//
//                    PAUSE GAME || PLAY GAME
//                */
//                if (PtInRect(&playRect, cursorPos)) {
//                    // if click play 
//                    if (manageFirstTime) {
//                        //IsPlayGame = true;
//                        statePlayingGame = PLAY;
//                        manageFirstTime = false;
//                        for (int i = 0; i < enemylist.size(); i++) {
//                            enemylist[i].isMove = true;
//                        }
//                    }
//                    else {
//                        if (statePlayingGame == PLAY) {
//                            displayYesNoBoard = true;
//                            //IsPlayGame = false;
//                            statePlayingGame = PAUSE;
//                            for (int i = 0; i < enemylist.size(); i++) {
//                                enemylist[i].isMove = false;
//                            }
//                        }
//                    }
//                    //}
//
//                    /*=========================================================================
//                        PAUSE GAME
//                      =========================================================================
//                    */
//                    if (displayYesNoBoard) {
//                        // if yes
//                        RECT yesRect = {
//                            yesBtnPos.x,
//                            yesBtnPos.y,
//                            yesBtnPos.x + yesnoSize.x * 4, // Button width
//                            yesBtnPos.y + yesnoSize.y * 4 // Button height
//                        };
//
//                        if (PtInRect(&yesRect, cursorPos)) {
//                            displayYesNoBoard = false;
//                            //IsPlayGame = true;
//                            for (int i = 0; i < enemylist.size(); i++) {
//                                enemylist[i].isMove = true;
//                            }
//
//                            statePlayingGame = PLAY;
//                        }
//
//                        // if no
//                        RECT noRect = {
//                            noBtnPos.x,
//                            noBtnPos.y,
//                            noBtnPos.x + yesnoSize.x * 4, // Button width
//                            noBtnPos.y + yesnoSize.y * 4 // Button height
//                        };
//                        if (PtInRect(&noRect, cursorPos)) {
//
//                            for (int i = 0; i < enemylist.size(); i++) {
//                                enemylist[i].isMove = false;
//                            }
//
//                            //std::vector<saveGame> games = getGameList();
//
//                            //saveGame newGame;
//
//                            //newGame.gameId = 0;
//                            //for (auto game : games) {
//                            //    if (newGame.gameId <= game.gameId) {
//                            //        newGame.gameId++;
//                            //    }
//                            //}
//                            //for (auto enemy : enemylist) {
//                            //    newGame.listEnemy.push_back({ enemy.getHealth(), enemy.getCurr(), enemy.getPath(), enemy.getIndex() });
//                            //}
//                            //for (auto tower : towerlist) {
//                            //    newGame.listTower.push_back({ tower.getLocation() });
//                            //}
//                            //newGame.mapCode = mapCode;
//                            //newGame.UserId = Guess.getId();
//
//
//                            ///*vector<int> gameID = Guess.getListGame();
//                            //gameID.push_back(newGame.gameId);
//                            //Guess.setListGame(gameID);*/
//                            ////OutputDebugStringA(std::to_string(newGame.UserId).c_str());
//
//                            //appendGameToFile(newGame);
//
//
//                            PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
//                        }
//                    }
//
//                    // if click in hamburger display board 
//                    RECT hamburgerRect = {
//                        hamburgerPos.x,
//                        hamburgerPos.y,
//                        hamburgerPos.x + buttonSize.x * 1.5, // Button width
//                        hamburgerPos.y + buttonSize.y * 1.5 // Button height
//                    };
//                    if (PtInRect(&hamburgerRect, cursorPos)) {
//                        displayBoard = !displayBoard;
//                    }
//
//
//                    /*
//                        CHECK END GAME
//                    */
//                    // HANDLE INPUT BOARD WIN GAME
//                    if (statePlayingGame == WIN)
//                    {
//                        // if yes
//                        RECT yesRect = {
//                            yesBtnPos.x,
//                            yesBtnPos.y,
//                            yesBtnPos.x + yesnoSize.x * 4, // Button width
//                            yesBtnPos.y + yesnoSize.y * 4 // Button height
//                        };
//
//                        // GO TO THE NEXT LEVEL 
//                        if (PtInRect(&yesRect, cursorPos)) {
//                            PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
//                        }
//
//                        // if no
//                        RECT noRect = {
//                            noBtnPos.x,
//                            noBtnPos.y,
//                            noBtnPos.x + yesnoSize.x * 4, // Button width
//                            noBtnPos.y + yesnoSize.y * 4 // Button height
//                        };
//
//                        // back to MAIN SCREEN
//                        if (PtInRect(&noRect, cursorPos)) {
//                            PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
//                        }
//                    }
//                    else
//                        // HANDLE INPUT BOARD LOSE GAME
//                        if (statePlayingGame == LOSE)
//                        {
//                            // if yes
//                            RECT yesRect = {
//                                yesBtnPos.x,
//                                yesBtnPos.y,
//                                yesBtnPos.x + yesnoSize.x * 4, // Button width
//                                yesBtnPos.y + yesnoSize.y * 4 // Button height
//                            };
//                        }
//                }
//            }
//
//            bool mouseClicked = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
//
//            static bool mouseReleased = true; // Trạng thái chuột đã nhả (tránh lặp sự kiện)
//            if (mouseClicked && mouseReleased) {
//                mouseReleased = false; // Đánh dấu chuột đã bấm
//
//                if (!isPicking) {
//                    // Người dùng chưa "nhặt tháp", bắt đầu "nhặt tháp"
//                    RECT initTowerRect = {
//                        Turretinit.x,
//                        Turretinit.y,
//                        Turretinit.x + towerSize.x * 2, // Chiều rộng nút
//                        Turretinit.y + towerSize.y * 2  // Chiều cao nút
//                    };
//
//                    if (PtInRect(&initTowerRect, cursorPos)) {
//                        isPicking = true;                // Chuyển sang trạng thái "nhặt tháp"
//                        Tpicking.setLocation(cursorPos); // Đặt vị trí ban đầu theo con trỏ chuột
//                    }
//                    RECT yesRect = {
//                                yesBtnPos.x,
//                                yesBtnPos.y,
//                                yesBtnPos.x + yesnoSize.x * 4, // Button width
//                                yesBtnPos.y + yesnoSize.y * 4 // Button height
//                    };
//                    // GO TO THE NEXT LEVEL 
//                    if (PtInRect(&yesRect, cursorPos)) {
//                        PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 1, 0);
//                    }
//
//                    // if no
//                    RECT noRect = {
//                        noBtnPos.x,
//                        noBtnPos.y,
//                        noBtnPos.x + yesnoSize.x * 4, // Button width
//                        noBtnPos.y + yesnoSize.y * 4 // Button height
//                    };
//
//                    // back to MAIN SCREEN
//                    if (PtInRect(&noRect, cursorPos)) {
//                        PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
//                    }
//
//                }
//
//            }
//
//            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
//                // if hold tower 
//                RECT initTowerRect = {
//                    Turretinit.x,
//                    Turretinit.y,
//                    Turretinit.x + towerSize.x * 2, // Button width
//                    Turretinit.y + towerSize.y * 2 // Button height
//                };
//                if (PtInRect(&initTowerRect, cursorPos)) {
//                    isPicking = true;
//                }
//                else {
//                    if (checkValidPos(Tpicking.getLocation())) {
//                        towerlist.push_back(Tpicking); // Thêm vào danh sách nếu hợp lệ
//                        isPicking = false;            // Kết thúc trạng thái "nhặt tháp"
//                    }
//                }
//            }
//
//            if (!mouseClicked) {
//                mouseReleased = true; // Đánh dấu chuột đã nhả
//            }
//
//            // Nếu đang "nhặt tháp", cập nhật vị trí theo con trỏ chuột
//            if (isPicking) {
//                Tpicking.setLocation(cursorPos);
//            }
//
//        }
//    }
//
//    void PlayScreen1::update(float delta) {
//        
//        // KIỂM TRA TRẠNG THÁI GAME
//        // CHỈ CẬP NHẬT TRẠNG THÁI MỚI NẾU STATE == PLAY
//        if (statePlayingGame != PLAY) return;
//        
//        // CẬP NHẬT TRẠNG THÁI ENEMY
//
//        for (auto& enemy : enemylist) {
//            if (enemy.isMove && !enemy.isEnd()) {
//                enemy.update(delta);
//            }
//        }
//
//        // update state playing game (win,lose,countheart)
//        //
//        int countDead = 0;
//        for (auto& enemy : enemylist) {
//            if (enemy.isEnd()) {
//                countHeart++;
//            }
//            if (enemy.isDead()) countDead++;
//        }
//
//        if (countDead + countHeart >= 10 && countHeart == 0)
//        {
//            statePlayingGame = WIN;
//            return;
//        }
//        else countDead = 0;
//
//        if (countHeart >= 1)
//        {
//            statePlayingGame = LOSE;
//            return;
//        }
//        else countHeart = 0;
//        //======================================================================
//        
//        /*enemylist.erase(
//            std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
//                return e.isDead() || e.isEnd();  
//                }),
//            enemylist.end()
//        );*/
//
//        // Towers shoot at the nearest enemy in range and update bullets
//        for (auto& tower : towerlist) {
//            cenemy* nearestEnemy = nullptr;
//            float minDistanceSquared = tower.getRange() * tower.getRange();
//            POINT towerPos = tower.getLocation();
//
//            // Xác định bounding box của phạm vi tower
//            RECT rangeRect = {
//                towerPos.x - static_cast<int>(tower.getRange()),
//                towerPos.y - static_cast<int>(tower.getRange()),
//                towerPos.x + static_cast<int>(tower.getRange()),
//                towerPos.y + static_cast<int>(tower.getRange())
//            };
//
//            for (auto& enemy : enemylist) {
//                if (!enemy.isMove || enemy.isEnd()) continue;
//
//                POINT enemyPos = enemy.getCurr();
//                if (!PtInRect(&rangeRect, enemyPos)) continue; // Bỏ qua nếu ngoài phạm vi
//
//                int dx = enemyPos.x - towerPos.x;
//                int dy = enemyPos.y - towerPos.y;
//                float distanceSquared = static_cast<float>(dx * dx + dy * dy);
//
//                if (distanceSquared < minDistanceSquared) {
//                    minDistanceSquared = distanceSquared;
//                    nearestEnemy = &enemy;
//                }
//            }
//
//            if (nearestEnemy) {
//                tower.shootAt(nearestEnemy);   
//            }
//            if (nearestEnemy) {
//                int x = nearestEnemy->getHealth();
//                if (x < 0) {
//                    guess.setPoint(guess.getPoint() + 10);
//                }
//            }
//
//            tower.updateBullet();
//        }
//    
//    
//    }
//
//    void PlayScreen1::render(HDC hdc) {
//
//        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
//        Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
//        Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
//
//        Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);
//
//
//        int numberEnemy = enemylist.size();
//
//        for (int i = 0; i < numberEnemy - 1; i++)
//            if (!enemylist[i].isDead() && !enemylist[i].isEnd())
//                enemylist[i].render(enemy1, hdc);
//
//        if (!enemylist[numberEnemy - 1].isDead() && !enemylist[numberEnemy - 1].isEnd())
//            enemylist[numberEnemy - 1].render(enemy3, hdc);
//
//
//        /*for (auto E : enemylist) {
//            E.render(enemy1, hdc);
//        }*/
//
//
//
//        for (auto T : towerlist) {
//            T.render(tower, hdc);
//
//            cbullet b = T.getBullet();
//
//            if (b.isActive()) {
//                b.render(hbullet, hdc);
//            }
//        }
//
//        // ve tower trong box
//        Graphic::DrawBitmap(tower, Turretinit, hdc);
//
//        // ve tower trong qua trinh di chuyen 
//        if (isPicking) {
//            Tpicking.render(tower, hdc);
//        }
//
//        // BẢNG HƯỚNG DẪN
//        if (displayBoard) {
//            Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
//        }
//        if (displayYesNoBoard) {
//            Graphic::DrawBitmap(boardYesNo, boardYesNoPos, hdc);
//            Graphic::DrawBitmap(WantToContinue, WantToContinuePos, hdc);
//            Graphic::DrawBitmap(yesBtn, yesBtnPos, hdc);
//            Graphic::DrawBitmap(noBtn, noBtnPos, hdc);
//        }
//
//
//        //----------------------------------------------
//        // DRAW BOARD END GAME
//        //----------------------------------------------
//        if (statePlayingGame == LOSE)
//        {
//            Graphic::DrawBitmap(Graphic::LoadBitmapImage(L"Assets/game/info/BoardLose.png", 1.2), { 280, 60 }, hdc);
//            Graphic::DrawBitmap(yesBtn, yesBtnPos, hdc);
//            Graphic::DrawBitmap(noBtn, noBtnPos, hdc);
//        }
//        else
//            if (statePlayingGame == WIN)
//            {
//                Graphic::DrawBitmap(Graphic::LoadBitmapImage(L"Assets/game/info/BoardWin.png", 1.2), { 280, 60 }, hdc);
//                Graphic::DrawBitmap(yesBtn, yesBtnPos, hdc);
//                Graphic::DrawBitmap(noBtn, noBtnPos, hdc);
//            }
//    }
//
//    //========================================================================================================================//
//}