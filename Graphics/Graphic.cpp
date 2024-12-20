#include "Graphic.h"

Graphic::Graphic() {
    InitGdiPlus();
}

Graphic::~Graphic() {
    GdiplusShutdown(gdiPlusToken);
    OutputDebugStringA("~Graphic\n");
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

void Graphic::DrawBitmap(HBITMAP hBitmap, POINT start, HDC hdc) {
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

HBITMAP Graphic::LoadCustomTest(std::string text, double factor, int spacing) {
    // Base folder path for character bitmaps
    std::wstring basePath = L"Assets/text/";

    // Calculate total dimensions for the combined bitmap
    int totalWidth = 0;
    int maxHeight = 0;

    // Measure total width and maximum height
    for (char c : text) {
        if (std::islower(c)) {
            c = std::toupper(c); // Convert to uppercase if necessary
        }

        std::wstring fileName;
        if (std::isdigit(c)) {
            fileName = basePath + std::to_wstring(c - '0') + L".bmp";
        }
        else if (std::isupper(c)) {
            fileName = basePath + std::wstring(1, c) + L".bmp";
        }
        else {
            continue; // Skip unsupported characters
        }

        Bitmap tempBitmap(fileName.c_str());
        if (tempBitmap.GetLastStatus() != Ok) {
            continue;
        }

        totalWidth += static_cast<int>(tempBitmap.GetWidth() * factor) + spacing;
        if (maxHeight < static_cast<int>(tempBitmap.GetHeight() * factor)) { maxHeight = static_cast<int>(tempBitmap.GetHeight() * factor); }
    }

    // Adjust totalWidth to remove trailing spacing after the last character
    if (!text.empty()) {
        totalWidth -= spacing;
    }

    // Create the resulting bitmap
    Bitmap resultBitmap(totalWidth, maxHeight, PixelFormat32bppARGB);

    // Set all pixels in the result bitmap to transparent
    for (int y = 0; y < maxHeight; ++y) {
        for (int x = 0; x < totalWidth; ++x) {
            resultBitmap.SetPixel(x, y, Color(0, 0, 0, 0)); // Transparent background
        }
    }

    // Load and copy each character into the resulting bitmap
    int currentX = 0;
    for (char c : text) {
        if (std::islower(c)) {
            c = std::toupper(c); // Convert to uppercase if necessary
        }

        std::wstring fileName;
        if (std::isdigit(c)) {
            fileName = basePath + std::to_wstring(c - '0') + L".bmp";
        }
        else if (std::isupper(c)) {
            fileName = basePath + std::wstring(1, c) + L".bmp";
        }
        else {
            continue; // Skip unsupported characters
        }

        Bitmap tempBitmap(fileName.c_str());
        if (tempBitmap.GetLastStatus() != Ok) {
            continue;
        }

        int charWidth = tempBitmap.GetWidth();
        int charHeight = tempBitmap.GetHeight();

        for (int y = 0; y < charHeight; ++y) {
            for (int x = 0; x < charWidth; ++x) {
                Color pixelColor;
                tempBitmap.GetPixel(x, y, &pixelColor);

                // Copy scaled pixels into the result bitmap
                for (int offsetY = 0; offsetY < factor; ++offsetY) {
                    for (int offsetX = 0; offsetX < factor; ++offsetX) {
                        int destX = currentX + static_cast<int>(x * factor) + offsetX;
                        int destY = static_cast<int>(y * factor) + offsetY;

                        if (destX < totalWidth && destY < maxHeight) {
                            resultBitmap.SetPixel(destX, destY, pixelColor);
                        }
                    }
                }
            }
        }

        // Move to the next character position, adding spacing
        currentX += static_cast<int>(charWidth * factor) + spacing;
    }

    // Convert the resulting GDI+ Bitmap to HBITMAP
    HBITMAP hBitmap = nullptr;
    resultBitmap.GetHBITMAP(Color(0, 0, 0, 0), &hBitmap);

    // Return the new HBITMAP
    return hBitmap;
}

POINT Graphic::GetBitmapSize(HBITMAP hbitmap) {
    BITMAP bitmap;
    POINT size = { 0, 0 }; // Khởi tạo POINT với giá trị mặc định là (0, 0)

    // Lấy thông tin về HBITMAP vào cấu trúc BITMAP
    if (GetObject(hbitmap, sizeof(BITMAP), &bitmap)) {
        size.x = bitmap.bmWidth;  // Chiều rộng của bitmap
        size.y = bitmap.bmHeight; // Chiều cao của bitmap
    }

    return size;
}

HFONT Graphic::CreateCustomFont(int fontSize, const wchar_t* fontName) {
    return CreateFontW(
        fontSize,               // Font height (size)
        0,                      // Default width
        0,                      // No rotation angle
        0,                      // No base-line orientation angle
        FW_NORMAL,              // Normal font weight
        FALSE,                  // Not italic
        FALSE,                  // No underline
        FALSE,                  // No strikeout
        DEFAULT_CHARSET,        // Default character set
        OUT_DEFAULT_PRECIS,     // Default output precision
        CLIP_DEFAULT_PRECIS,    // Default clipping precision
        DEFAULT_QUALITY,        // Default quality
        DEFAULT_PITCH | FF_SWISS, // Default pitch and family
        fontName                // Font name
    );
}

void Graphic::RenderText(const wchar_t* text, HDC hdc, POINT pos, HFONT hFont, COLORREF color) {
    // Select the font into the device context
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

    // Set text color
    SetTextColor(hdc, color);

    // Set transparent background for text
    SetBkMode(hdc, TRANSPARENT);

    // Render the text at the specified position
    TextOutW(hdc, pos.x, pos.y, text, wcslen(text));

    // Restore the old font
    SelectObject(hdc, oldFont);
}


void Graphic::ReleaseBitmap(HBITMAP& hBitmap) {
    if (hBitmap) {
        if (!DeleteObject(hBitmap)) {
            // Log an error or throw an exception
            OutputDebugString(L"Failed to delete HBITMAP.\n");
        }
        hBitmap = nullptr;
    }
}