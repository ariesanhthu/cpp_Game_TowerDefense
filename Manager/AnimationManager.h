#pragma once
#include "VFX.h"
#include <vector>
#include <string>
#include <Windows.h>

class AnimationManager
{
public:
    static AnimationManager& getInstance();

    void addVFX(const std::vector<std::wstring>& framePaths, float factor, POINT position, float speed);

    void update(float deltaTime);

    void render(HDC hdc);

private:
    AnimationManager(); // Constructor riêng tư
    std::vector<VFX> vfxList; // Quản lý danh sách VFX
};
