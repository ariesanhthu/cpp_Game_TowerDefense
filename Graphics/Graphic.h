#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <algorithm>
#include <cmath>

using namespace Gdiplus;

class Graphic {
private:
    ULONG_PTR gdiPlusToken;

public:
    Graphic();
    ~Graphic();

    void InitGdiPlus();
    static HBITMAP LoadBitmapImage(const wchar_t* filename, double factor);
    static HBITMAP LoadCustomTest(std::string text, double factor, int spacing = 5);
    static void DrawBitmap(HBITMAP hBitmap, POINT start, HDC hdc);
    static void ReleaseBitmap(HBITMAP& hBitmap);
    static POINT GetBitmapSize(HBITMAP hbitmap); 
    static void RenderText(const wchar_t* text, HDC hdc, POINT pos, HFONT hFont, COLORREF color);
    static HFONT CreateCustomFont(int fontSize, const wchar_t* fontName);
};
