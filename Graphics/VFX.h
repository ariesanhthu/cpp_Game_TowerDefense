#pragma once
#include "UIElement.h"
#include <Windows.h>
#include <Animation.h>

class VFX : public UIElement {
public:
    // Constructor cho VFX
    VFX(const std::vector<std::wstring>& framePaths, float factor, POINT pos, float speed)
        : UIElement(framePaths, factor, pos)
    {
        setAnimation(framePaths, speed, factor);
    }
    //VFX(const VFX& other) {
    //    // Logic copy từng thành phần
    //    if (this != &other) {
    //        // Logic copy từng thành phần
    //    }
    //    return *this;
    //}

    VFX& operator=(const VFX& other) {
        if (this != &other) {
            // Logic copy từng thành phần
        }
        return *this;
    }

    //void updateUI(float deltaTime) override {
    //    animation.update(deltaTime * animation.getNumberFrame());
    //    image = animation.getCurrentFrame(); // Cập nhật frame hiện tại của animation
    //}

    //// Override phương thức renderUI
    //void update(float delta) {
    //    updateUI(delta);
    //}

    //// Kiểm tra nếu animation đã kết thúc
    bool isFinished() {
        return animation.getIsAnimating();
    }
};
