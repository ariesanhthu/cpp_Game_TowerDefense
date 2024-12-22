#include "game.h"

namespace towerdefense
{
    //==========================================================
    // CALLBACK
    //==========================================================
    // Hàm xử lý các sự kiện của cửa sổ (Windows message)
    LRESULT CALLBACK WindowCallback(
        HWND windowHandle,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    ) {
        Graphic* graphic = nullptr;
       
        LRESULT result = 0; // Lưu kết quả trả về từ Windows

        switch (message)
        {
        case WM_CREATE: 
            graphic = new Graphic();

            Game::getInstance().loadInitialScreen(0);
        break;
        
        // Sự kiện đóng cửa sổ
        case WM_CLOSE: 
        {
            if (graphic) delete graphic;

            Game::getInstance().running = false; // Dừng game
            OutputDebugString(L"window close\n");
        } break;
        
        // Sự kiện hủy cửa sổ
        case WM_DESTROY:
        {

            if (graphic) delete graphic;

            // Dừng game
            Game::getInstance().running = false; 
            OutputDebugString(L"window destroy\n");
        } break;
        case WM_SIZE:
        {
            RECT rect;

            // đọc kích thước màn hình
            GetClientRect(windowHandle, &rect);

        }break;

        case WM_CUSTOM_LOAD_SCREEN:
        {
            int x = (int)wParam;
            Game::getInstance().loadInitialScreen(x);

        } break;

        case WM_SETCURSOR:
        {
            // Set the custom cursor
            SetCursor(Game::getInstance().hCustomCursor);
            return TRUE;
        } break;



        default:
            result = DefWindowProc(windowHandle, message, wParam, lParam); // Xử lý mặc định
        }
        return result;
    }

    //==========================================================
    // Constructor của lớp Game
    //==========================================================
    Game::Game() : hInstance(GetModuleHandle(NULL))
    {
        // Thiết lập các thuộc tính cửa sổ mặc định
        windowTitle = L"Cat-farm Tower Defense";
        windowWidth = 1280;
        windowHeight = 720;

        screenManager = std::make_shared<ScreenManager>(); 

        // Lấy kích thước cửa sổ hiện tại (nếu có)
        /*RECT rect;
        if (GetClientRect(GetActiveWindow(), &rect))
        {
            windowWidth = rect.right - rect.left;
            windowHeight = rect.bottom - rect.top;
        }*/
    }

