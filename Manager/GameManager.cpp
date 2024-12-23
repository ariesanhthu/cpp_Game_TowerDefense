#include "GameManager.h"

// Định nghĩa biến static
bool GameManager::firstStartGame = false;
// Constructor
GameManager::GameManager()
{
    //firstStartGame = false; // Khởi tạo mặc định
}

// Destructor
GameManager::~GameManager() {}

// Truy cập Singleton
GameManager& GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

// Getter
bool GameManager::isFirstStartGame() const
{
    return firstStartGame;
}

// Setter
void GameManager::setFirstStartGame(bool value)
{
    firstStartGame = value;
}