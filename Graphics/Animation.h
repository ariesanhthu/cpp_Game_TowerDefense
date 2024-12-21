#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include "Graphic.h"

class Animation
{
private:
    std::vector<HBITMAP> frames; // Các frame của animation
    int currentFrame;            // Frame hiện tại
    float animationTimer;        // Bộ đếm thời gian để đổi frame
    float animationSpeed;        // Tốc độ đổi frame (giây)
    bool isAnimating;            // Trạng thái animation (true nếu đang chạy)

public:
    Animation() : currentFrame(0), animationTimer(0.0f), animationSpeed(0.2f), isAnimating(false) {}

    void setFrames(const std::vector<std::wstring>& framePaths, float speed, float factor)
    {
        animationSpeed = speed;
        frames.clear();
        for (const auto& path : framePaths)
        {
            frames.push_back(Graphic::LoadBitmapImage(path.c_str(), factor)); // Load từng frame
        }
        isAnimating = true;
    }

    void update(float deltaTime)
    {
        if (!isAnimating || frames.empty())
        {
            return;
        }

        animationTimer += deltaTime;

        if (animationTimer >= animationSpeed)
        {
            animationTimer = 0.0f;
            currentFrame = (currentFrame + 1) % frames.size(); // Quay vòng các frame
        }
    }

    void stop()
    {
        isAnimating = false;
        currentFrame = 0;
    }

    void play()
    {
        isAnimating = true;
    }

    HBITMAP getCurrentFrame() const
    {
        return frames.empty() ? nullptr : frames[currentFrame];
    }

    int getNumberFrame()
    {
        return frames.size();
    }

    ~Animation()
    {
        for (auto& frame : frames)
        {
            DeleteObject(frame);
        }
    }
};
