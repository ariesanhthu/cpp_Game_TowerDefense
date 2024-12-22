﻿#pragma once
#include <vector>
#include <memory>
#include "Screen/Screen.h"
#include "GameManage/GamePlayManage.h"
#include "Screen/ScreenManager.h"
#include <fstream>

#include "User/SaveGameManager.h"
#include "User/UserManager.h"
#include "User/SaveGame.h"
#include "User/User.h"

using namespace std;

namespace towerdefense
{
    /*
   ////////////////////////////////
           STATE GAME
   ////////////////////////////////
   */
    enum GameState {
        PLAY = 0,
        WIN = 1,
        LOSE = 2,
        PAUSE = 3,
    };

    class MapScreen : public Screen {
    protected:
        // --- SETUP ---
        vector<vector<cpoint>> path;
        vector<int> mapSetup;
        // -------------

        GameState statePlayingGame = PAUSE;
        int countHeart = 0;

        bool loadstatus = false;

        // buton play or pause 
        POINT posbuttonplay = { 580, 570 };

        std::shared_ptr<Button> _playOrPause;
        std::shared_ptr<Button> _hamburger;
        std::shared_ptr<Item> _background;
        std::shared_ptr<Item> _instructionboard;
        std::shared_ptr<Item> _towerInitPlace;

        // yes no board
        std::shared_ptr<Item> _yesnoBoard;
        std::shared_ptr<Button> _yesBtn;
        std::shared_ptr<Button> _noBtn;

        // lose game 
        std::shared_ptr<Item> _loseBoard; 
       
        // win game 
        std::shared_ptr<Item> _winBoard; 
 

        // PAUSE BOARD
        //std::shared_ptr<Item> _pauseBoard;

        //bool IsPlayGame = false;
        bool manageFirstTime = true;

        // Pause handling
        bool displayYesNoBoard = false;
        POINT WantToContinuePos = { 500, 250 };
        POINT boardYesNoPos = { 280, 60 };
        POINT yesBtnPos = { 525, 350 };
        POINT noBtnPos = { 700, 350 };
        POINT yesnoSize = { 18, 20 };

        // instruction pos
        POINT instructionPos = { 800, 50 };
        POINT hamburgerPos = { 1200, 5 };

        // position init place of box
        POINT towerInitPos = { 25, 520 };
        POINT Turretinit = { 50, 565 };
        POINT Turretinit1 = { 52, 568 };
        POINT Turretinit2 = { 120, 563 };
        POINT Turretinit3 = { 192, 565 };
        int towerPicked = 0;

        // delay hand variable
        std::chrono::steady_clock::time_point lastMouseClickTime;
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 200; // 200 ms debounce delay

        GamePlayManage manager;

        std::shared_ptr<TowerBase> pickedTowerType1;
        std::shared_ptr<TowerBase> renderTowerType1;
        std::shared_ptr<TowerBase> pickedTowerType2;
        std::shared_ptr<TowerBase> renderTowerType2;
        std::shared_ptr<TowerBase> pickedTowerType3;
        std::shared_ptr<TowerBase> renderTowerType3;

    public:
        MapScreen() {
            manager.destroy();
            manager.setupTower();

            pickedTowerType1 = TowerFactory::createTower(0, { Turretinit1.x, Turretinit1.y, 0 });
            renderTowerType1 = TowerFactory::createTower(0, { Turretinit1.x, Turretinit1.y, 0 });
            pickedTowerType2 = TowerFactory::createTower(1, { Turretinit2.x, Turretinit2.y, 0 });
            renderTowerType2 = TowerFactory::createTower(1, { Turretinit2.x, Turretinit2.y, 0 });
            pickedTowerType3 = TowerFactory::createTower(2, { Turretinit3.x, Turretinit3.y, 0 });
            renderTowerType3 = TowerFactory::createTower(2, { Turretinit3.x, Turretinit3.y, 0 });

            loadstatus = false;
        }
        MapScreen(bool _loadstatus) { 
            manager.destroy(); 
            manager.setupTower();

            pickedTowerType1 = TowerFactory::createTower(0, { Turretinit1.x, Turretinit1.y, 0 });
            renderTowerType1 = TowerFactory::createTower(0, { Turretinit1.x, Turretinit1.y, 0 });
            pickedTowerType2 = TowerFactory::createTower(1, { Turretinit2.x, Turretinit2.y, 0 });
            renderTowerType2 = TowerFactory::createTower(1, { Turretinit2.x, Turretinit2.y, 0 });
            pickedTowerType3 = TowerFactory::createTower(2, { Turretinit3.x, Turretinit3.y, 0 });
            renderTowerType3 = TowerFactory::createTower(2, { Turretinit3.x, Turretinit3.y, 0 });

            loadstatus = _loadstatus;   
        };
        virtual ~MapScreen() {

        }

