/*
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
    // Instance duy nhất của Singleton
    static std::shared_ptr<SaveGameManager> instance;

    // Danh sách save games
    std::vector<std::shared_ptr<SaveGame>> saveGames;

    // Constructor private để ngăn tạo đối tượng từ bên ngoài
    SaveGameManager() {
        // get all user
    }

public:
    // Destructor
    ~SaveGameManager() {
        saveGames.clear();
    }

    // Phương thức tĩnh để lấy instance duy nhất
    static std::shared_ptr<SaveGameManager> getInstance() {
        if (instance == nullptr) {
            instance = std::shared_ptr<SaveGameManager>(new SaveGameManager());
        }
        return instance;
    }

    // Các phương thức thao tác
    void GET_ALL_SAVE_GAME();
    void POST_ALL_SAVE_GAME();
    void POST_NEW_SAVE_GAME(std::shared_ptr<SaveGame> saveGame);
    void DELETE_SAVE_GAME(std::shared_ptr<SaveGame> saveGame);

    std::vector<std::shared_ptr<SaveGame>> getSaveGameList();
    void printListSaveGameForTest();
};
*/