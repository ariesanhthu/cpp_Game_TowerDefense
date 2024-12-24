#include "AnimationManager.h"

// Định nghĩa singleton instance
AnimationManager& AnimationManager::getInstance()
{
    static AnimationManager instance;
    return instance;
}

// Constructor
AnimationManager::AnimationManager() = default;

// Thêm một hiệu ứng VFX
void AnimationManager::addVFX(const std::vector<std::wstring>& framePaths, float factor, POINT position, float speed)
{
    vfxList.emplace_back(framePaths, factor, position, speed);
}

// Cập nhật trạng thái của tất cả VFX
void AnimationManager::update(float deltaTime)
{
    for (auto it = vfxList.begin(); it != vfxList.end(); )
    {
        it->updateUI(deltaTime);
        if (it->isFinished())
        {
            it = vfxList.erase(it); // Xóa VFX đã hoàn thành
        }
        else
        {
            ++it;
        }
    }
}

// Vẽ tất cả các VFX
void AnimationManager::render(HDC hdc)
{
    for (auto& vfx : vfxList)
    {
        vfx.render(hdc);
    }
}