        /* --------------------------------------------------
                        TEMPLATE METHOD
            - Các code dùng chung đặt trong MapScreen
            - Gọi đa hình các code riêng với từng map khác nhau
           --------------------------------------------------
        */
        // ====================================================================================
        // ---- CÁC HÀM DÙNG CHUNG --------
        //virtual void loadContent(int width, int height) = 0;
        void loadContent(int width, int height)
        {
            _towerInitPlace = std::make_shared<Item>(L"Assets/game/BoardSetupTower.png", 1.5f, towerInitPos);
            _hamburger = std::make_shared<Button>(L"Assets/button/aboutBtn.png", L"Assets/button/selectbox.bmp", 2, hamburgerPos);
            _playOrPause = std::make_shared<Button>(L"Assets/button/btnPlay.png", L"Assets/button/selectbox.bmp", 2, posbuttonplay);

            _yesnoBoard = std::make_shared<Item>(L"Assets/game/info/BoardPAUSE.png", 1.2, boardYesNoPos);
            _yesBtn = std::make_shared<Button>(L"Assets/button/AcceptBtn.png", L"Assets/button/selectbox.bmp", 3, yesBtnPos);
            _noBtn = std::make_shared<Button>(L"Assets/button/RejectBtn.png", L"Assets/button/selectbox.bmp", 3, noBtnPos);

            _loseBoard = std::make_shared<Item>(L"Assets/game/info/BoardLose.png", 1.2, boardYesNoPos);
            _winBoard = std::make_shared<Item>(L"Assets/game/info/BoardWin.png", 1.2, boardYesNoPos);

            // Gọi hàm riêng (abstract)
            loadSpecificContent(width, height);
        }
        
        void handleInput(HWND hwnd) {
            // Lấy tọa độ con trỏ chuột
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(GetActiveWindow(), &cursorPos);

            static bool isMousePressed = false;         // Trạng thái chuột trái được nhấn
            static bool isPicking = false;              // Tháp đang được nhấc lên
            static bool isPickedFromInitPos = false;    // Tháp nhấc từ initPos

            // Kiểm tra chuột trái được nhấn
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                if (!isMousePressed) { // Chỉ xử lý 1 lần khi chuột nhấn xuống
                    isMousePressed = true;
                    // Xử lý nút PLAY/PAUSE
                    if (_playOrPause->isClicked(cursorPos)) {
                        if (manageFirstTime) {
                            statePlayingGame = PLAY; // Bắt đầu chơi
                            manageFirstTime = false;
                        }
                        // --------------------------------- PAUSE GAME ---------------------------------
                        else
                        {
                            if (manager.getGameStatus() == PAUSE)
                                manager.setGameStatus(PLAY);
                            else
                                manager.setGameStatus(PAUSE);
                        }
                    }

                    // Xử lý nút HAMBURGER để mở/đóng instruction board
                    if (_hamburger->isClicked(cursorPos)) {
                        bool currentTrigger = _instructionboard->getTriger();
                        _instructionboard->setTriger(!currentTrigger);
                    }

                    // Kiểm tra click vào tháp tại vị trí initPos
                    if (renderTowerType1->isHovered(cursorPos)) {
                        isPicking = true;          // Bắt đầu nhấc tháp
                        isPickedFromInitPos = true; // Đánh dấu nhấc từ vị trí initPos
                        towerPicked = 0;
                    }else
                    if (renderTowerType2->isHovered(cursorPos)) {
                        isPicking = true;          // Bắt đầu nhấc tháp
                        isPickedFromInitPos = true; // Đánh dấu nhấc từ vị trí initPos
                        towerPicked = 1;
                    }else
                    if (renderTowerType3->isHovered(cursorPos)) {
                        isPicking = true;          // Bắt đầu nhấc tháp
                        isPickedFromInitPos = true; // Đánh dấu nhấc từ vị trí initPos
                        towerPicked = 2;
                    }
                }
            }
            else
                /*
                            PICKING TOWER
                */
            { // Xử lý khi chuột trái được thả
                if (isPicking && isPickedFromInitPos) {
                    isPicking = false;       // Kết thúc trạng thái nhấc tháp
                    isPickedFromInitPos = false;

                    // Thêm tháp mới vào TowerManager tại vị trí con trỏ chuột
                    if (checkValidPos(cursorPos)) {
                        manager.towerManager.addTower(
                            TowerFactory::createTower(towerPicked, { cursorPos.x, cursorPos.y, 0 })
                        );
                    }

                    // Đặt tháp được nhấc trở về vị trí ban đầu
                    pickedTowerType1->setCurrentPosition({ Turretinit1.x, Turretinit1.y, 0 });
                    pickedTowerType2->setCurrentPosition({ Turretinit2.x, Turretinit2.y, 0 });
                    pickedTowerType3->setCurrentPosition({ Turretinit3.x, Turretinit3.y, 0 });
                }

                isMousePressed = false; // Reset trạng thái chuột
            }

