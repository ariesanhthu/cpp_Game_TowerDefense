#include "MainScreen.h"

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

        _background = std::make_shared<Item>(L"Assets/background/mainscreen.png", 1, 0, 0);
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
            else if (_map3->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 3, 0);
            }
            else if (_map4->isClicked(cursorPos)) {
                PostMessage(hwnd, WM_CUSTOM_LOAD_SCREEN, 4, 0);
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

                     //login
					std::string name = utils.wstringToString(_inputName->getText());
					std::string password = utils.wstringToString(_inputPassword->getText());

                    if (userManager.login(name, password)) {
						// token bây giờ sẽ khác nullptr
						// show mess thành công
                    }
                    else {
                        // show mess thất bại
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
}