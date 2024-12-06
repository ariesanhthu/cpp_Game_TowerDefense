#pragma once

#include <UIElement.h>
#include <memory>


class Item : public UIElement {
public: 
    Item() = default;
    Item(POINT pos, HBITMAP background) : UIElement(pos, background) {}
    Item(const wchar_t* link, float scale, int x, int y) : UIElement(link, scale, x, y) {}
};

class Button : public UIElement {
private: 
    HBITMAP hover;
    HBITMAP clicked = nullptr; 
    bool isClicking;

public: 
	Button(POINT pos, HBITMAP hdefault, HBITMAP hover, HBITMAP clicked) : UIElement(pos, hdefault), hover(hover), clicked(clicked) {}
	Button(POINT pos, HBITMAP hdefault, HBITMAP hover) : UIElement(pos, hdefault), hover(hover) {}
    Button(const wchar_t* linkDefault, const wchar_t* linkHover, float scale, int x, int y) : UIElement(linkDefault, scale, x, y) {
        hover = Graphic::LoadBitmapImage(linkHover, scale); 
    }
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
        HBITMAP currentImage = image;

        if (isClicking && clicked) {
            currentImage = clicked;
        }

        else if (hover && isHovered(cursorPos)) {
            //currentImage = hover;
            POINT buttonPosHover = position;
            buttonPosHover.x -= 12;
            buttonPosHover.y -= 14;

            Graphic::DrawBitmap(hover, buttonPosHover, hdc);
        }

        if (currentImage) {
            Graphic::DrawBitmap(currentImage, position, hdc);
        }
    }

    void handleClick() override {
        isClicking = true;
        // Thực hiện hành động khi bấm nút
    }

    void resetClick() { isClicking = false; }
};

class Popup : public UIElement {
private:
    POINT endPosition;
    bool isAnimating;
    float animationSpeed;
    bool trigger;

public:
    Popup(POINT start, POINT end, HBITMAP img, float speed = 1.0f)
        : UIElement(start, img), endPosition(end), isAnimating(false), trigger(false), animationSpeed(speed) {}

    void startAnimation() { isAnimating = true; }

    void update(float deltaTime) {
        if (!isAnimating || !trigger) return;

        // Logic di chuyển popup
        position.x += (endPosition.x - position.x) * animationSpeed * deltaTime;
        position.y += (endPosition.y - position.y) * animationSpeed * deltaTime;

        if (abs(position.x - endPosition.x) < 1 && abs(position.y - endPosition.y) < 1) {
            position = endPosition;
            isAnimating = false;
        }
    }

    void render(HDC hdc) {
        if (trigger) {
            Graphic::DrawBitmap(image, position, hdc);
        }
    }

    bool getTriger() {
        return trigger;
    }

    void setTriger(bool t) {
        trigger = t;
    }
    
    bool isFinished() const { return !isAnimating; }
    
};

