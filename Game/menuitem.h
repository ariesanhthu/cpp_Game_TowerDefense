﻿#pragma once

#include <UIElement.h>
#include <memory>
#include <string>
#include "Graphic.h"

using namespace std;



class Item : public UIElement {
public: 
    Item() = default;
    Item(POINT pos, HBITMAP background) : UIElement(pos, background) {}
    Item(const wchar_t* link, float scale, int x, int y) : UIElement(link, scale, x, y) {}
    Item(const wchar_t* link, float scale, POINT pos) : UIElement(link, scale, pos) {}
};

class Button : public UIElement {
private:
    HBITMAP hover;
    HBITMAP clicked = nullptr;
    bool isClicking = false;
    bool enable = true;
    POINT buttonPosHover = {position.x - 12, position.y - 14};


public: 
	Button(POINT pos, HBITMAP hdefault, HBITMAP hover, HBITMAP clicked) : UIElement(pos, hdefault), hover(hover), clicked(clicked) {
        setCenterHover();
    }
	Button(POINT pos, HBITMAP hdefault, HBITMAP hover) : UIElement(pos, hdefault), hover(hover) {
        setCenterHover();
    }
    Button(const wchar_t* linkDefault, const wchar_t* linkHover, float scale, int x, int y) : UIElement(linkDefault, scale, x, y) {
        hover = Graphic::LoadBitmapImage(linkHover, scale); 
        setCenterHover();
    }
    Button(const wchar_t* linkDefault, const wchar_t* linkHover, float scale, POINT pos) : UIElement(linkDefault, scale, pos) {
        hover = Graphic::LoadBitmapImage(linkHover, scale);
        setCenterHover();
    }

	// --------- click button ------------
    Button(const wchar_t* linkDefault, const wchar_t* linkHover, const wchar_t* linkClicked, float scale, POINT pos) : UIElement(linkDefault, scale, pos) {
        hover = Graphic::LoadBitmapImage(linkHover, scale);
        clicked = Graphic::LoadBitmapImage(linkClicked, scale);
    }
	//----------------------------------

    Button() = default;
    ~Button() override {
        if (hover) {
            DeleteObject(hover);
            hover = nullptr;
        }
        if (clicked) {
            DeleteObject(clicked);
            clicked = nullptr;
        }
    }

    void render(HDC hdc) override {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(GetActiveWindow(), &cursorPos);


        if (hover && isHovered(cursorPos)) {
            Graphic::DrawBitmap(hover, buttonPosHover, hdc);
        }
        
        Graphic::DrawBitmap(image, position, hdc);
    }

    void handleClick(POINT mousePos) override {
        isClicking = true;
        // Thực hiện hành động khi bấm nút
    }

    void resetClick() { isClicking = false; }

    void setHoverPos(POINT pos) {
        this->buttonPosHover = pos;
    }

    void setCenterHover() {
        // Get the size of the hover bitmap and the image bitmap
        POINT sizeHover = Graphic::GetBitmapSize(hover);
        POINT sizeImage = Graphic::GetBitmapSize(image);

        // Calculate the center position for the hover effect
        POINT pos = position; // Position of the image
        POINT hoverPos;

        hoverPos.x = pos.x + (sizeImage.x - sizeHover.x) / 2; // Center horizontally
        hoverPos.y = pos.y + (sizeImage.y - sizeHover.y) / 2; // Center vertically

        // Set the calculated hover position
        this->buttonPosHover = hoverPos;
    }

    bool isEnabled() {
        return enable;
    }

    void setEnabled(bool t) {
        enable = t;
    }

};

class Popup : public UIElement {
private:
    POINT endPosition;
    bool isAnimating;
    float animationSpeed;

public:
    Popup(POINT start, POINT end, HBITMAP img, float speed = 1.0f)
        : UIElement(start, img), endPosition(end), isAnimating(false), animationSpeed(speed) {}
    Popup(const wchar_t* link, float scale, POINT start, POINT end, float speed = 1.0f) 
        : UIElement(link, scale, start), endPosition(end), isAnimating(false), animationSpeed(speed) {}

