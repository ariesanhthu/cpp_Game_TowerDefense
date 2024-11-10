#include "ctool.h"

mutex ctool::mtx;

void ctool::ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void ctool::GotoXY(int x, int y) {
    COORD crd;
    crd.X = x;
    crd.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
}
void ctool::Draw(char* str, int i, cpoint p[], cpoint& _p) {
    mtx.lock();
    _p = p[i];
    ctool::GotoXY(_p.getX(), _p.getY());
    cout << str;
    mtx.unlock();
}