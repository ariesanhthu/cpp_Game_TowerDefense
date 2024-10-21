#include <iostream>
#include <Windows.h>

using namespace std;

enum colors { BLACK = 0, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, GREY,
                 LIGHTGREY, LIGHTRED, LIGHTGREEN, LIGHTYELLOW, LIGHTBLUE,
                 LIGHTPURPLE, LIGHTCYAN, WHITE, DEFAULT };

// Hàm chỉnh buffer size
void SetConsoleBufferSize(SHORT width, SHORT height) {

    HANDLE buffer = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SHORT columns, rows;

    GetConsoleScreenBufferInfo(buffer, &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    COORD NewSize;
    NewSize.X = columns;
    NewSize.Y = rows;

    SetConsoleScreenBufferSize(buffer, NewSize);
}

// Hàm chỉnh window size
void SetWindowSize(SHORT width, SHORT height) {
    RECT r;
    HWND console_window = GetConsoleWindow();
    GetWindowRect(console_window, &r);
    MoveWindow(console_window, 1, 1, width, height, TRUE);
}

// Hàm chỉnh font size
void SetConsoleFont(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = width; 
    cfi.dwFontSize.Y = height;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;

    wcscpy_s(cfi.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void DisableScrollbar() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &info);

    info.srWindow.Right = info.dwSize.X - 1;
    info.dwSize.X = info.srWindow.Right + 1;

    SetConsoleScreenBufferInfoEx(hConsole, &info);
}

// Các hàm khác giữ nguyên
void ShowScrollbar(BOOL Show) {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void moveWindow(int x, int y) {
    HWND console_window = GetConsoleWindow();
    RECT r;
    GetWindowRect(console_window, &r);
    MoveWindow(console_window, x, y, r.right - r.left, r.bottom - r.top, TRUE);
}

void setCenterWindowPosition() {
    RECT windowRect;
    GetWindowRect(GetConsoleWindow(), &windowRect);

    int centerX = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
    int centerY = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;

    MoveWindow(GetConsoleWindow(), centerX, centerY, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, TRUE);
}

void goToXY(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

void setConsoleRGBColor(int index, int r, int g, int b) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &info);
    info.ColorTable[index] = RGB(r, g, b);
    SetConsoleScreenBufferInfoEx(hConsole, &info);
}

void setConsoleTextAndBackgroundColor(int foregroundIndex, int backgroundIndex) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, foregroundIndex + (backgroundIndex << 4));
}


int main() {

    ShowScrollbar(FALSE);
    setCenterWindowPosition();
    SetConsoleTitle("Duc ne hihi");

    SetConsoleFont(3, 3);
    SetConsoleBufferSize(1280, 720);
    SetWindowSize(1280, 720);


    setConsoleRGBColor(2, 0, 0, 0);
    setConsoleRGBColor(4, 32, 235, 229);

    system("cls");
    goToXY(0, 0);

    setConsoleTextAndBackgroundColor(2, 4);

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            goToXY(i + 10, j + 10);
            cout << " ";
        }
        cout << endl;
    }

    // for (int i = 0; i < 1000; i++) {
    //     cout << " ";
    // }

    cin.get();

    setConsoleTextAndBackgroundColor(7, 0);

    return 0;
}