            // Nếu đang nhấc tháp, cập nhật vị trí tháp theo tọa độ chuột
            if (isPicking) {
                if (towerPicked == 0)
                    pickedTowerType1->setCurrentPosition({ cursorPos.x, cursorPos.y, 0 });
                else if (towerPicked == 1)
                    pickedTowerType2->setCurrentPosition({ cursorPos.x, cursorPos.y, 0 });
                else if (towerPicked == 2)
                    pickedTowerType3->setCurrentPosition({ cursorPos.x, cursorPos.y, 0 });
            }
            //--------------------------------------------------------------------------

            /*
                GIỐNG NHAU GIỮA CÁC SCREEN -> STATE
            */

            /*if (statePlayingGame == PLAY)
            {
                
            }*/

            if (statePlayingGame == LOSE) {

                if (_yesBtn->isClicked(cursorPos)) {
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, getCurrentMap(), 0);
                }
                if (_noBtn->isClicked(cursorPos)) {
                    // save game 
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                }
            }

            if (statePlayingGame == WIN) {

                if (_yesBtn->isClicked(cursorPos)) {

                    // qua man tiep theo, hien tai de reload map
                    int nextMap = getCurrentMap() + 1;
                    if(nextMap > 4)
						nextMap = 0;

                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, nextMap, 0);
                }
                if (_noBtn->isClicked(cursorPos)) {
                    // save game 
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                }
            }

            if (statePlayingGame == PAUSE)
            {
                if (_yesBtn->isClicked(cursorPos)) {
                    manager.setGameStatus(PLAY);
                    statePlayingGame = PLAY;
                    _yesnoBoard->setTriger(false);
                    _noBtn->setTriger(false);
                    _yesBtn->setTriger(false);
                }
                if (_noBtn->isClicked(cursorPos)) {

                    // save game

                    int mapCode = getCurrentMap();

                    saveToLoadGame();
                    
                    // trở về home
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                }
            }

            // handle mấy cái riêng
             //OutputDebugStringA("handleSpecificInput 2\n");
        }
        
        void update(float delta)
        {
            if (statePlayingGame != PLAY) return;

            //----------- WIN GAME -----------
            if (manager.getGameStatus() == WIN) {
                statePlayingGame = WIN;

                _winBoard->setTriger(true);
            }
            //----------- LOSE GAME -----------
            else if (manager.getGameStatus() == LOSE) {
                statePlayingGame = LOSE;

                _loseBoard->setTriger(true);

            }
            //----------- PLAY GAME -----------
            else if (manager.getGameStatus() == PLAY) {
                manager.update(delta);
                statePlayingGame = PLAY;
            }
            //----------- PAUSE GAME -----------
            else if (manager.getGameStatus() == PAUSE) {
                statePlayingGame = PAUSE;

                _yesnoBoard->setTriger(true);
            }
        }
        
        void render(HDC hdc)
        {
            renderCommonElements(hdc);
        }


        // ------- ABSTRACT FUNCTION --------

        virtual void loadSpecificContent(int width, int height) = 0;
        virtual int getCurrentMap() = 0;

        // ====================================================================================

        // ----------------------------------------------------
        // CÁC HÀM DÙNG CHUNG GIỮA CÁC MAP
        // ----------------------------------------------------
        // ------ SETUPGAME -----
        void GamePlaySetup()
        {
            // nếu là game mới 
            if (loadstatus == false) {

                OutputDebugStringA(
                    (
                        "NEW GAMEEE........................ " + std::to_string(getCurrentMap()) + " " + std::to_string(loadstatus) + "\n"
                        ).c_str()
                );

                manager.setupEnemy(path);

                //----------------
                int nofpath = path.size();

                manager.enemyManager.setup(mapSetup);

                //setup enemy for each phase
                for (size_t e = 1; e <= 3; e++)
                {
                    int typeEnemy = e;

                    // Đổi style enemy Goblin đi bộ thành Goblin bơi
                    if(e == 1 && getCurrentMap() == 4) 
					    typeEnemy = 4;

                    for (int i = 0; i < mapSetup[e]; i++) {                    
                        manager.enemyManager.addEnemy(EnemyFactory::createEnemy(typeEnemy, rand() % nofpath));
                    }
                }
            }
            // nếu là load game
            else {
                OutputDebugStringA(
                    (
                        "LOADDINGGGGGGGG........................ " + std::to_string(getCurrentMap()) + " " + std::to_string(loadstatus) + "\n"
                     ).c_str()
                                    );

                manager.setupEnemy(path);
                manager.enemyManager.setup(mapSetup);

                std::shared_ptr<SaveGameSupport> supsave;
                SaveGame game_saving = supsave->readMapInfo(getCurrentMap());
                
                // get all enemy element 
                vector<cpoint> enemyPos = game_saving.getEnemyPos();
                vector<int> enemyHealth = game_saving.getEnemyHealth();
                vector<int> enemyPathNumber = game_saving.getEnemyPathNumber();
                vector<int> enemyType = game_saving.getEnemyType();
                vector<int> enemyIndex = game_saving.getEnemyIndex();
                int enemyCount = enemyPos.size();

                for (int i = 0; i < enemyCount; ++i) {
                    // Tạo chuỗi debug cho từng enemy
                    std::string message = "Enemy " + std::to_string(i) + ": " +
                        "Pos (" + std::to_string(enemyPos[i].getX()) + ", " + std::to_string(enemyPos[i].getY()) + ") " +
                        "Health: " + std::to_string(enemyHealth[i]) + " " +
                        "Path: " + std::to_string(enemyPathNumber[i]) + " " +
                        "Type: " + std::to_string(enemyType[i]) + " " +
                        "Index: " + std::to_string(enemyIndex[i]) + "\n";

                    // In chuỗi ra OutputDebugStringA
                    OutputDebugStringA(message.c_str());
                }
                
                // get all tower element 
                vector<cpoint> towerPos = game_saving.getTowerPos();
                vector<int> towerType = game_saving.getTowerType();
                int towerCount = towerPos.size();
               
                for (int i = 0; i < towerCount; ++i) {
                    // Tạo chuỗi debug cho từng tháp
                    std::string message = "Tower " + std::to_string(i) + ": " +
                        "Pos (" + std::to_string(towerPos[i].getX()) + ", " + std::to_string(towerPos[i].getY()) + ") " +
                        "Type: " + std::to_string(towerType[i]) + "\n";

                    // In chuỗi ra OutputDebugStringA
                    OutputDebugStringA(message.c_str());
                }

                //for (int i = 0; i < towerCount; i++) {
                //    store_tower[i]->setCurrentPosition(towerPos[i]);
                //    store_tower[i]->setType(towerType[i]);
                //}

                /*for (size_t e = 1; e <= 3; e++) {
                    for (int i = 0; i < mapSetup[e]; i++) {
                        manager.enemyManager.addEnemy(EnemyFactory::createEnemy(enemyType[i], enemyPathNumber[i]));
                    }
                }*/


                for (size_t e = 1; e <= 3; e++)
                {
                    for (int i = 0; i < mapSetup[e]; i++) {
                        manager.enemyManager.addEnemy(EnemyFactory::createEnemy(e, 0));
                    }
                }
                vector<shared_ptr<EnemyBase>> listEnemy(enemyCount, make_shared<EnemyBase>());
                for (int i = 0; i < enemyCount; i++) {
                    listEnemy[i]->setCurrentPosition(enemyPos[i]);
                    listEnemy[i]->setIndex(enemyIndex[i]);
                    listEnemy[i]->setHealth(enemyHealth[i]);
                    listEnemy[i]->setPath(enemyPathNumber[i]);
                }
                manager.enemyManager.setLoadEnemy(listEnemy);

                for (int i = 0; i < towerCount; i++) {
                    manager.towerManager.addTower(TowerFactory::createTower(towerType[i], towerPos[i]));
                }

                vector<shared_ptr<TowerBase>> listTower(towerCount, make_shared<TowerBase>());
                for (int i = 0; i < towerCount; i++) {
                    listTower[i]->setCurrentPosition(towerPos[i]);
                }
                manager.towerManager.setLoadTower(listTower);
            }
        }
        // ------ RENDER -----
        void renderCommonElements(HDC hdc) {

            _background->render(hdc);
            _hamburger->render(hdc);
            _towerInitPlace->render(hdc);

            if (_instructionboard->getTriger()) {
                _instructionboard->render(hdc);
            }


            pickedTowerType1->render(hdc);
            renderTowerType1->render(hdc);
            pickedTowerType2->render(hdc);
            renderTowerType2->render(hdc);
            pickedTowerType3->render(hdc);
            renderTowerType3->render(hdc);
            manager.render(hdc);

            _playOrPause->render(hdc);

            // ---------- BOARD ----------
            if (_yesnoBoard->getTriger()) {
                _yesnoBoard->render(hdc);
                _noBtn->render(hdc);
                _yesBtn->render(hdc);
            }

            if (_loseBoard->getTriger()) {
                _loseBoard->render(hdc);
                _noBtn->render(hdc);
                _yesBtn->render(hdc);
            }

            if (_winBoard->getTriger()) {
                _winBoard->render(hdc);
                _noBtn->render(hdc);
                _yesBtn->render(hdc);
            }
        }
        // ------ END RENDER -----
        bool checkValidPos(POINT cursurPos) {
            if (_towerInitPlace->isHovered(cursurPos)) {
                return false;
            }
            if (_playOrPause->isHovered(cursurPos)) {
                return false;
            }
            if (_hamburger->isHovered(cursurPos)) {
                return false;
            }
            if (_instructionboard->getTriger()) {
                if (_instructionboard->isHovered(cursurPos)) {
                    return false;
                }
            }


            return true;
        }
		// ------ save game ----- 
        void saveToLoadGame() {

            std::string name = "guess";

            int point = manager.getPoint();
            int health = manager.enemyManager.getUserHP();
            int mapCode = getCurrentMap();

            std::vector<cpoint> enemyPos;
            std::vector<int> enemyHealth;
            std::vector<int> enemyPathNumber;
            std::vector<int> enemyIndex;
            std::vector<int> enemyType;
            std::vector<cpoint> towerPos;
            std::vector<int> towerType;

            for (auto& enemy : manager.enemyManager.getAllEnemy()) {
                enemyPos.push_back(enemy->getCurrentPosition());
                enemyHealth.push_back(enemy->getHealth());
                enemyPathNumber.push_back(enemy->getPath());
                enemyIndex.push_back(enemy->getIndex());
                enemyType.push_back(enemy->getType());
            }

            for (auto& tower : manager.towerManager.getAllTower()) {
                towerPos.push_back(tower->getCurrentPosition());
                towerType.push_back(tower->getType());
            }

            SaveGame game_to_save(name, enemyPos, enemyHealth, enemyPathNumber, enemyIndex, enemyType, towerPos, towerType, point, mapCode, health); 


            game_to_save.writefile(mapCode);   
        }
        bool getLoadStatus() {
            return loadstatus;
        }
        void setLoadStatus(bool t) {
            loadstatus = t;
        }

    }; // END CLASS
} // END NAMESPACE
