#include "game.h"
#include "input.h"
#include "ScreenManager.h"
#include <chrono>
#include <thread>

namespace towerdefense
{
    //==========================================================
    // CALLBACK
    //==========================================================
    // Hàm xử lý các sự kiện của cửa sổ (Windows message)
    HWND g_hwnd = nullptr;

    LRESULT CALLBACK WindowCallback(
        HWND windowHandle,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    )
    {
        LRESULT result = 0; // Lưu kết quả trả về từ Windows
        switch (message)
        {
        case WM_CREATE: 
            g_hwnd = windowHandle;
            Game::getInstance().loadInitialScreen(0);
        break;
        case WM_CLOSE: // Sự kiện đóng cửa sổ
        {
            Game::getInstance().running = false; // Dừng game
            OutputDebugString(L"window close\n");
        } break;
        case WM_DESTROY: // Sự kiện hủy cửa sổ
        {
            Game::getInstance().running = false; // Dừng game
            OutputDebugString(L"window destroy\n");
        } break;
        case WM_SIZE:
        {
            RECT rect;

            // đọc kích thước màn hình
            GetClientRect(windowHandle, &rect);

        }break;
        case WM_PAINT: // Sự kiện vẽ lại cửa sổ
        {
            OutputDebugString(L"window paint\n");

            PAINTSTRUCT paint;
            HDC device_context = BeginPaint(windowHandle, &paint); // Bắt đầu vẽ

            // Vẽ nội dung game trực tiếp lên cửa sổ
            Game::getInstance().screenManager.render(device_context);

            EndPaint(windowHandle, &paint); // Kết thúc vẽ
        } break;

        case WM_CUSTOM_LOAD_SCREEN:
        {
            int x = (int)wParam;
            Game::getInstance().loadInitialScreen(x);

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
            CW_USEDEFAULT,                   // Vị trí mặc định
            CW_USEDEFAULT,                   // Vị trí mặc định
            windowWidth,
            windowHeight,
            nullptr,
            0,
            hInstance,
            0
        );

        const int FPS = 60;
        const int frameDelay = 1000 / FPS;

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
                    screenManager.handleInput(g_hwnd);
                    screenManager.update(delta);  // Cập nhật logic của màn hình
                    screenManager.render(bufferDC); // Vẽ màn hình vào DC bộ đệm

                    // Copy nội dung từ bộ đệm ra màn hình
                    BitBlt(hdc, 0, 0, width, height, bufferDC, 0, 0, SRCCOPY);

                    // Giải phóng tài nguyên
                    SelectObject(bufferDC, oldBitmap);
                    DeleteObject(bufferBitmap);
                    DeleteDC(bufferDC);
                    ReleaseDC(windowHandle, hdc);

                    auto frameEnd = std::chrono::high_resolution_clock::now();
                    auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();

                    if (frameDelay > frameTime) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - frameTime));
                    }
                    // inputHadle
                    // update
                    // render
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
    void Game::loadInitialScreen(int x)
    {
        // Tạo màn hình chính
        

        //std::shared_ptr<Screen> newscreen = std::make_shared<MainScreen>();
        std::shared_ptr<Screen> newscreen;

        switch (x)
        {
        case 0:
        {
            newscreen = std::make_shared<MainScreen>();
        }
        case 1:
        {
            newscreen = std::make_shared<PlayScreen>();
        }
        default:
            break;
        }

        screenManager.changeScreen(std::move(newscreen));
        screenManager.loadContent(windowWidth, windowHeight);
        

        // Tải nội dung màn hình chính
        //currentScreen->loadContent(graphic, windowWidth, windowHeight);
    }
}
