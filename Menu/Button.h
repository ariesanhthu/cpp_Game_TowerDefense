//#pragma once
//#include <windows.h>
//#include <functional>
//#include <string>
//#include "Graphic.h"
//
//class Button {
//private:
//    HWND hwndButton;
//    HWND hwndParent;
//    int id;
//
//    POINT position;
//    POINT size;
//
//    HBITMAP hDefault;
//    HBITMAP hHover;
//    HBITMAP hOnClick;
//
//    HFONT hFont;
//    std::wstring label;
//
//    Graphic graphic;
//
//    enum ButtonState { DEFAULT, HOVER, ON_CLICK } state;
//
//    std::function<void()> onClickCallback;
//
//public:
//    Button(HWND parent, int buttonId, POINT pos, POINT sz);
//    ~Button();
//
//    void create();
//    void setImages(const wchar_t* def, const wchar_t* hover, const wchar_t* click, double scale);
//    void setText(const std::wstring& text, HFONT font = nullptr);
//    void setCallback(std::function<void()> callback);
//
//    void handleEvent(UINT message, WPARAM wParam, LPARAM lParam);
//    void render(HDC hdc);
//};
