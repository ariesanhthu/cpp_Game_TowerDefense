//#include "PlayScreen4.h"
//
//using namespace std;
//
//namespace towerdefense
//{
//
//    PlayScreen4::PlayScreen4() {
//        for (int i = 0; i < 10; i++) {
//            cenemy dummy;
//            std::vector<POINT> otherPath1 = epath1;
//            std::vector<POINT> otherPath2 = epath2;
//
//            otherPath1[0].x -= i * (rand() % 300 + 100);
//            otherPath2[0].y -= i * (rand() % 300 + 100);
//
//            int choice = rand() % 2 + 1;
//
//            if (choice == 1) {
//                dummy.setPath(otherPath1);
//            }
//            else if (choice == 2) {
//                dummy.setPath(otherPath2);
//            }
//
//            enemylist.push_back(dummy);
//        }
//
//        Turretinit = { 50, 565 };
//    }
//
//    PlayScreen4::~PlayScreen4() {
//        Graphic::ReleaseBitmap(background);
//        Graphic::ReleaseBitmap(tower);
//        Graphic::ReleaseBitmap(towerInitPlace);
//        Graphic::ReleaseBitmap(instructionBoard);
//
//        // Destroy enemy
//        Graphic::ReleaseBitmap(enemy1);
//        Graphic::ReleaseBitmap(enemy2);
//        Graphic::ReleaseBitmap(enemy3);
//        
//        Graphic::ReleaseBitmap(hamburger);
//        Graphic::ReleaseBitmap(play_or_pause);
//        Graphic::ReleaseBitmap(hbullet);
//
//
//        OutputDebugStringA("~PlayScreen2\n");
//    }
//
//    void PlayScreen4::loadContent(int width, int height) {
//        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
//        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
//        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
//        float scaleB = 3;                                   // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
//        float scaleC = 5;                                   // scale cho input
//        float scaleD = 10;                                  // sacle cho text login
//        float scaleE = 2;
//
//        background = Graphic::LoadBitmapImage(L"Assets/background/map4.bmp", scale);
//        towerInitPlace = Graphic::LoadBitmapImage(L"Assets/game/BoardSetupTower.png", 1.5);
//        instructionBoard = Graphic::LoadBitmapImage(L"Assets/game/info/board4.png", 1);
//        enemy1 = Graphic::LoadBitmapImage(L"Assets/game/slime.bmp", 2);
//        hamburger = Graphic::LoadBitmapImage(L"Assets/button/aboutBtn.png", 2);
//        play_or_pause = Graphic::LoadBitmapImage(L"Assets/button/btnPlay.png", 1.8);
//        hbullet = Graphic::LoadBitmapImage(L"Assets/game/bullet2-2.png", 2);
//        tower = Graphic::LoadBitmapImage(L"Assets/game/tured.bmp", 0.8);
//    }
//
//    void PlayScreen4::handleInput(HWND hwnd) {
//        POINT cursorPos;
//        GetCursorPos(&cursorPos);
//        ScreenToClient(GetActiveWindow(), &cursorPos);
//
//        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button pressed
//            auto now = std::chrono::steady_clock::now();
//            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
//                lastMouseClickTime = now;
//
//                OutputDebugStringA((std::to_string(cursorPos.x) + " " + std::to_string(cursorPos.y) + "\n").c_str());
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
//
//                    for (int i = 0; i < enemylist.size(); i++) {
//                        enemylist[i].isMove = !enemylist[i].isMove;
//                    }
//                }
//
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
//            }
//        }
//
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
//                isPicking = false;
//            }
//        }
//
//        if (isPicking) {
//            Tpicking.setLocation(cursorPos);
//        }
//        else {
//            // neu vi tri thoa dieu kien thi them vao list tower
//            if (checkValidPos(TcurrentPick)) {
//                towerlist.push_back(Tpicking);
//            }
//        }
//    }
//
//    void PlayScreen4::update(float delta) {
//        for (auto& enemy : enemylist) {
//            if (enemy.isMove && !enemy.isEnd()) {
//                enemy.update(delta);
//            }
//        }
//
//        enemylist.erase(
//            std::remove_if(enemylist.begin(), enemylist.end(), [](const cenemy& e) {
//                return e.isDead() || e.isEnd();
//                }),
//            enemylist.end()
//        );
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
//                // tower.shootAt(nearestEnemy->getCurr());
//                tower.shootAt(nearestEnemy);
//                //POINT pos = tower.getBullet().getCurr();
//                //if (pos.x)
//                //nearestEnemy->takeDamage(tower.getBullet().getDamage());
//            }
//
//            tower.updateBullet();
//        }
//    }
//
//    void PlayScreen4::render(HDC hdc) {
//        Graphic::DrawBitmap(background, { 0, 0 }, hdc);
//        Graphic::DrawBitmap(towerInitPlace, towerInitPos, hdc);
//        Graphic::DrawBitmap(play_or_pause, posbuttonplay, hdc);
//        if (displayBoard) {
//            Graphic::DrawBitmap(instructionBoard, instructionPos, hdc);
//        }
//        Graphic::DrawBitmap(hamburger, hamburgerPos, hdc);
//
//        for (auto E : enemylist) {
//            E.render(enemy1, hdc);
//        }
//
//        for (auto T : towerlist) {
//            
//            T.render(tower, hdc);
//            cbullet b = T.getBullet();
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
//
//
//    }
//}
//
//
