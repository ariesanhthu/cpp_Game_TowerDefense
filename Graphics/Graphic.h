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

	// HFONT TẠO NHỮNG FONT CÓ SẴN
    //static HFONT normalFont;
    //static HFONT boldFont;
    //static HFONT TitleFont;

	//------------------------------ -
    static HFONT CreateCustomFont(int fontSize, const wchar_t* fontName);
    //static HFONT LoadCustomFont(const std::wstring& fontPath, const std::wstring& fontName, int fontSize, int fontWeight)
    //{
    //    // Thêm font vào bộ nhớ hệ thống
    //    if (AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL) == 0)
    //    {
    //        OutputDebugStringA("Failed to load font from file\n");
    //        return nullptr;
    //    }

    //    // Tạo font tùy chỉnh
    //    HFONT hFont = CreateFontW(
    //        fontSize,               // Font height (size)
    //        0,                      // Default width
    //        0,                      // No rotation angle
    //        0,                      // No base-line orientation angle
    //        fontWeight,             // Font weight (e.g., FW_NORMAL, FW_BOLD)
    //        FALSE,                  // Not italic
    //        FALSE,                  // No underline
    //        FALSE,                  // No strikeout
    //        DEFAULT_CHARSET,        // Default character set
    //        OUT_DEFAULT_PRECIS,     // Default output precision
    //        CLIP_DEFAULT_PRECIS,    // Default clipping precision
    //        DEFAULT_QUALITY,        // Default quality
    //        DEFAULT_PITCH | FF_SWISS, // Default pitch and family
    //        fontName.c_str()        // Font name
    //    );

    //    if (!hFont)
    //    {
    //        OutputDebugStringA("Failed to create font\n");
    //    }

    //    return hFont;
    //}

};
