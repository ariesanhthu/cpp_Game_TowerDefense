#pragma once

#include <vector>
#include <memory>
#include "SaveGame.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <Windows.h>

using namespace std;

class SaveGameManager {
private:
    std::vector<std::shared_ptr<SaveGame>> saveGames;

public:
    SaveGameManager();
    ~SaveGameManager();

    void GET_ALL_SAVE_GAME();
    void POST_ALL_SAVE_GAME();
    void POST_NEW_SAVE_GAME(std::shared_ptr<SaveGame> saveGame);
    void DELETE_SAVE_GAME(std::shared_ptr<SaveGame> saveGame);

    std::vector<std::shared_ptr<SaveGame>> getSaveGameList();
    void printListSaveGameForTest();
};

