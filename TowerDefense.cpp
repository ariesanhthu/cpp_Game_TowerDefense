#include <windows.h>

// Khai báo HBITMAP để giữ bitmap đã load
HBITMAP hBitmap;

// Hàm load bitmap
void LoadBitmapImage()
{
    // Load image từ file hoặc từ tài nguyên (ở đây load từ file)
    hBitmap = (HBITMAP)LoadImage(
        NULL,            // Không lấy từ tài nguyên của ứng dụng
        L"Assets/enemy2.bmp",  // Đường dẫn file
        IMAGE_BITMAP,    // Loại ảnh là bitmap
        0, 0,            // Giữ nguyên kích thước gốc
        LR_LOADFROMFILE  // Load từ file
    );

    if (hBitmap == NULL) {
        MessageBox(NULL, L"Failed to load bitmap!", L"Error", MB_OK);
    }
}

// Hàm vẽ bitmap
void DrawBitmap(HDC hdc, int x, int y)
{
    if (hBitmap != NULL) {
        // Tạo memory DC và chọn bitmap vào đó
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

        // Lấy kích thước bitmap
        BITMAP bitmap;
        GetObject(hBitmap, sizeof(bitmap), &bitmap);

        // Sao chép bitmap từ memory DC lên cửa sổ
        BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
        //BitBlt(hdc, 200, 200, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

        // Dọn dẹp
        SelectObject(hdcMem, hbmOld);
        DeleteDC(hdcMem);
    }
}

