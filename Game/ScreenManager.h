#pragma once
#include <vector>
#include <memory>
#include "Graphic.h"

class Screen {
public:
    virtual ~Screen() = default;
    virtual void loadContent(Graphic& graphic) = 0;
    virtual void handleInput() = 0;
    virtual void update(float delta) = 0;
    virtual void render(HDC hdc) = 0;
};

class MainMenuScreen : public Screen {
    void loadContent(Graphic& graphic) override;
    void handleInput() override;
    void update(float delta) override;
    void render(HDC hdc) override;
};

// Các màn hình khác tương tự
