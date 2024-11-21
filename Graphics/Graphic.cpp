#include "Graphic.h"

Graphic::Graphic() {
    InitGdiPlus();
}

Graphic::~Graphic() {
    GdiplusShutdown(gdiPlusToken);
}

void Graphic::InitGdiPlus() {
    GdiplusStartupInput gdiPlusStartupInput;
    GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, nullptr);
}

HBITMAP Graphic::LoadBitmapImage(const wchar_t* filename, double factor) {
    Bitmap* originalBitmap = new Bitmap(filename);
    if (originalBitmap->GetLastStatus() != Ok) {
        delete originalBitmap;
    }

    int originalWidth = originalBitmap->GetWidth();
    int originalHeight = originalBitmap->GetHeight();
    int scaledWidth = originalWidth * factor;
    int scaledHeight = originalHeight * factor;

    Bitmap scaledBitmap(scaledWidth, scaledHeight, PixelFormat32bppARGB);
    for (int y = 0; y < originalHeight; y++) {
        for (int x = 0; x < originalWidth; x++) {
            Color pixelColor;
            originalBitmap->GetPixel(x, y, &pixelColor);
            for (int offsetY = 0; offsetY < factor; offsetY++) {
                for (int offsetX = 0; offsetX < factor; offsetX++) {
                    scaledBitmap.SetPixel(x * factor + offsetX, y * factor + offsetY, pixelColor);
                }
            }
        }
    }

    HBITMAP hBitmap;
    scaledBitmap.GetHBITMAP(Color(0, 0, 0), &hBitmap);

    delete originalBitmap;
    return hBitmap;
}

void Graphic::DrawBitmap(HBITMAP hBitmap, POINT start, HDC hdc) const {
    if (!hBitmap || !hdc) {
        MessageBoxW(nullptr, L"Invalid Bitmap or HDC!", L"Error", MB_OK);
        return;
    }

    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(bitmap), &bitmap);

    BLENDFUNCTION blendFunc = {};
    blendFunc.BlendOp = AC_SRC_OVER;
    blendFunc.SourceConstantAlpha = 255;
    blendFunc.AlphaFormat = AC_SRC_ALPHA;

    BOOL success = AlphaBlend(
        hdc, start.x, start.y, bitmap.bmWidth, bitmap.bmHeight,
        hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, blendFunc
    );

    if (!success) {
        MessageBoxW(nullptr, L"AlphaBlend failed!", L"Error", MB_OK);
    }

    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);
}

void Graphic::ReleaseBitmap(HBITMAP& hBitmap) const {
    if (hBitmap) {
        DeleteObject(hBitmap);
        hBitmap = nullptr;
    }
}