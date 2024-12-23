#include "MainScreen.h"

using namespace std;

namespace towerdefense
{
	// --------------------------------------------------
    //auto& audioManager = 
	// --------------------------------------------------
    
    // Constructor
    MainScreen::MainScreen() {
        loadContent(1280, 720);
        // -------------------------------------------------
        // dum 
   /*     auto& leaderBoard = Leaderboard::getInstance();
        User user1("guess", 100);
        User user2("guess2", 10);
        leaderBoard.addUser(user1);
        leaderBoard.addUser(user2);*/
        // -------------------------------------------------


        // ------------- HOW TO PLAY ---------------------- 
        //_boardHowToPlay = std::make_shared<Item>(L"Assets/game/info/howtoplay.png", 2, boardHowtoPlayPos);
        _boardHowToPlay = std::make_shared<Popup>(L"Assets/game/info/howtoplay.png", 1, initpoint, endpoint);
        
        auto& gameManager = GameManager::getInstance();

        if (!gameManager.isFirstStartGame())
        {
            _boardHowToPlay->setTriger(true);
            gameManager.setFirstStartGame(true);
        }
        // -----------------------------------------------

        customfont = FontManager::getInstance().getFont("normal");
        Titlefont = FontManager::getInstance().getFont("title");


        float scaleX = static_cast<float>(1280) / 395.0f;   // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(720) / 213.0f;    // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh 

        _background = std::make_shared<Item>(L"Assets/background/mainscreen.png", 1, 0, 0);
        _catfam = std::make_shared<Item>(L"Assets/decor/nameLogo.png", 2, 0, 0);

        _play = std::make_shared<Button>(L"Assets/button/btnPlay.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[0]);
        _cont = std::make_shared<Button>(L"Assets/button/btnContinue.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[1]);
        _lead = std::make_shared<Button>(L"Assets/button/btnLeaderboard.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[2]);
        _sett = std::make_shared<Button>(L"Assets/button/btnSetting.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[3]);
        _exit = std::make_shared<Button>(L"Assets/button/btnExit.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[4]);
        _about = std::make_shared<Button>(L"Assets/button/aboutBtn.png", L"Assets/button/selectbox.bmp", 2, buttonPositions[5]);

        popup = std::make_shared<Popup>(L"Assets/board/board.bmp", 3, initpoint, endpoint);

        _map1 = std::make_shared<Button>(L"Assets/map_resize/map1_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsEnd[0]);
        _map2 = std::make_shared<Button>(L"Assets/map_resize/map2_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsEnd[1]);
        _map3 = std::make_shared<Button>(L"Assets/map_resize/map3_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsEnd[2]);
        _map4 = std::make_shared<Button>(L"Assets/map_resize/map4_scaleDown.bmp", L"Assets/board/border.bmp", 3, optionPositionsEnd[3]);

        _login = std::make_shared<Button>(L"Assets/button/LoginBtn.png", L"Assets/button/selectBox2.bmp", 2, loginPosition);
        _inputName = std::make_shared<InputElement>(L"Name", inputNamePosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);
        _inputPassword = std::make_shared<InputElement>(L"Password", inputPasswordPosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);

        _register = std::make_shared<Button>(L"Assets/button/LoginBtn.png", L"Assets/button/selectBox2.bmp", 2, registerPosition);
        _inputNameReg = std::make_shared<InputElement>(L"Name", inputNamePosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);
        _inputPasswordReg = std::make_shared<InputElement>(L"Password", inputPasswordPosition, customfont, RGB(255, 255, 255), L"Assets/button/input.bmp", 5);

        _gotoPage = std::make_shared<TextElement>(L"Goto Register Form", customfont, RGB(255, 255, 255), linkPos);

        //  ----------- setting -----------
        TitleSetting = std::make_shared<TextElement>(L"SETTING", Titlefont, RGB(255, 255, 255), titlePos);

        // Thanh âm lượng
        _VolumeBar = std::make_shared<Item>(L"Assets/setting/volumn.png", 6, VolumeBarPos);
        _VolumeBarOn = std::make_shared<Item>(L"Assets/setting/volumnOn.png", 6, VolumeBarOnPos);

        // Loa
        _audioOffItem = std::make_shared<Item>(L"Assets/setting/sound_off.png", 2, audioItemPos);
        _audioItem = std::make_shared<Item>(L"Assets/setting/sound_on.png", 2, audioItemPos);

        // BẬT TẮT ÂM THANH
        //_switchAudio = std::make_shared<Button>(L"Assets/setting/switchOff.png", L"Assets/setting/switchOff.png", L"Assets/setting/switchOn.png", 3, switchAudioPos);
        _switchOffAudio = std::make_shared<Item>(L"Assets/setting/switchOff.png", 3, switchAudioPos);
        _switchOnAudio = std::make_shared<Item>(L"Assets/setting/switchOn.png", 3, switchAudioPos);


        /*
            TẠO CLASS xử lý riêng các button

            hoặc thêm trạng thái enableHover (có hiệu ứng hover hay không)

        */
        _arrowUpButton = std::make_shared<Button>(L"Assets/setting/arrowUp.png", L"Assets/button/select.bmp", 5, arrowUpPos);
        _arrowDownButton = std::make_shared<Button>(L"Assets/setting/arrowDown.png", L"Assets/button/select.bmp", 5, arrowDownPos);



		// -------------------------------------------


        for (int i = 0; i < _FourContinueItem.size(); i++) {

            wstring name = Utils::stringToWstring(LoadList[i].getUserName());
            wstring point = Utils::stringToWstring(std::to_string(LoadList[i].getPoint()));
            wstring level = Utils::stringToWstring(std::to_string(LoadList[i].getMapCode()));

            /*std::wstring allias = L"Assets/map_resize/map" + to_wstring(i) + L"_scaleDown.bmp";
            const wchar_t* mapLink = Utils::wstringToWchar_t(allias);*/

            _FourContinueItem[i] = std::make_shared<ContinueElement>(name, point, level, optionPositionsEnd[i], customfont, RGB(255, 255, 255), maplink[LoadList[i].getMapCode()], 3);
            _FourContinueItem[i]->setTriger(false);
        }

        _map1->setTriger(false);



    }

    // Destructor
    MainScreen::~MainScreen() {
        // Giải phóng tài nguyên
        //DeleteObject(customfont);
        //DeleteObject(Titlefont);
		/*TitleSetting.reset();*/
        OutputDebugStringA("~MainScreen\n");
    }
    int MainScreen::menu = 0;

    void MainScreen::loadContent(int width, int height) {
        // Tính toán tỉ lệ dựa trên kích thước màn hình
        //float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        //float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        //float scale  = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh     

        buttonPositions = {
            {1280 / 11 * 1, 720 * 7 / 10},   // Play button
            {1280 / 11 * 3, 720 * 7 / 10},   // Pause button
            {1280 / 11 * 5, 720 * 7 / 10},   // Trophy button
            {1280 / 11 * 7, 720 * 7 / 10},   // Settings button
            {1280 / 11 * 9, 720 * 7 / 10},   // Exit button
            {1280 / 11 * 10, 720 * 7 / 100 + 10}   // about us
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


        //listGame = supSaveGame->readfile();
        LoadList = supSaveGame->loadFourLastestMapGame();

        //OutputDebugStringA((to_string(LoadList.size()) + "load list size\n").c_str());

        LeaderboardList = supSaveGame->loadFourLastestMapGame();

        //OutputDebugStringA((to_string(LoadList.size()) + "leaderboard size\n").c_str());

        _FourContinueItem.resize(LoadList.size());
        _FourLeaderBoardItem.resize(LeaderboardList.size());
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
                
                // ----------------------------------------------------
                if (_boardHowToPlay->getTriger()) {
                    if (!_boardHowToPlay->isHoverInside(cursorPos)) {
                        menu = 0;
                        _boardHowToPlay->setTriger(false);
                    }
                }
                // ----------------------------------------------------
                
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
                    }
                    else if (_cont && _cont->isHoverInside(cursorPos)) {
                        menu = 2;
                        popup->setTriger(true);
                        for (auto i : _FourContinueItem) {
                            i->setTriger(true);
                        }
                    }
                    else if (_lead && _lead->isHoverInside(cursorPos)) {
                        menu = 3;
                        popup->setTriger(true);

                        // ----------------------- LEADER BOARD -------------------------------
                        auto& leaderBoard = Leaderboard::getInstance();
                        leaderBoard.loadLeaderBoard();
                        // ----------------------- LEADER BOARD -------------------------------
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
                        _boardHowToPlay->setTriger(true);
                    }
                    else if (_login && _login->isHoverInside(cursorPos)) {
                        menu = 101;
                        popup->setTriger(true);
                    }
                }
            }
        }

        // ===============================================================================
        // nếu bật cờ popup thì popup
        
        // ------------------------------------------------------------------------
        if (_boardHowToPlay->getTriger() == true) _boardHowToPlay->startAnimation();
        else _boardHowToPlay->setPosition(initpoint);
        // ------------------------------------------------------------------------
        if (popup->getTriger() == true) popup->startAnimation();
        else popup->setPosition(initpoint);

        // ===============================================================================

        if (menu == 0) {

        }
        // -------------------------- choose map --------------------------
        else if (menu == 1) {
            if (_map1->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 1, 0);
            }
            else if (_map2->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 2, 0);
            }
            else if (_map3->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 3, 0);
            }
            else if (_map4->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 4, 0);
            }
        }
        // -------------------------- continue --------------------------
        else if (menu == 2) {
            for (int i = 0; i < LoadList.size(); i++) {
                if (_FourContinueItem[i]->isClicked(cursorPos)) {
                    PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, LoadList[i].getMapCode() + 4, 0);
                }
            }
        }
        // -------------------------- leaderboard --------------------------
        else if (menu == 3) {
            
        }
        // -------------------------- setting --------------------------
        else if (menu == 4) {
            if (_switchOffAudio->isClicked(cursorPos)) {
                // stop 
                if (AudioManager::getInstance().isBackgroundMusicPlaying) {
                    AudioManager::getInstance().stopBackgroundMusic();
                    AudioManager::getInstance().isBackgroundMusicPlaying = false;
                }
                // play
                else {
                    AudioManager::getInstance().playBackgroundMusic();
                    AudioManager::getInstance().isBackgroundMusicPlaying = true;
                }
            }

            if (_arrowDownButton->isClicked(cursorPos)) {
                AudioManager::getInstance().adjustMusicVolume(-0.1f);
            }

            if (_arrowUpButton->isClicked(cursorPos)) {
                AudioManager::getInstance().adjustMusicVolume(0.1f);
            }
        }
        // -------------------------- exit --------------------------
        else if (menu == 5) {
            PostQuitMessage(0);
        }
        else if (menu == 6) {

        }
        // -------------------------- login --------------------------
        else if (menu == 101) {
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

            // Nếu nhấn enter
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                    lastMouseClickTime = now;

                    // login
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

        // ---------------------------------------------------------
        if (_boardHowToPlay && !_boardHowToPlay->isFinished())
        {
            _boardHowToPlay->update(delta);
        }
        // ---------------------------------------------------------

        if (popup && !popup->isFinished()) {
            popup->update(delta);
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

        // -------------------------------------------------------------
        // ĐỂ TẠM THỜI
        if (AudioManager::getInstance().isBackgroundMusicPlaying)
        {
            _audioItem->setTriger(true);
            _audioOffItem->setTriger(false);

            _switchOnAudio->setTriger(true);
            _switchOffAudio->setTriger(false);
        }
        else
        {
            _audioOffItem->setTriger(true);
            _audioItem->setTriger(false);

            _switchOnAudio->setTriger(false);
            _switchOffAudio->setTriger(true);
        }
        // -----------------------------------------------------------------

        if (menu == 0) {

        }
        else {
            if (popup->isFinished()) {
                if (menu == 1) {
                    if (_map1->getTriger()) {
                        _map1->render(hdc);
                        _map2->render(hdc);
                        _map3->render(hdc);
                        _map4->render(hdc);
                    }
                }
                else if (menu == 2) {
                    
                    for (auto i : _FourContinueItem) {
                        if (i->getTriger()) {
                            i->render(hdc);
                        }
                    }

        }
        else if (menu == 3) {
            /*for (auto i : _FourLeaderBoardItem) {
                i->render(hdc);
            }*/
            auto& leaderBoard = Leaderboard::getInstance();
            leaderBoard.render(hdc);
        }
        else if (menu == 4) {

                    //_VolumeButton->render(hdc);
                    TitleSetting->render(hdc);

                    if (_audioItem->getTriger())
                        _audioItem->render(hdc);

                    if (_audioOffItem->getTriger())
                        _audioOffItem->render(hdc);

                    //_switchAudio->render(hdc);
                    if (_switchOnAudio->getTriger())
                        _switchOnAudio->render(hdc);

                    if (_switchOffAudio->getTriger())
                        _switchOffAudio->render(hdc);

                    _VolumeBar->render(hdc);
                    _arrowUpButton->render(hdc);
                    _arrowDownButton->render(hdc);

                    // bar volume
                    // Số thanh trạng thái bật (từ 0 đến 9)
                    int activeBars = static_cast<int>(AudioManager::getInstance().getMusicVolume() * 10);
                    shared_ptr<Item> volumeOn = make_shared<Item>(L"Assets/setting/volumnOn.png", 6, VolumeBarOnPos);
                    for (int i = 0; i < activeBars; ++i)
                    {
                        // Điều chỉnh vị trí từng thanh (giả định thanh cách nhau 20px theo trục x)
                        volumeOn->setPosition({ VolumeBarOnPos.x + i * 30, VolumeBarOnPos.y });

                        volumeOn->render(hdc);
                    }

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

        }
        // HOW TO PLAY
        auto& gameManager = GameManager::getInstance();
        if (!gameManager.isFirstStartGame() || _boardHowToPlay->getTriger())
        {

            //gameManager.setFirstStartGame(true);
            _boardHowToPlay->render(hdc);

        }
            
        // ---------------------------
    }//
}//