    void startAnimation() { isAnimating = true; }

    void update(float deltaTime) {
        if (!isAnimating) return;

        // Logic di chuyển popup
        position.x += (endPosition.x - position.x) * animationSpeed * deltaTime;
        position.y += (endPosition.y - position.y) * animationSpeed * deltaTime;

        if (abs(position.x - endPosition.x) < 1 && abs(position.y - endPosition.y) < 1) {
            position = endPosition;
            isAnimating = false;
        }
    }

    void render(HDC hdc) {
        Graphic::DrawBitmap(image, position, hdc);
    }
    
    bool isFinished() const { return !isAnimating; }
    
};

class Option : public UIElement {
private:
    HBITMAP hover;
    HBITMAP clicked = nullptr;
    bool isClicking;

    POINT endPosition;
    bool isAnimating;
    float animationSpeed;
    bool trigger = false;

public:
    Option(POINT start, POINT end, HBITMAP img, float speed = 1.0f)
        : UIElement(start, img), endPosition(end), isAnimating(false), trigger(false), animationSpeed(speed) {}
    Option(const wchar_t* defaultLink, const wchar_t* hoverLink, float scale, POINT start, POINT end, float speed = 1.0f)
        : UIElement(defaultLink, scale, start), endPosition(end), isAnimating(false), trigger(false), animationSpeed(speed) {
        hover = Graphic::LoadBitmapImage(hoverLink, scale);
    }
    Option() = default;
    ~Option() override {
        if (hover) {
            DeleteObject(hover);
            hover = nullptr;
        }
        if (clicked) {
            DeleteObject(clicked);
            clicked = nullptr;
        }
    }

    void startAnimation() { isAnimating = true; }

    void update(float deltaTime) {
        if (!isAnimating) return;

        // Logic di chuyển popup
        position.x += (endPosition.x - position.x) * animationSpeed * deltaTime;
        position.y += (endPosition.y - position.y) * animationSpeed * deltaTime;

        if (abs(position.x - endPosition.x) < 1 && abs(position.y - endPosition.y) < 1) {
            position = endPosition;
            isAnimating = false;
        }
    }

    void handleClick(POINT pos) override {
        isClicking = true;
        // Thực hiện hành động khi bấm nút
    }

    void resetClick() { isClicking = false; }

    void render(HDC hdc) {
        //if (trigger) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(GetActiveWindow(), &cursorPos);
            HBITMAP currentImage = image;

            if (isClicking && clicked) {
                currentImage = clicked;
            }

            else if (hover && isHovered(cursorPos)) {
                //currentImage = hover;
                POINT buttonPosHover = position;
                buttonPosHover.x -= 3;
                buttonPosHover.y -= 3;

                Graphic::DrawBitmap(hover, buttonPosHover, hdc);
            }

            if (currentImage) {
                Graphic::DrawBitmap(currentImage, position, hdc);
            }
        //}
    }

    bool getTriger() {
        return trigger;
    }

    void setTriger(bool t) {
        trigger = t;
    }

    bool isFinished() const { return !isAnimating; }

};

class TextElement : public UIElement {
private:
    std::wstring text;   
    HFONT font;          
    COLORREF textColor;

public:
    TextElement(wstring text, HFONT font, COLORREF textColor, POINT pos)
        : UIElement(pos, nullptr), text(text), font(font), textColor(textColor) {
    }

    void render(HDC hdc) override {
        Graphic::RenderText(text.c_str(), hdc, position, font, textColor);
    }

    // Update the text
    void setText(const wchar_t* newText) {
        text = newText;
    }
    std::wstring getText() const {
        return text;
    }
};

