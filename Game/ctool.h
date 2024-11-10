#pragma once
#include "cpoint.h"
#include <windows.h>
#include <iostream>
#include <mutex>

using namespace std;


class ctool {
    public:
        static mutex mtx;
        static void ShowConsoleCursor(bool);
        static void GotoXY(int, int);
        static void Draw(char*, int, cpoint[], cpoint&);
};