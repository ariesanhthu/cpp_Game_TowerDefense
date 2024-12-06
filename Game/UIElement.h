#pragma once

#include <windows.h>
#include <Graphic.h>
#include <chrono>

class UIElement {
protected:
    POINT position;  // Position of the UI element
    POINT size;      // Size of the UI element
    HBITMAP image;   // Default image for the element
    mutable std::chrono::steady_clock::time_point lastMouseClickTime;  // mutable to modify in const method
    std::chrono::steady_clock::time_point lastKeyPressTime;
    const int debounceDelayMs = 300; // 200 ms debounce delay

public:
    UIElement(POINT pos, HBITMAP img)
        : position(pos), image(img), lastMouseClickTime(std::chrono::steady_clock::now()) {
        size = Graphic::GetBitmapSize(image);
    }
    UIElement(const wchar_t* link, float factor, int x, int y) {
        position.x = x;
        position.y = y; 
        image = Graphic::LoadBitmapImage(link, factor); 
    }

    virtual ~UIElement() {
        if (image) {
            DeleteObject(image); // Release HBITMAP
            image = nullptr;
        }
    }

    // Render the element on the screen
    virtual void render(HDC hdc) {
        if (image) {
            Graphic::DrawBitmap(image, position, hdc);
        }
    }
    // Check if the mouse is hovering over the element
    virtual bool isHovered(POINT mousePos) const {
        return mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
            mousePos.y >= position.y && mousePos.y <= position.y + size.y;
    }

    // Check if the element is clicked, with debounce handling
    virtual int isClicked(POINT mousePos) const {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;
                if (isHovered(mousePos)) {
                    return 1;
                }
                else {
                    return -1;
                }
            }
        }
        else {
            return 0;
        }
    }

    virtual HBITMAP getBitmap() {
        return image;
    }

    virtual void setBitmap(HBITMAP himage) {
        image = himage;
    }

    virtual void setPosition(POINT pos) {
        position = pos;
    }

    // Handle click event on the element
    virtual void handleClick() {}
};
