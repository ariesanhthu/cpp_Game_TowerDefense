#pragma once
#include <vector>
#include <memory>
#include "Screen/Screen.h"
#include "GameManage/GamePlayManage.h"
#include "Screen/ScreenManager.h"

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

        cplayer guess;
        GameState statePlayingGame = PAUSE;
        int countHeart = 0;

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
        std::shared_ptr<Item> _loseBoard; // hien tai giong pause
       
        // win game 
        std::shared_ptr<Item> _winBoard; // hien tai giong pause
 

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

        // CHECK COI K DÙNG THÌ XÓA
        bool displayBoard = true;

        // position init place of box
        POINT towerInitPos = { 25, 520 };
        POINT Turretinit = { 50, 565 };

        // delay hand variable
        std::chrono::steady_clock::time_point lastMouseClickTime;
        std::chrono::steady_clock::time_point lastKeyPressTime;
        const int debounceDelayMs = 200; // 200 ms debounce delay

        //// enemy 
        //std::vector<cenemy> enemylist;
        //POINT Einit;              // enemy position

        //// tower
        //std::vector<ctower> towerlist;
        //POINT Turretinit;         // tower position 

        GamePlayManage manager;

        std::shared_ptr<TowerBase> pickedTowerType1 = TowerFactory::createTower(0, { Turretinit.x, Turretinit.y, 0 });
        std::shared_ptr<TowerBase> renderTowerType1 = TowerFactory::createTower(0, { Turretinit.x, Turretinit.y, 0 });

        // tower de chon di chuyen
        /*ctower Tpicking;
        POINT TcurrentPick;
        bool isPicking = false;
        bool isMouseDown = false;*/

        // size
        /*POINT buttonSize = { 26, 29 };
        POINT boardSize = { 260, 180 };
        POINT towerSize = { 20, 30 };*/

        // support 


        /* =======================================

        FIXBIG
        THÊM ĐƯỜNG

        ======================================= */

        bool isInRange(POINT pos, int range) {
            return range < sqrt((pos.x * pos.x + pos.y * pos.y));
        }

    public:
        //MapScreen();
        virtual ~MapScreen() {}

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

            static bool isMousePressed = false;   // Trạng thái chuột trái được nhấn
            static bool isPicking = false;        // Tháp đang được nhấc lên
            static bool isPickedFromInitPos = false; // Tháp nhấc từ initPos

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
                            if (manager.gameStatus == PAUSE)
                                manager.gameStatus = PLAY;
                            else
                                manager.gameStatus = PAUSE;
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
                            TowerFactory::createTower(1, { cursorPos.x, cursorPos.y, 0 })
                        );
                    }

                    // Đặt tháp được nhấc trở về vị trí ban đầu
                    pickedTowerType1->setCurrentPosition({ Turretinit.x, Turretinit.y, 0 });
                }

                isMousePressed = false; // Reset trạng thái chuột
            }

            // Nếu đang nhấc tháp, cập nhật vị trí tháp theo tọa độ chuột
            if (isPicking) {
                pickedTowerType1->setCurrentPosition({ cursorPos.x, cursorPos.y, 0 });
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
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
                }
                if (_noBtn->isClicked(cursorPos)) {
                    // save game 
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                }
            }

            if (statePlayingGame == WIN) {
                if (_yesBtn->isClicked(cursorPos)) {

                    // qua man tiep theo, hien tai de reload map

                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
                }
                if (_noBtn->isClicked(cursorPos)) {
                    // save game 
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                }
            }

            if (statePlayingGame == PAUSE)
            {
                if (_yesBtn->isClicked(cursorPos)) {
                    manager.gameStatus = PLAY;
                    statePlayingGame = PLAY;
                    _yesnoBoard->setTriger(false);
                    _noBtn->setTriger(false);
                    _yesBtn->setTriger(false);
                }
                if (_noBtn->isClicked(cursorPos)) {
                    // save game 
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
            if (manager.gameStatus == WIN) {
                statePlayingGame = WIN;

                _winBoard->setTriger(true);
            }
            //----------- LOSE GAME -----------
            else if (manager.gameStatus == LOSE) {
                statePlayingGame = LOSE;

                _loseBoard->setTriger(true);

            }
            //----------- PLAY GAME -----------
            else if (manager.gameStatus == PLAY) {
                //OutputDebugStringA("11111111111111111\n");
                manager.update(delta);
                statePlayingGame = PLAY;
            }
            //----------- PAUSE GAME -----------
            else if (manager.gameStatus == PAUSE) {
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

        // ====================================================================================

        // ----------------------------------------------------
        // CÁC HÀM DÙNG CHUNG GIỮA CÁC MAP
        // ----------------------------------------------------
        // ------ SETUPGAME -----
        void GamePlaySetup()
        {
            manager.setup(path);

            //----------------
            int nofpath = path.size();

            manager.enemyManager.setup(mapSetup);

            //setup enemy for each phase
            for(size_t e = 1; e <= 3; e++)
                for (int i = 0; i < mapSetup[e]; i++)
                    manager.enemyManager.addEnemy(EnemyFactory::createEnemy(e, rand() % nofpath));
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
            return true;
        }
    }; // END CLASS
} // END NAMESPACE