    //==========================================================
    // Tạo cửa sổ game và bắt đầu vòng lặp game
    //==========================================================
    void Game::startWindow()
    {
        // Định nghĩa thông tin lớp cửa sổ
        const wchar_t* className = L"dewcin_window";
        WNDCLASS windowClass = {};
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WindowCallback; // Đăng ký hàm callback xử lý sự kiện
        windowClass.hInstance = hInstance;
        windowClass.lpszClassName = className;
        windowClass.hCursor = NULL;

        // Đăng ký lớp cửa sổ
        if (!RegisterClass(&windowClass))
        {
            OutputDebugString(L"Failed to register window class\n");
            return;
        }

        // Tạo cửa sổ
        windowHandle = CreateWindowEx(
            0,
            className,
            windowTitle.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Kiểu cửa sổ
            CW_USEDEFAULT,                    // Vị trí mặc định
            CW_USEDEFAULT,                    // Vị trí mặc định
            windowWidth,
            windowHeight,
            nullptr,
            0,
            hInstance,
            0
        );

        HBITMAP hBitmap = Graphic::LoadBitmapImage(L"Assets/mouse/mouse1.png", 2);

        ICONINFO iconInfo = { 0 };
        iconInfo.fIcon = FALSE;      // Set to FALSE to indicate a cursor
        iconInfo.xHotspot = 0;       // Adjust based on your desired hotspot
        iconInfo.yHotspot = 0;
        iconInfo.hbmMask = hBitmap;  // Use the same bitmap as a mask for simplicity
        iconInfo.hbmColor = hBitmap;

        hCustomCursor = CreateIconIndirect(&iconInfo);

        if (!hCustomCursor) {
            MessageBoxW(windowHandle, L"Failed to create custom cursor", L"Error", MB_OK);
        }

        if (windowHandle) // Kiểm tra nếu cửa sổ tạo thành công
        {
            OutputDebugString(L"GAME INIT\n");
            running = true;

            // Thiết lập clock để tính toán delta time (thời gian giữa hai frame)
            LARGE_INTEGER cpu_frequency;
            QueryPerformanceFrequency(&cpu_frequency);
            LARGE_INTEGER last_counter;
            QueryPerformanceCounter(&last_counter);

            while (running) // Vòng lặp game chính
            {
                // Tính delta time
                LARGE_INTEGER current_counter;
                QueryPerformanceCounter(&current_counter);
                int64_t counter_elapsed = current_counter.QuadPart - last_counter.QuadPart;
                float delta = (float)counter_elapsed / (float)cpu_frequency.QuadPart; // Thời gian giữa hai frame
                last_counter = current_counter;

                auto frameStart = std::chrono::high_resolution_clock::now();

                // Xử lý các sự kiện Windows
                MSG message;
                if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
                {
                    if (message.message == WM_QUIT)
                        running = false;
                    TranslateMessage(&message);
                    DispatchMessage(&message); // Gửi thông điệp đến WindowCallback
                }
                else
                {
                    auto start = std::chrono::high_resolution_clock::now();

                    HDC hdc = GetDC(windowHandle); // Lấy ngữ cảnh thiết bị từ cửa sổ
                    HDC bufferDC = CreateCompatibleDC(hdc); // Tạo DC tương thích để vẽ vào bộ đệm

                    // Tạo một bitmap để làm bộ đệm
                    RECT clientRect;
                    GetClientRect(windowHandle, &clientRect);
                    int width = clientRect.right - clientRect.left;
                    int height = clientRect.bottom - clientRect.top;

                    HBITMAP bufferBitmap = CreateCompatibleBitmap(hdc, width, height);
                    HBITMAP oldBitmap = (HBITMAP)SelectObject(bufferDC, bufferBitmap); // Gắn bitmap vào DC bộ đệm

                    // Xóa bộ đệm trước khi vẽ
                    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0)); // Màu nền (đen)
                    FillRect(bufferDC, &clientRect, brush);
                    DeleteObject(brush);

                    // Vẽ vào bộ đệm
                    // inputHadle
                    // update
                    // render
                    screenManager->handleInput(windowHandle);
                    screenManager->update(delta);  // Cập nhật logic của màn hình
                    screenManager->render(bufferDC); // Vẽ màn hình vào DC bộ đệm

                    // Copy nội dung từ bộ đệm ra màn hình
                    BitBlt(hdc, 0, 0, width, height, bufferDC, 0, 0, SRCCOPY);

                    // Giải phóng tài nguyên
                    SelectObject(bufferDC, oldBitmap);
                    DeleteObject(bufferBitmap);
                    DeleteDC(bufferDC);
                    ReleaseDC(windowHandle, hdc);

                    auto end = std::chrono::high_resolution_clock::now();
                    std::this_thread::sleep_for(std::chrono::milliseconds(16) - (end - start));
                }
            }
        }
        else
        {
            OutputDebugString(L"Failed to create a window\n");
        }
    }

    //==========================================================
    // Tách phần load screen
    //==========================================================
    void Game::loadInitialScreen(int x) {
        try {
            std::shared_ptr<Screen> screen = nullptr;

            if (x == 0) {
                screen = std::make_shared<MainScreen>();
            }
            else if (x >= 1 && x <= 4) {
                switch (x) {
                case 1: screen = std::make_shared<PlayScreen1>(); break;
                case 2: screen = std::make_shared<PlayScreen2>(); break;
                case 3: screen = std::make_shared<PlayScreen3>(); break;
                case 4: screen = std::make_shared<PlayScreen4>(); break;
                }
            }
            else if (x >= 5 && x <= 8) {
                // Load game screens with setLoadStatus(true)
                std::shared_ptr<MapScreen> gameScreen = nullptr;
                switch (x) {
                case 5: gameScreen = std::make_shared<PlayScreen1>(); break;
                case 6: gameScreen = std::make_shared<PlayScreen2>(); break;
                case 7: gameScreen = std::make_shared<PlayScreen3>(); break;
                case 8: gameScreen = std::make_shared<PlayScreen4>(); break;
                }
                if (gameScreen) {
                    gameScreen->setLoadStatus(true);
                    screen = gameScreen;
                }
            }
            else {
                OutputDebugStringA("Invalid screen index.\n");
                return;
            }

            if (screen) {
                screenManager->changeScreen(screen);
                screenManager->loadContent(windowWidth, windowHeight);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

}
