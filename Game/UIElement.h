#pragma once

#include <windows.h>
#include <Graphic.h>
#include <chrono>
#include <vector>

#include "Animation.h"

class UIElement {
protected:
    POINT position;  // Position of the UI element
    POINT size;      // Size of the UI element
    HBITMAP image;   // Default image for the element

    mutable std::chrono::steady_clock::time_point lastMouseClickTime;  // mutable to modify in const method
    std::chrono::steady_clock::time_point lastKeyPressTime;
    const int debounceDelayMs = 300; // 200 ms debounce delay
    bool trigger = false;

    Animation animation;

public:
    UIElement() {
        image = nullptr;
    }
    UIElement(POINT pos, HBITMAP img)
        : position(pos), image(img), lastMouseClickTime(std::chrono::steady_clock::now()) {
        size = Graphic::GetBitmapSize(image);
    }
    UIElement(const wchar_t* link, float factor, int x, int y) {
        position.x = x;
        position.y = y; 
        image = Graphic::LoadBitmapImage(link, factor); 
        size = Graphic::GetBitmapSize(image);
    }
    UIElement(const wchar_t* link, float factor, POINT pos) {
        position = pos; 
        image = Graphic::LoadBitmapImage(link, factor);
        size = Graphic::GetBitmapSize(image);
    }

    bool getTriger() {
        return trigger;
    }

    void setTriger(bool t) {
        trigger = t;
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

    virtual bool isHoverInside(POINT mousePos) const {
        RECT area = {
            position.x,
            position.y,
            position.x + size.x,
            position.y + size.y   
        };

        if (PtInRect(&area, mousePos)) {
            return true;
        } 

        return false;
    }

    // Check if the element is clicked, with debounce handling
    virtual bool isClicked(POINT mousePos) const {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;
                if (isHovered(mousePos)) {
                    return true;
                }
            }
        }
        return false;
    }

    virtual bool isNotClicked(POINT mousePos) const {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMouseClickTime).count() >= debounceDelayMs) {
                lastMouseClickTime = now;
                if (!isHoverInside(mousePos)) {
                    return true;
                }
            }
        }
        return false;
    }

    virtual bool isNotHoverInside(POINT mousePos) const {
        RECT area = {
            position.x,
            position.y,
            position.x + size.x,
            position.y + size.y
        };

        if (!PtInRect(&area, mousePos)) {
            return true;
        }

        return false;
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
    virtual void handleClick(POINT mousePos) {}

    // -------------------------------------------
	//  ANIMATION
	// -------------------------------------------
    void playAnimation() {
        animation.play();
    }

    void stopAnimation() {
        animation.stop();
    }
    // Update the element (including animation)
    virtual void updateUI(float deltaTime) {
        animation.update(deltaTime);
        image = animation.getCurrentFrame(); 
    }
    // Animation Setup
    void setAnimation(const std::vector<std::wstring>& framePaths, float speed, float factor) {
        animation.setFrames(framePaths, speed, factor);
        if (!framePaths.empty()) {
            image = animation.getCurrentFrame(); // Set initial frame
        }
    }
	// khởi tạo animation
    UIElement(const std::vector<std::wstring>& imagePaths, float factor, POINT pos) {
        position = pos;
        image = Graphic::LoadBitmapImage(imagePaths[0].c_str(), factor);
        size = Graphic::GetBitmapSize(image);
        setAnimation(imagePaths, 0.1f, factor);
    }
};
