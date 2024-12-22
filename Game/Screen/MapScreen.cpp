//#include "MapScreen.h"
//
//namespace towerdefense {
//
//    bool MapScreen::isInRange(POINT pos, int range) {
//        return range < sqrt((pos.x * pos.x + pos.y * pos.y));
//    }
//    // ----------------------------------------------------------------------------------------------------------------------
//    /*void MapScreen::loadContent(int width, int height)
//    {*/
//        /* _towerInitPlace = std::make_shared<Item>(L"Assets/game/BoardSetupTower.png", 1.5f, towerInitPos);
//         _hamburger = std::make_shared<Button>(L"Assets/button/aboutBtn.png", L"Assets/button/selectbox.bmp", 2, hamburgerPos);
//         _playOrPause = std::make_shared<Button>(L"Assets/button/btnPlay.png", L"Assets/button/selectbox.bmp", 2, posbuttonplay);
//
//         _yesnoBoard = std::make_shared<Item>(L"Assets/board/board.bmp", 1.5, boardYesNoPos);
//         _yesBtn = std::make_shared<Button>(L"Assets/button/AcceptBtn.png", L"Assets/button/selectbox.bmp", 3, yesBtnPos);
//         _noBtn = std::make_shared<Button>(L"Assets/button/RejectBtn.png", L"Assets/button/selectbox.bmp", 3, noBtnPos);
//
//         _loseBoard = std::make_shared<Item>(L"Assets/board/board.bmp", 1.5, boardYesNoPos);
//         _winBoard = std::make_shared<Item>(L"Assets/board/board.bmp", 1.5, boardYesNoPos);
//
//         pickedTowerType1 = TowerFactory::createTower(0, { Turretinit.x, Turretinit.y, 0 });
//         renderTowerType1 = TowerFactory::createTower(0, { Turretinit.x, Turretinit.y, 0 });*/
//
//         // Gọi hàm riêng (abstract)
//         //loadSpecificContent(width, height);
//    //}
//
//    // ----------------------------------------------------------------------------------------------------------------------
//    //void MapScreen::handleInput(HWND hwnd)
//    //{
//    //    // Lấy tọa độ con trỏ chuột
//    //    POINT cursorPos;
//    //    GetCursorPos(&cursorPos);
//    //    ScreenToClient(GetActiveWindow(), &cursorPos);
//    //
//    //    static bool isMousePressed = false;   // Trạng thái chuột trái được nhấn
//    //    static bool isPicking = false;        // Tháp đang được nhấc lên
//    //    static bool isPickedFromInitPos = false; // Tháp nhấc từ initPos
//    //
//    //    // Kiểm tra chuột trái được nhấn
//    //    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
//    //        if (!isMousePressed) { // Chỉ xử lý 1 lần khi chuột nhấn xuống
//    //            isMousePressed = true;
//    //
//    //            // Xử lý nút PLAY/PAUSE
//    //            if (_playOrPause->isClicked(cursorPos)) {
//    //                if (manageFirstTime) {
//    //                    statePlayingGame = PLAY; // Bắt đầu chơi
//    //                    manageFirstTime = false;
//    //                }
//    //            }
//    //
//    //            // Xử lý nút HAMBURGER để mở/đóng instruction board
//    //            if (_hamburger->isClicked(cursorPos)) {
//    //                bool currentTrigger = _instructionboard->getTriger();
//    //                _instructionboard->setTriger(!currentTrigger);
//    //            }
//    //
//    //            // Kiểm tra click vào tháp tại vị trí initPos
//    //            if (renderTowerType1->isHovered(cursorPos)) {
//    //                isPicking = true;          // Bắt đầu nhấc tháp
//    //                isPickedFromInitPos = true; // Đánh dấu nhấc từ vị trí initPos
//    //            }
//    //        }
//    //    }
//    //    else
//    //        /*
//    //                    PICKING TOWER
//    //        */
//    //    { // Xử lý khi chuột trái được thả
//    //        if (isPicking && isPickedFromInitPos) {
//    //            isPicking = false;       // Kết thúc trạng thái nhấc tháp
//    //            isPickedFromInitPos = false;
//    //
//    //            // Thêm tháp mới vào TowerManager tại vị trí con trỏ chuột
//    //            if (checkValidPos(cursorPos)) {
//    //                manager.towerManager.addTower(
//    //                    TowerFactory::createTower(1, { cursorPos.x, cursorPos.y, 0 })
//    //                );
//    //            }
//    //
//    //            // Đặt tháp được nhấc trở về vị trí ban đầu
//    //            pickedTowerType1->setCurrentPosition({ Turretinit.x, Turretinit.y, 0 });
//    //        }
//    //
//    //        isMousePressed = false; // Reset trạng thái chuột
//    //    }
//    //
//    //    // Nếu đang nhấc tháp, cập nhật vị trí tháp theo tọa độ chuột
//    //    if (isPicking) {
//    //        pickedTowerType1->setCurrentPosition({ cursorPos.x, cursorPos.y, 0 });
//    //    }
//    //    //--------------------------------------------------------------------------
//    //
//    //    /*
//    //        GIỐNG NHAU GIỮA CÁC SCREEN -> STATE
//    //    */
//    //    if (statePlayingGame == LOSE) {
//    //        if (_yesBtn->isClicked(cursorPos)) {
//    //            PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
//    //        }
//    //        if (_noBtn->isClicked(cursorPos)) {
//    //            // save game 
//    //            PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
//    //        }
//    //    }
//    //
//    //    if (statePlayingGame == WIN) {
//    //        if (_yesBtn->isClicked(cursorPos)) {
//    //
//    //            // qua man tiep theo, hien tai de reload map
//    //
//    //            PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
//    //        }
//    //        if (_noBtn->isClicked(cursorPos)) {
//    //            // save game 
//    //            PostMessageA(hwnd, WM_CUSTOM_LOAD_SCREEN, 0, 0);
//    //        }
//    //    }
//    //    // -------------------------------------
//    //    //handleSpecificInput(hwnd);
//    //}
//
//    // ----------------------------------------------------------------------------------------------------------------------
//
//    //void MapScreen::update(float delta)
//    //{
//        //if (statePlayingGame != PLAY) return;
//
//        ////----------- WIN GAME -----------
//        //if (manager.gameStatus == WIN) {
//        //    statePlayingGame = WIN;
//
//        //    _winBoard->setTriger(true);
//        //}
//        ////----------- LOSE GAME -----------
//        //else if (manager.gameStatus == LOSE) {
//        //    statePlayingGame = LOSE;
//
//        //    _loseBoard->setTriger(true);
//
//        //}
//        ////----------- PLAY GAME -----------
//        //else if (manager.gameStatus == PLAY) {
//        //    //OutputDebugStringA("11111111111111111\n");
//        //    manager.update(delta);
//        //    statePlayingGame = PLAY;
//        //}
//        ////----------- PAUSE GAME -----------
//        //else if (manager.gameStatus == PAUSE) {
//        //    // ........
//        //}
//
//        ////manager.update(delta);
//
//        //updateSpecific(delta);
//    //}
//
//    // ----------------------------------------------------------------------------------------------------------------------
//    //
//    //void MapScreen::render(HDC hdc)
//    //{
//    //    renderCommonElements(hdc);
//    //
//    //    //renderSpecific(hdc);
//    //}
//
//    // ----------------------------------------------------------------------------------------------------------------------
//
//    // ======================================================================================================================
//    // CÁC HÀM PHỤ DÙNG CHUNG
//    // ======================================================================================================================
//
//    void MapScreen::GamePlaySetup()
//    {
//        manager.setup(path);
//
//        int nofpath = path.size();
//
//        manager.enemyManager.setup(mapSetup);
//
//        // setup enemy for each phase
//        // For: enemy type
//            // For: số lượng enemy
//
//        for (int e = 1; e <= 3; e++)
//            for (int i = 0; i < mapSetup[e]; i++)
//                manager.enemyManager.addEnemy(EnemyFactory::createEnemy(e, rand() % nofpath));
//    }
//
//    void MapScreen::renderCommonElements(HDC hdc) {
//        _background->render(hdc);
//        _hamburger->render(hdc);
//        _towerInitPlace->render(hdc);
//
//        if (_instructionboard->getTriger()) {
//            _instructionboard->render(hdc);
//        }
//
//        if (_yesnoBoard->getTriger()) {
//            _yesnoBoard->render(hdc);
//            _noBtn->render(hdc);
//            _yesBtn->render(hdc);
//        }
//
//        if (_loseBoard->getTriger()) {
//            _loseBoard->render(hdc);
//            _noBtn->render(hdc);
//            _yesBtn->render(hdc);
//        }
//
//        if (_winBoard->getTriger()) {
//            _winBoard->render(hdc);
//            _noBtn->render(hdc);
//            _yesBtn->render(hdc);
//        }
//
//        pickedTowerType1->render(hdc);
//        renderTowerType1->render(hdc);
//        manager.render(hdc);
//
//        _playOrPause->render(hdc);
//    }
//    bool MapScreen::checkValidPos(POINT cursurPos) {
//        if (_towerInitPlace->isHovered(cursurPos)) {
//            return false;
//        }
//        return true;
//    }
//}