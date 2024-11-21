#pragma once
class UIElement {
protected:
    int x, y, width, height;

public:
    virtual void render() = 0;
    virtual void update(float delta) = 0;
    //virtual void handleInput(InputEvent input) = 0;
    virtual ~UIElement() {}
};