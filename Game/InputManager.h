#pragma once
#include <windows.h>

class InputManager {
public:
    void processKeyboard(WPARAM wParam);
    void processMouse(LPARAM lParam);
};
