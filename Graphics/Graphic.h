#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace Gdiplus;

class Graphic {
private:
    ULONG_PTR gdiPlusToken;

public:
    Graphic();
    ~Graphic();

    void InitGdiPlus();
    HBITMAP LoadBitmapImage(const wchar_t* filename, double factor);
    static void DrawBitmap(HBITMAP hBitmap, POINT start, HDC hdc);
    //void DrawBitmap(HBITMAP hBitmap, POINT start, HDC hdc) const;
    void ReleaseBitmap(HBITMAP& hBitmap) const;
};
