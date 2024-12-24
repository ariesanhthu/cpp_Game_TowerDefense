#pragma once
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

#include "User/Leaderboard.h"

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
        EXIT = 4,
    };

    class MapScreen : public Screen {
    protected:
        // FONT
        HFONT boldFont = FontManager::getInstance().getFont("bold");;
        // -------------
        // --- SETUP ---
        vector<vector<cpoint>> path;
        vector<int> mapSetup;
        int nOfTower = 5; // defaul number of Tower
        // -------------
        // --- GAME SCORE ----
        shared_ptr<TextElement> _scoreGame;
        shared_ptr<Item> _scoreBoard;
        POINT scorePos = { 900, 25 };
        POINT scoreBoardPos = { 860, 0 };
        //--------------------
        GameState statePlayingGame = PAUSE;
        int countHeart = 0;

        bool loadstatus = false;

        
        std::shared_ptr<Button> _play;
        std::shared_ptr<Button> _pause;


        std::shared_ptr<Button> _hamburger;
        std::shared_ptr<Button> _ExitHouse;
        std::shared_ptr<Item> _background;

        std::shared_ptr<Item> _instructionboard;
        std::shared_ptr<Item> _exitBoard;

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
        bool manageOut = false;

        // Pause handling
        bool displayYesNoBoard = false;
        POINT WantToContinuePos = { 500, 250 };
        POINT boardYesNoPos = { 280, 60 };
        POINT yesBtnPos = { 525, 350 };
        POINT noBtnPos = { 700, 350 };
        POINT yesnoSize = { 18, 20 };

        // exit handling 
        POINT exitDirectPos = { 700, 570 };

        // buton play or pause 
        POINT posbuttonplay = { 580, 570 };

        // instruction pos
        POINT instructionPos = { 800, 50 };
        POINT hamburgerPos = { 1150, 25 };

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

        // health 
        std::shared_ptr<Item> _health;
        int curHealth = 5;
        POINT firstHealthPos = { towerInitPos.x, towerInitPos.y };

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
            
            _play = std::make_shared<Button>(L"Assets/button/btnPlay.png", L"Assets/button/selectbox.bmp", 2, posbuttonplay);
            _pause = std::make_shared<Button>(L"Assets/button/btnContinue.png", L"Assets/button/selectbox.bmp", 2, posbuttonplay);

            _yesnoBoard = std::make_shared<Item>(L"Assets/game/info/BoardPAUSE.png", 1.2, boardYesNoPos);
            _yesBtn = std::make_shared<Button>(L"Assets/button/AcceptBtn.png", L"Assets/button/selectbox.bmp", 3, yesBtnPos);
            _noBtn = std::make_shared<Button>(L"Assets/button/RejectBtn.png", L"Assets/button/selectbox.bmp", 3, noBtnPos);

            _loseBoard = std::make_shared<Item>(L"Assets/game/info/BoardLose.png", 1.2, boardYesNoPos);
            _winBoard = std::make_shared<Item>(L"Assets/game/info/BoardWin.png", 1.2, boardYesNoPos);

            _ExitHouse = std::make_shared<Button>(L"Assets/button/HomeBtn.png", L"Assets/button/selectbox.bmp", 2, exitDirectPos);

            _exitBoard = std::make_shared<Item>(L"Assets/game/info/BoardGotoHome.png", 1.3f , boardYesNoPos);
            _health = std::make_shared<Item>(L"Assets/game/Heart.png", 1.5f, towerInitPos);

            // --------- SCORE ----------------
            
            _scoreGame = make_shared<TextElement>(L"0", boldFont, RGB(255, 255, 255), scorePos);
            _scoreGame->setTriger(true);

            _scoreBoard = std::make_shared<Item>(L"Assets/game/info/boardScore.png", 1.2f, scoreBoardPos);
            _scoreBoard->setTriger(true);
            // ---------------------------------

            // Gọi hàm riêng (abstract)
            loadSpecificContent(width, height);
        }

        // ------------------------------------------- LEADER BOARD ----------------------------------------------------
        void saveToLeaderBoard()
        {
            User user("Guess", manager.getPoint());
            auto& leaderBoard = Leaderboard::getInstance();
            leaderBoard.addUser(user);
            leaderBoard.writeFile(user);
        }
        // -------------------------------------------------------------------------------------------------------------
        
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

                    if (_pause->isEnabled()) {
                        // Kiểm tra trạng thái hiện tại của trò chơi
                        if (_pause->isClicked(cursorPos)) {
                            _ExitHouse->setEnabled(false);
                        
                            if (manageFirstTime) {
                                statePlayingGame = PLAY; // Bắt đầu chơi
                                manageFirstTime = false;
                                _ExitHouse->setEnabled(true);
                            }
                            else {
                                // Chuyển đổi giữa PAUSE và PLAY
                                if (manager.getGameStatus() == PAUSE)
                                    manager.setGameStatus(PLAY);
                                else
                                    manager.setGameStatus(PAUSE);
                            }

                            // Khi nhấn PLAY hoặc PAUSE, vô hiệu hóa nút EXIT
                        }
                    }

                    if (_ExitHouse->isClicked(cursorPos) && _ExitHouse->isEnabled()) {
                        statePlayingGame = EXIT;
                        _pause->setEnabled(false);
                    }


                    /*if (manager.getGameStatus() == PAUSE) {
                        _ExitHouse->setEnabled(true);
                    }*/


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

                    saveToLoadGame();

                    ///
                    saveToLeaderBoard();

                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, nextMap, 0);
                }
                if (_noBtn->isClicked(cursorPos)) {
                    // save game 

                    saveToLoadGame();

                    ///
                    saveToLeaderBoard();

                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                }
            }

            if (statePlayingGame == PAUSE)
            {
                if (_yesBtn->isClicked(cursorPos)) {
                    manager.setGameStatus(PLAY);
                    statePlayingGame = PLAY;

                    _ExitHouse->setEnabled(true);

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

            if (statePlayingGame == EXIT)
            {
                if (_yesBtn->isClicked(cursorPos)) {
                    manager.setGameStatus(PLAY);
                    statePlayingGame = PLAY;

                    if (manageFirstTime) manageFirstTime = false;
                    _pause->setEnabled(true);

                    _exitBoard->setTriger(false);
                    _noBtn->setTriger(false);
                    _yesBtn->setTriger(false);
                }
                if (_noBtn->isClicked(cursorPos)) {

                    // save game

                    int mapCode = getCurrentMap();

                    saveToLoadGame();
                    ///
                    saveToLeaderBoard();
                    
                    // trở về home
                    PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
                }
            }

            // handle mấy cái riêng
             //OutputDebugStringA("handleSpecificInput 2\n");
        }
        
        void update(float delta)
        {
            if (statePlayingGame == EXIT) {
                _exitBoard->setTriger(true);
            }


            if (statePlayingGame != PLAY) return;


            curHealth = manager.enemyManager.getUserHP();
      
            
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

                manager.enemyManager.setNOfPhase(3);
                OutputDebugStringA(("hahahahahahahha:" + to_string(manager.enemyManager.getNOfPhase()) + "\n").c_str());

                //setup enemy for each phase
                for (size_t e = 1; e <= 3; e++)
                {
                    int typeEnemy = e;

                    // Đổi style enemy Goblin đi bộ thành Goblin bơi
                    if(e == 1 && getCurrentMap() == 4) 
					    typeEnemy = 4;
                    // Đổi enemy 3 -> goblin khi ở map 1
                    if (e == 3 && getCurrentMap() == 1)
                        typeEnemy = 5;

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

                // get enemy element
                int nOfPhase = game_saving.getNOfPhase();
                vector<int> nOfEnemyEachPhase = game_saving.getNOfEnemyEachPhase();
                int remainEnemy = game_saving.getRemainEnemy();
                int nOfEnemy = game_saving.getNOfEnemy();
                int phase = game_saving.getPhase();
                int spawnedEnemy = game_saving.getSpawnedEnemy();
                
                // get all tower element 
                vector<cpoint> towerPos = game_saving.getTowerPos();
                vector<int> towerType = game_saving.getTowerType();
                int towerCount = towerPos.size();
              
                // set all manager element 
                manager.enemyManager.setNOfPhase(nOfPhase);
                manager.enemyManager.setNOfEnemyEachPhase(nOfEnemyEachPhase);
                manager.enemyManager.setRemainEnemy(remainEnemy);
                manager.enemyManager.setNOfEnemy(nOfEnemy);
                manager.enemyManager.setPhase(phase); 
                manager.enemyManager.setSpawnedEnemy(spawnedEnemy);

                // update enemy state
                vector<shared_ptr<EnemyBase>> listEnemy(enemyCount);
                for (int i = 0; i < enemyCount; i++) {
                    listEnemy[i] = EnemyFactory::createEnemy(enemyType[i], enemyPathNumber[i]);
                }
                for (int i = 0; i < enemyCount; i++) {
                    listEnemy[i]->setCurrentPosition(enemyPos[i]);
                    listEnemy[i]->setIndex(enemyIndex[i]);
                    listEnemy[i]->setHealth(enemyHealth[i]);
                }
                manager.enemyManager.setLoadEnemy(listEnemy);


                // update tower state
                for (int i = 0; i < towerCount; i++) {
                    manager.towerManager.addTower(TowerFactory::createTower(towerType[i], towerPos[i]));
                }
                
                vector<shared_ptr<TowerBase>> listTower(towerCount);
                
                for (int i = 0; i < towerCount; i++) {
                    listTower[i] = TowerFactory::createTower(towerType[i], towerPos[i]);
                }
                
                for (int i = 0; i < towerCount; i++) {
                    listTower[i]->setCurrentPosition(towerPos[i]);
                }

                manager.towerManager.setLoadTower(listTower);

                int point = game_saving.getPoint();
                int health = game_saving.getUserHealth();

                manager.setPoint(point);
                manager.enemyManager.setUserHP(health); 

                // Debug output
                /*std::ostringstream debugMessage;
                debugMessage << "File reddddddddddddddddđ: " << "filename" << "\n"
                    << "2. Points: " << point << "\n"
                    << "3. User Health: " << health << "\n"
                    << "5. Enemy Count: " << enemyCount << "\n"
                    << "6. Enemy Health: [ ";
                for (const auto& health : enemyHealth) debugMessage << health << " ";
                debugMessage << "]\n"
                    << "7. Enemy Path: [ ";
                for (const auto& path : enemyPathNumber) debugMessage << path << " ";
                debugMessage << "]\n"
                    << "8. Enemy Index: [ ";
                for (const auto& index : enemyIndex) debugMessage << index << " ";
                debugMessage << "]\n"
                    << "9. Enemy Type: [ ";
                for (const auto& type : enemyType) debugMessage << type << " ";
                debugMessage << "]\n"
                    << "10. Tower Count: " << towerCount << "\n"
                    << "11. Tower Type: [ ";
                for (const auto& type : towerType) debugMessage << type << " ";
                debugMessage << "]\n"
                    << "12. Number of Phases: " << nOfPhase << "\n"
                    << "13. Enemies Each Phase: [ ";
                for (const auto& count : nOfEnemyEachPhase) debugMessage << count << " ";
                debugMessage << "]\n"
                    << "14. Current Phase: " << phase << "\n"
                    << "15. Remaining Enemies: " << remainEnemy << "\n"
                    << "16. Total Enemies: " << nOfEnemy << "\n"
                    << "17. Spawned Enemies: " << spawnedEnemy << "\n";

                OutputDebugStringA(debugMessage.str().c_str());*/
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

            // ---------------------- SCORE GAME -------------------------------------
            _scoreBoard->render(hdc);
            string scoreStr = "Score: " + to_string(manager.getPoint());
            _scoreGame = make_shared<TextElement>(Utils::stringToWstring(scoreStr), boldFont, RGB(255, 255, 255), scorePos);

            _scoreGame->render(hdc);

            // =========================================================================


            // nếu được nhấn thì đổi trạng thái
            //if (_playOrPause->getTriger()) {
            //    // đổi trạng thái 1
            //    _playOrPause->render(hdc);
            //}
            //else {
            //    // đôi trạng thái 2
            //    _playOrPause->render(hdc);
            //}

            if (statePlayingGame == PLAY || statePlayingGame == WIN || statePlayingGame == LOSE || statePlayingGame == EXIT) {
                _pause->render(hdc);
            }
            else if (statePlayingGame == PAUSE) {
                _play->render(hdc);
            }

            _ExitHouse->render(hdc);

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

            if (_exitBoard->getTriger()) {
                _exitBoard->render(hdc);
                _noBtn->render(hdc);
                _yesBtn->render(hdc);
            }

            for (int i = 0; i < curHealth; i++) {
                _health->setPosition({ i * 25 + firstHealthPos.x + 35, firstHealthPos.y + 10 });
                _health->render(hdc);
            }

        }

        // ------ END RENDER -----
        bool checkValidPos(POINT cursurPos) {
            if (_towerInitPlace->isHovered(cursurPos)) {
                return false;
            }
            if (_play->isHovered(cursurPos)) {
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
            
            int nOfPhase = manager.enemyManager.getNOfPhase();
            vector<int> nOfEnemyEachPhase = manager.enemyManager.getNOfEnemyEachPhase();
            int remainEnemy = manager.enemyManager.getRemainEnemy();
            int nOfEnemy = manager.enemyManager.getNOfEnemy();
            int phase = manager.enemyManager.getPhase();
            int spawnedEnemy = manager.enemyManager.getSpawnedEnemy();

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

            SaveGame game_to_save
            (
                name,

                enemyPos,
                enemyHealth,
                enemyPathNumber,
                enemyIndex,
                enemyType,

                towerPos,
                towerType,

                nOfPhase,
                nOfEnemyEachPhase,
                phase,
                remainEnemy,
                nOfEnemy,
                spawnedEnemy,

                point,
                mapCode,
                health
            ); 


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