// Hàm xử lý Windows Messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Vẽ bitmap lên cửa sổ
        DrawBitmap(hdc, 100, 100);

        DrawBitmap(hdc, 200, 200);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY: {
        // Giải phóng bitmap khi đóng ứng dụng
        if (hBitmap != NULL) {
            DeleteObject(hBitmap);
        }
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Chương trình chính
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    // create window class
    WNDCLASS WindowClass = {};

    WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpszClassName = L"Game Window Class";
    WindowClass.lpfnWndProc = WindowProc;

    // register class
    RegisterClass(&WindowClass);
    // Tạo cửa sổ
    HWND window = CreateWindow(
        WindowClass.lpszClassName,
        L"cat-farm",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1280, 720,
        0, 0,
        hInstance,
        0);

    HDC hdc = GetDC(window);

    ShowWindow(window, nCmdShow);

    // Load bitmap khi khởi động
    LoadBitmapImage();

    // Vòng lặp message
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

////#pragma once
//#include "Utils/PrecompiledHeader.h"
//
////typedef struct tagBITMAPINFOHEADER {
////	DWORD biSize;
////	LONG  biWidth;
////	LONG  biHeight;
////	WORD  biPlanes;
////	WORD  biBitCount;
////	DWORD biCompression;
////	DWORD biSizeImage;
////	LONG  biXPelsPerMeter;
////	LONG  biYPelsPerMeter;
////	DWORD biClrUsed;
////	DWORD biClrImportant;
////} BITMAPINFOHEADER, * LPBITMAPINFOHEADER, * PBITMAPINFOHEADER;
//
////win32 platform
//bool running = true;
//
////callback nhận những thay đổi từ việc điều chỉnh màn hình window, gửi về và thực hiện
//// nếu không gọi callback window sẽ ở trạng thái not responding
//LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	//return a messenge
//	LRESULT result = 0;
//
//	switch (uMsg)
//	{
//	case WM_CLOSE:
//	case WM_DESTROY: {
//		running = false;
//		break;
//	}
//				   // lấy kích thước cửa sổ mỗi khi có sự thay đổi
//	case WM_SIZE:
//	{
//		RECT rect;
//		
//		// đọc kích thước màn hình
//		GetClientRect(hwnd, &rect);
//
//		// tính toán buffer
//		render_state.width = rect.right - rect.left;
//		render_state.height = rect.bottom - rect.top;
//
//		// kích thước buffer tích các ô buffer và kích thước mỗi ô (32bit == unsigned int)
//		int buffer_size = render_state.width * render_state.height * sizeof(unsigned int);
//
//		// check nếu buffer quá nhỏ
//		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
//
//		render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//		
//		// set bitmap header
//		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
//		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
//		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
//		render_state.bitmap_info.bmiHeader.biPlanes = 1; //Specifies the number of planes for the target device. This value must be set to 1.
//		render_state.bitmap_info.bmiHeader.biBitCount = 32; // depth of uncompressed inmage: số bit trung bình /pixel, 
//		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
//
//		
//	}
//	default:
//		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
//	}
//
//	return result;
//}
//
//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//{
//	// create window class
//	WNDCLASS WindowClass = {};
//
//	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
//	WindowClass.lpszClassName = L"Game Window Class";
//	WindowClass.lpfnWndProc = window_callback;
//
//	// register class
//	RegisterClass(&WindowClass);
//
//	// create window
//	HWND window = CreateWindow(WindowClass.lpszClassName, L"cat-farm", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
//	HDC hdc = GetDC(window);
//
//	while (running)
//	{
//		//input
//		MSG message;
//		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&message);
//			DispatchMessage(&message);
//		}
//
//		//simulate
//		Clear_screen(0xff5500);
//		draw_rect(50, 50, 500, 500, 0xff000);
//
//
//		// khởi tạo một biến con trỏ
//		// trỏ tới vùng nhớ (render_state.memory) nơi lưu trữ các giá trị thay đổi windown
//		//unsigned int* pixel = (unsigned int*)render_state.memory;
//		//for(int y = 0; y < render_state.height; y ++)
//		//	for (int x = 0; x < render_state.width; x++)
//		//	{
//		//		// truy cập đến vùng nhớ được trỏ tới
//		//		// thay đổi giá trị trên vùng nhớ đó
//		//			*pixel++ = x*y;
//		//	}
//	
//		//render
//		StretchDIBits(
//			hdc,
//			0,				//xDest
//			0,				//yDest
//			render_state.width,	//DestWidth
//			render_state.height,  //DestHeight
//			0,				// xSrc
//			0,				// ySrc
//			render_state.width,	// SrcWidth
//			render_state.height,	// SrcHeight
//			render_state.memory,	// lpBits
//			&render_state.bitmap_info,
//			DIB_RGB_COLORS,
//			SRCCOPY
//		);
//	}
//}
// /*
// ===========================================================
// load bitmap
// ===========================================================*/
// 
//#include <windows.h>
//
//// Khai báo HBITMAP để giữ bitmap đã load
//HBITMAP hBitmap;
//
//// Hàm load bitmap
//void LoadBitmapImage()
//{
//    // Load image từ file hoặc từ tài nguyên (ở đây load từ file)
//    hBitmap = (HBITMAP)LoadImage(
//        NULL,            // Không lấy từ tài nguyên của ứng dụng
//        L"Assets\\enemy2.bmp", // Đường dẫn tuyệt đối
//        // Đường dẫn file
//        IMAGE_BITMAP,    // Loại ảnh là bitmap
//        0, 0,            // Giữ nguyên kích thước gốc
//        LR_LOADFROMFILE  // Load từ file
//    );
//
//    if (hBitmap == NULL) {
//        MessageBox(NULL, L"Failed to load bitmap!", L"Error", MB_OK);
//    }
//}
//
//// Hàm vẽ bitmap
//void DrawBitmap(HDC hdc)
//{
//    if (hBitmap != NULL) {
//        // Tạo memory DC và chọn bitmap vào đó
//        HDC hdcMem = CreateCompatibleDC(hdc);
//        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);
//
//        // Lấy kích thước bitmap
//        BITMAP bitmap;
//        GetObject(hBitmap, sizeof(bitmap), &bitmap);
//
//        // Sao chép bitmap từ memory DC lên cửa sổ
//        BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
//
//        // Dọn dẹp
//        SelectObject(hdcMem, hbmOld);
//        DeleteDC(hdcMem);
//    }
//}
//
//// Hàm xử lý Windows Messages
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg) {
//    case WM_PAINT: {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//
//        // Vẽ bitmap lên cửa sổ
//        DrawBitmap(hdc);
//
//        EndPaint(hwnd, &ps);
//        break;
//    }
//    case WM_DESTROY: {
//        // Giải phóng bitmap khi đóng ứng dụng
//        if (hBitmap != NULL) {
//            DeleteObject(hBitmap);
//        }
//        PostQuitMessage(0);
//        break;
//    }
//    }
//    return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
//
//// Chương trình chính
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//    // Đăng ký lớp cửa sổ
//    WNDCLASS wc = {};
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = L"BitmapWindowClass";
//
//    RegisterClass(&wc);
//
//    // Tạo cửa sổ
//    HWND hwnd = CreateWindowEx(
//        0, L"BitmapWindowClass", L"Bitmap Window",
//        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
//        NULL, NULL, hInstance, NULL
//    );
//
//    if (hwnd == NULL) return 0;
//
//    ShowWindow(hwnd, nCmdShow);
//
//    // Load bitmap khi khởi động
//    LoadBitmapImage();
//
//    // Vòng lặp message
//    MSG msg = {};
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return 0;
//}
//
//#include <windows.h>
//
//// Khai báo HBITMAP để giữ bitmap đã load
//HBITMAP hBitmap;
//HBITMAP hMask; // Bitmap mask
//
//// Hàm load bitmap
//void LoadBitmapImage()
//{
//    hBitmap = (HBITMAP)LoadImage(
//        NULL,
//        L"Assets\\enemy2.bmp",
//        IMAGE_BITMAP,
//        0, 0,
//        LR_LOADFROMFILE
//    );
//
//    if (hBitmap == NULL) {
//        MessageBox(NULL, L"Failed to load bitmap!", L"Error", MB_OK);
//        return;
//    }
//
//    // Tạo mask từ bitmap
//    HDC hdc = GetDC(NULL);
//    HDC hdcMem = CreateCompatibleDC(hdc);
//    HDC hdcMask = CreateCompatibleDC(hdc);
//
//    // Chọn bitmap vào hdcMem và tạo mask bitmap
//    SelectObject(hdcMem, hBitmap);
//    BITMAP bmp;
//    GetObject(hBitmap, sizeof(BITMAP), &bmp);
//
//    // Tạo bitmap mask
//    hMask = CreateBitmap(bmp.bmWidth, bmp.bmHeight, 1, 1, NULL);
//    SelectObject(hdcMask, hMask);
//
//    // Tạo mask với nền đen (các pixel màu đen trở thành màu trắng trong mask)
//    SetBkColor(hdcMem, RGB(0, 0, 0));
//    BitBlt(hdcMask, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);
//
//    // Dọn dẹp
//    DeleteDC(hdcMem);
//    DeleteDC(hdcMask);
//    ReleaseDC(NULL, hdc);
//}
//
//// Hàm vẽ bitmap với mask để loại bỏ nền đen
//void DrawBitmap(HDC hdc)
//{
//    if (hBitmap != NULL && hMask != NULL) {
//        // Tạo memory DC và chọn bitmap và mask vào đó
//        HDC hdcMem = CreateCompatibleDC(hdc);
//        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);
//
//        HDC hdcMaskMem = CreateCompatibleDC(hdc);
//        HBITMAP hbmMaskOld = (HBITMAP)SelectObject(hdcMaskMem, hMask);
//
//        BITMAP bitmap;
//        GetObject(hBitmap, sizeof(bitmap), &bitmap);
//
//        // Vẽ nền bitmap để giữ các pixel nền
//        //BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMaskMem, 0, 0, SRCAND);
//
//        // Vẽ bitmap đã loại bỏ nền đen
//        BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCPAINT);
//
//        // Dọn dẹp
//        SelectObject(hdcMem, hbmOld);
//        SelectObject(hdcMaskMem, hbmMaskOld);
//        DeleteDC(hdcMem);
//        DeleteDC(hdcMaskMem);
//    }
//}
//
//// Hàm xử lý Windows Messages
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg) {
//    case WM_PAINT: {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//
//        // Vẽ bitmap với mask lên cửa sổ
//        DrawBitmap(hdc);
//
//        EndPaint(hwnd, &ps);
//        break;
//    }
//    case WM_DESTROY: {
//        // Giải phóng bitmap và mask khi đóng ứng dụng
//        if (hBitmap != NULL) {
//            DeleteObject(hBitmap);
//        }
//        if (hMask != NULL) {
//            DeleteObject(hMask);
//        }
//        PostQuitMessage(0);
//        break;
//    }
//    }
//    return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
//
//// Chương trình chính
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//    WNDCLASS wc = {};
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = L"BitmapWindowClass";
//
//    RegisterClass(&wc);
//
//    HWND hwnd = CreateWindowEx(
//        0, L"BitmapWindowClass", L"Bitmap Window",
//        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
//        NULL, NULL, hInstance, NULL
//    );
//
//    if (hwnd == NULL) return 0;
//
//    ShowWindow(hwnd, nCmdShow);
//
//    // Load bitmap và mask khi khởi động
//    LoadBitmapImage();
//
//    MSG msg = {};
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return 0;
//}
