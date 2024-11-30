#pragma once
#include <windows.h>
#include <memory>

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleInput() = 0;
    virtual void update(float delta) = 0;
    virtual void render(HDC hdc) = 0;
};

class MainMenuState : public GameState {
public:
    void handleInput() override;
    void update(float delta) override;
    void render(HDC hdc) override;
};

class PlayingState : public GameState {
public:
    void handleInput() override;
    void update(float delta) override;
    void render(HDC hdc) override;
};

class PausedState : public GameState {
public:
    void handleInput() override;
    void update(float delta) override;
    void render(HDC hdc) override;
};
