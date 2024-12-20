#include "SaveGameManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

SaveGameManager::SaveGameManager() {
    saveGames = {};
    GET_ALL_SAVE_GAME();
}

SaveGameManager::~SaveGameManager() {
    saveGames.clear();
}

void SaveGameManager::GET_ALL_SAVE_GAME() {
    // Load all save games from file
    std::ifstream file("Storage/savegames.catfam", std::ios::binary);
    if (file.is_open()) {

        if (file.peek() == EOF) {
            file.close();
            return;
        }

        //while (file.peek() != EOF) {
            /*int userName, point, mapCode;
            size_t enemyCount, towerCount, bulletCount;*/

        //    // Read userName and point and mapCode
        //    file.read((char*)&userName, sizeof(int));
        //    file.read((char*)&point, sizeof(int));
        //    file.read((char*)&mapCode, sizeof(int));

        //    // Read enemy positions
        //    file.read((char*)&enemyCount, sizeof(size_t));
        //    std::vector<cpoint> enemyPos(enemyCount);
        //    file.read((char*)enemyPos.data(), enemyCount * sizeof(cpoint));

        //    // Read tower positions
        //    file.read((char*)&towerCount, sizeof(size_t));
        //    std::vector<cpoint> towerPos(towerCount);
        //    file.read((char*)towerPos.data(), towerCount * sizeof(cpoint));

        //    // Read bullet positions
        //    file.read((char*)&bulletCount, sizeof(size_t));
        //    std::vector<cpoint> bulletPos(bulletCount);
        //    file.read((char*)bulletPos.data(), bulletCount * sizeof(cpoint));

        //    // Create SaveGame object and add it to the list
        //    std::shared_ptr<SaveGame> saveGame = std::make_shared<SaveGame>(
        //        userName, enemyPos, towerPos, bulletPos, point, mapCode
        //    );
        //    saveGames.push_back(saveGame);
        //}
        file.close();
    }
}

void SaveGameManager::POST_ALL_SAVE_GAME() {
    // Save all save games to the file
    std::ofstream file("Storage/savegames.catfam", std::ios::binary | std::ios::trunc);
    if (file.is_open()) {
        for (const auto& saveGame : saveGames) {
            int userName = saveGame->getUserName();
            int point = saveGame->getPoint();
            int mapCode = saveGame->getMapCode();
            const std::vector<cpoint>& enemyPos = saveGame->getEnemyPos();
            const std::vector<cpoint>& towerPos = saveGame->getTowerPos();
            const std::vector<cpoint>& bulletPos = saveGame->getBulletPos();

            size_t enemyCount = enemyPos.size();
            size_t towerCount = towerPos.size();
            size_t bulletCount = bulletPos.size();

            // Write data
            file.write((char*)&userName, sizeof(int));
            file.write((char*)&point, sizeof(int));
            file.write((char*)&mapCode, sizeof(int));
            file.write((char*)&enemyCount, sizeof(size_t));
            file.write((char*)enemyPos.data(), enemyCount * sizeof(cpoint));
            file.write((char*)&towerCount, sizeof(size_t));
            file.write((char*)towerPos.data(), towerCount * sizeof(cpoint));
            file.write((char*)&bulletCount, sizeof(size_t));
            file.write((char*)bulletPos.data(), bulletCount * sizeof(cpoint));
        }
        file.close();
    }
}

void SaveGameManager::POST_NEW_SAVE_GAME(std::shared_ptr<SaveGame> saveGame) {
    // Add the new save game to the list
    saveGames.push_back(saveGame);

    // Save all save games to file
    POST_ALL_SAVE_GAME();
}

void SaveGameManager::DELETE_SAVE_GAME(std::shared_ptr<SaveGame> saveGame) {
    // Remove the save game from the list
    saveGames.erase(
        std::remove(saveGames.begin(), saveGames.end(), saveGame),
        saveGames.end()
    );

    // Save all save games to file
    POST_ALL_SAVE_GAME();
}

std::vector<std::shared_ptr<SaveGame>> SaveGameManager::getSaveGameList() {
    return saveGames;
}

void SaveGameManager::printListSaveGameForTest() {
    // print all save games include pos
    for (const auto& saveGame : saveGames) {
        std::cout << "SaveGame: " << std::endl;
        std::cout << "userName: " << saveGame->getUserName() << std::endl;
        std::cout << "point: " << saveGame->getPoint() << std::endl;
        std::cout << "mapCode: " << saveGame->getMapCode() << std::endl;
        std::cout << "enemyPos: " << std::endl;
        for (auto& pos : saveGame->getEnemyPos()) {
            std::cout << pos.getX() << " " << pos.getY() << std::endl;
        }
        std::cout << "towerPos: " << std::endl;
        for (auto& pos : saveGame->getTowerPos()) {
            std::cout << pos.getX() << " " << pos.getY() << std::endl;
        }
        std::cout << "bulletPos: " << std::endl;
        for (auto& pos : saveGame->getBulletPos()) {
            std::cout << pos.getX() << " " << pos.getY() << std::endl;
        }
        std::cout << std::endl;
    }
}

