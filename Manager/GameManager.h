#pragma once
#include <iostream>
#include <memory>

class GameManager
{
private:
    static bool firstStartGame;
    GameManager();
    // Destructor.
    ~GameManager();

public:
    // Xóa copy constructor và operator= để tránh sao chép đối tượng Singleton.
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    // Hàm truy cập instance duy nhất của Singleton.
    static GameManager& getInstance();

    // Getter cho `firstStartGame`.
    bool isFirstStartGame()const;

    // Setter cho `firstStartGame`.
    void setFirstStartGame(bool value);
};