class InputElement : public UIElement {
private:
    std::wstring text = L"input";   // Current text in the input box
    std::wstring label = L"";
    HFONT font;          // Font for rendering
    COLORREF textColor;  // Text color
    bool isFocused;      // Focus state of the input element

public:
    InputElement(wstring label, POINT position, HFONT font, COLORREF textColor, const wchar_t* link, float factor)
        : UIElement(link, factor, position), label(label), font(font), textColor(textColor), isFocused(false) {
    }

    void render(HDC hdc) override {
        Graphic::DrawBitmap(image, position, hdc);
        POINT labelPos = position;
        labelPos.x -= 150; 
        labelPos.y += 20;
        POINT textPos = position;
        textPos.x += 20; 
        textPos.y += 20;
        Graphic::RenderText(label.c_str(), hdc, labelPos, font, textColor);
        Graphic::RenderText(text.c_str(), hdc, textPos, font, textColor);
    }

    // Handle mouse click to toggle focus
    void handleClick(POINT mousePos) override {
        isFocused = true;
    }

    bool isEdit() {
        return isFocused;
    }

    void setEdit(bool flag) {
        isFocused = flag;
    }

    void handleEdit() {
        if (isFocused) {
            for (wchar_t ch = 0x20; ch <= 0x7E; ++ch) {
                if (GetAsyncKeyState(ch) & 0x8000) {
                    auto now = std::chrono::steady_clock::now();
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() >= debounceDelayMs) {
                        lastKeyPressTime = now;
                        this->handleKeyPress(ch);
                    }
                }
            }
            if (GetAsyncKeyState(VK_BACK) & 0x8000) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() >= debounceDelayMs) {
                    lastKeyPressTime = now;
                    this->handleKeyPress(VK_BACK);
                }
            }
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count() >= debounceDelayMs) {
                    lastKeyPressTime = now;

                    this->handleKeyPress(VK_RETURN);
                }
            }


        }
    }

    // Handle keyboard input
    void handleKeyPress(wchar_t key) {
        if (isFocused) {
            if (key == VK_BACK && !text.empty()) {
                text.pop_back(); // Handle backspace
            }
            else if ((key >= 0x20 && key <= 0x7E) || (key >= 0x80)) {
                text += key;
            }
            else if (key == VK_RETURN) {
                text = L"";
            }
        }
    }

    // Get the current text
    const std::wstring& getText() const {
        return text;
    }

    // Set the text programmatically
    void setText(const wchar_t* newText) {
        text = newText;
    }

    // Get the current text
    const std::wstring& getLabel() const {
        return text;
    }

    // Set the text programmatically
    void setLabel(std::wstring newText) {
        text = newText;
    }
};

class ContinueElement : public UIElement {
private: 
    std::wstring name;
    std::wstring point; 
    std::wstring level;
    HFONT font;
    COLORREF textColor;

public: 
    ContinueElement(wstring name, wstring point, wstring level, POINT position, HFONT font, COLORREF textColor, const wchar_t* link, float factor)
        : UIElement(link, factor, position), name(name), point(point), level(level), font(font), textColor(textColor) {}

    wstring getName() { return name; }
    void setName(wstring _name) { name = _name; }
    wstring getPoint() { return point; }
    void setPoint(wstring _point) { point = _point; }
    wstring getLevel() { return level; }
    void setLevel(wstring _level) { level = _level; }

    void render(HDC hdc) override {
        Graphic::DrawBitmap(image, position, hdc);
        POINT namePos = position;
        namePos.x += 20;
        namePos.y += 15;
        Graphic::RenderText(name.c_str(), hdc, namePos, font, textColor);
        POINT pointPos = position;
        pointPos.x += 120;
        pointPos.y += 15;
        Graphic::RenderText(point.c_str(), hdc, pointPos, font, textColor);
        POINT levelPos = position;
        levelPos.x += 200;
        levelPos.y += 15;
        Graphic::RenderText(level.c_str(), hdc, levelPos, font, textColor);
    }
};



