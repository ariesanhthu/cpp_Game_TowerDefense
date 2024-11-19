#include "game.h"

namespace towerdefense {

    Game::Game() {
        hInstance = GetModuleHandle(NULL);
        windowTitle = L"Tower Defense";
    }

    Game::~Game() {
        delete menu;
        // Cleanup resources
        // xử lý những dữ liệu còn thừa
        // menu đã được destructor nhờ ~menu nên không cần gọi ở đây
    }

    // khởi tạo static
    int Game::ScreenCode = MENU;

    Game& Game::getInstance() {
        static Game instance;
        return instance;
    }

    void Game::start() {
        getInstance().startWindow();
    }

    void Game::setWindowProperties(const std::wstring& title, int width, int height) {
        getInstance().windowTitle = title;
        getInstance().windowWidth = width;
        getInstance().windowHeight = height;
    }

    LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_CREATE:
            Game::getInstance().menu = new Menu();

            RECT rect;
            GetClientRect(hwnd, &rect);
            Game::getInstance().menu->setWindowRect(rect);

            Game::getInstance().loadResources();
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Game::getInstance().render(hdc);
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void Game::startWindow() {
        const wchar_t* className = L"towerdefense_window";

        WNDCLASS windowClass = {};
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WindowCallback;
        windowClass.hInstance = hInstance;
        windowClass.lpszClassName = className;

        if (!RegisterClass(&windowClass)) {
            OutputDebugString(L"Failed to register window class\n");
            return;
        }

        windowHandle = CreateWindowEx(
            0,
            className,
            windowTitle.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            windowWidth,
            windowHeight,
            0,
            0,
            hInstance,
            0
        );

        if (!windowHandle) {
            OutputDebugString(L"Failed to create a window\n");
            return;
        }

        running = true;

        MSG message;
        while (running) {
            while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
                if (message.message == WM_QUIT) {
                    running = false;
                }
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
    }

    void Game::loadResources() {

        // ở screen nào thì load screen đó

        switch (ScreenCode) {
        case MENU: 
            menu->loadResources();
            break;
        case LOGIN: 
            // login loading
            break;
        case MAP1: 
            // map1 load
            break;
        }
    }

    void Game::render(HDC hdc) {

        // ở screen nào thì vẽ screen đó

        switch (ScreenCode) {
        case MENU:
            menu->render(hdc);
            break;
        case LOGIN:
            // login render
            break;
        case MAP1:
            // map1 render
            break;
        }
    }
}
