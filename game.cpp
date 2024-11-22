#include "game.h"
#include "input.h"
#include "ScreenManager.h"

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
    )
    {
        LRESULT result = 0; // Lưu kết quả trả về từ Windows
        switch (message)
        {
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
        case WM_KEYDOWN: // Phím được nhấn
        case WM_KEYUP:   // Phím được nhả
        {
            uint32_t VKCode = wParam; // Mã phím
            bool wasDown = (lParam & (1 << 30)) != 0; // Kiểm tra trạng thái phím
            bool isDown = (lParam & (1 << 31)) == 0;
            Input::processKeyboardInput(VKCode, wasDown, isDown); // Xử lý phím
        } break;
        case WM_SIZE:
        {
            RECT rect;

            // đọc kích thước màn hình
            GetClientRect(windowHandle, &rect);

            //// tính toán buffer
            /*Game::windowWidth = rect.right - rect.left;
            Game::windowHeight = rect.bottom - rect.top;*/

        }break;
        case WM_PAINT: // Sự kiện vẽ lại cửa sổ
        {
            OutputDebugString(L"window paint\n");

            PAINTSTRUCT paint;
            HDC device_context = BeginPaint(windowHandle, &paint); // Bắt đầu vẽ

            // Vẽ nội dung game trực tiếp lên cửa sổ
            Game::getInstance().currentScreen->render(device_context);

            EndPaint(windowHandle, &paint); // Kết thúc vẽ
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
            0,
            0,
            hInstance,
            0
        );

        if (windowHandle) // Kiểm tra nếu cửa sổ tạo thành công
        {
            OutputDebugString(L"GAME INIT\n");
            running = true;

            //==========================================================
            // Tách phần load screen vào hàm riêng
            loadInitialScreen(); // Gọi hàm tách code (xem định nghĩa bên dưới)
            //==========================================================

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
                    // Cập nhật và vẽ màn hình hiện tại
                    currentScreen->update(delta); // Cập nhật logic của màn hình
                    HDC hdc = GetDC(windowHandle); // Lấy ngữ cảnh thiết bị để vẽ
                    currentScreen->render(hdc);   // Vẽ màn hình
                    ReleaseDC(windowHandle, hdc); // Giải phóng ngữ cảnh thiết bị
                    
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
    void Game::loadInitialScreen()
    {
        // Tạo màn hình chính
        currentScreen = std::make_unique<MainScreen>();

        // Tải nội dung màn hình chính
        currentScreen->loadContent(graphic, windowWidth, windowHeight);
    }
}
