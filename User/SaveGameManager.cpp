#include "SaveGameManager.h"

// Khởi tạo instance duy nhất là nullptr
std::shared_ptr<SaveGameManager> SaveGameManager::instance = nullptr;

// Truy cập instance duy nhất
//std::shared_ptr<SaveGameManager> SaveGameManager::getInstance() {
//    if (instance == nullptr) {
//        instance = std::shared_ptr<SaveGameManager>(new SaveGameManager());
//    }
//    return instance;
//}
//
//// Constructor
//SaveGameManager::SaveGameManager() {
//    GET_ALL_SAVE_GAME();
//}
//
//// Destructor
//SaveGameManager::~SaveGameManager() {
//    saveGames.clear();
//}

// Đọc tất cả save game từ file
void SaveGameManager::GET_ALL_SAVE_GAME() {
    std::ifstream file("Storage/savegames.catfam", std::ios::binary);
    if (file.is_open()) {
        while (file.peek() != EOF) {
            string userName;
            int point, mapCode, userHealth;
            size_t enemyCount, towerCount, bulletCount, healthCount, pathCount;

            // Đọc dữ liệu userName
            size_t nameLength;
            file.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
            userName.resize(nameLength);
            file.read(&userName[0], nameLength);

            // Đọc point, mapCode và userHealth
            file.read(reinterpret_cast<char*>(&point), sizeof(int));
            file.read(reinterpret_cast<char*>(&mapCode), sizeof(int));
            file.read(reinterpret_cast<char*>(&userHealth), sizeof(int));

            // Đọc vị trí enemy
            file.read(reinterpret_cast<char*>(&enemyCount), sizeof(size_t));
            std::vector<cpoint> enemyPos(enemyCount);
            file.read(reinterpret_cast<char*>(enemyPos.data()), enemyCount * sizeof(cpoint));

            // Đọc health của enemy
            file.read(reinterpret_cast<char*>(&healthCount), sizeof(size_t));
            std::vector<int> enemyHealth(healthCount);
            file.read(reinterpret_cast<char*>(enemyHealth.data()), healthCount * sizeof(int));

            // Đọc đường đi của enemy
            file.read(reinterpret_cast<char*>(&pathCount), sizeof(size_t));
            std::vector<int> enemyPathNumber(pathCount);
            file.read(reinterpret_cast<char*>(enemyPathNumber.data()), pathCount * sizeof(int));

            // Đọc vị trí tower
            file.read(reinterpret_cast<char*>(&towerCount), sizeof(size_t));
            std::vector<cpoint> towerPos(towerCount);
            file.read(reinterpret_cast<char*>(towerPos.data()), towerCount * sizeof(cpoint));

            // Đọc vị trí bullet
            file.read(reinterpret_cast<char*>(&bulletCount), sizeof(size_t));
            std::vector<cpoint> bulletPos(bulletCount);
            file.read(reinterpret_cast<char*>(bulletPos.data()), bulletCount * sizeof(cpoint));

            // Tạo SaveGame và thêm vào danh sách
            std::shared_ptr<SaveGame> saveGame = std::make_shared<SaveGame>(
                userName, enemyPos, enemyHealth, enemyPathNumber, towerPos, bulletPos, point, mapCode, userHealth
            );
            saveGames.push_back(saveGame);
        }
        file.close();
    }
}

// Ghi tất cả save game ra file
void SaveGameManager::POST_ALL_SAVE_GAME() {
    std::ofstream file("Storage/savegames.catfam", std::ios::binary | std::ios::trunc);
    if (file.is_open()) {
        for (const auto& saveGame : saveGames) {
            string userName = saveGame->getUserName();
            int point = saveGame->getPoint();
            int mapCode = saveGame->getMapCode();
            int userHealth = saveGame->getUserHealth();
            const auto& enemyPos = saveGame->getEnemyPos();
            const auto& enemyHealth = saveGame->getEnemyHealth();
            const auto& enemyPathNumber = saveGame->getEnemyPathNumber();
            const auto& towerPos = saveGame->getTowerPos();
            const auto& bulletPos = saveGame->getBulletPos();

            size_t nameLength = userName.size();
            size_t enemyCount = enemyPos.size();
            size_t healthCount = enemyHealth.size();
            size_t pathCount = enemyPathNumber.size();
            size_t towerCount = towerPos.size();
            size_t bulletCount = bulletPos.size();

            // Ghi userName
            file.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
            file.write(userName.data(), nameLength);

            // Ghi point, mapCode và userHealth
            file.write(reinterpret_cast<const char*>(&point), sizeof(int));
            file.write(reinterpret_cast<const char*>(&mapCode), sizeof(int));
            file.write(reinterpret_cast<const char*>(&userHealth), sizeof(int));

            // Ghi enemy positions
            file.write(reinterpret_cast<const char*>(&enemyCount), sizeof(size_t));
            file.write(reinterpret_cast<const char*>(enemyPos.data()), enemyCount * sizeof(cpoint));

            // Ghi enemy health
            file.write(reinterpret_cast<const char*>(&healthCount), sizeof(size_t));
            file.write(reinterpret_cast<const char*>(enemyHealth.data()), healthCount * sizeof(int));

            // Ghi enemy path numbers
            file.write(reinterpret_cast<const char*>(&pathCount), sizeof(size_t));
            file.write(reinterpret_cast<const char*>(enemyPathNumber.data()), pathCount * sizeof(int));

            // Ghi tower positions
            file.write(reinterpret_cast<const char*>(&towerCount), sizeof(size_t));
            file.write(reinterpret_cast<const char*>(towerPos.data()), towerCount * sizeof(cpoint));

            // Ghi bullet positions
            file.write(reinterpret_cast<const char*>(&bulletCount), sizeof(size_t));
            file.write(reinterpret_cast<const char*>(bulletPos.data()), bulletCount * sizeof(cpoint));
        }
        file.close();
    }
}

// Thêm save game mới
void SaveGameManager::POST_NEW_SAVE_GAME(std::shared_ptr<SaveGame> saveGame) {
    saveGames.push_back(saveGame);
    POST_ALL_SAVE_GAME();
}

void SaveGameManager::DELETE_SAVE_GAME(std::shared_ptr<SaveGame> saveGame) {
    saveGames.erase(
        std::remove(saveGames.begin(), saveGames.end(), saveGame),
        saveGames.end()
    );
    POST_ALL_SAVE_GAME();
}

std::vector<std::shared_ptr<SaveGame>> SaveGameManager::getSaveGameList() {
    return saveGames;
}

void SaveGameManager::printListSaveGameForTest() {
    for (const auto& saveGame : saveGames) {
        std::cout << "UserName: " << saveGame->getUserName() << std::endl;
        std::cout << "Points: " << saveGame->getPoint() << std::endl;
        std::cout << "Map Code: " << saveGame->getMapCode() << std::endl;
        std::cout << "User Health: " << saveGame->getUserHealth() << std::endl;

        std::cout << "Enemy Positions: ";
        for (auto& pos : saveGame->getEnemyPos()) {
            std::cout << "(" << pos.getX() << ", " << pos.getY() << ") ";
        }
        std::cout << std::endl;

        std::cout << "Enemy Health: ";
        for (const auto& health : saveGame->getEnemyHealth()) {
            std::cout << health << " ";
        }
        std::cout << std::endl;

        std::cout << "Enemy Path Numbers: ";
        for (const auto& path : saveGame->getEnemyPathNumber()) {
            std::cout << path << " ";
        }
        std::cout << std::endl;

        std::cout << "Tower Positions: ";
        for (auto& pos : saveGame->getTowerPos()) {
            std::cout << "(" << pos.getX() << ", " << pos.getY() << ") ";
        }
        std::cout << std::endl;

        std::cout << "Bullet Positions: ";
        for (auto& pos : saveGame->getBulletPos()) {
            std::cout << "(" << pos.getX() << ", " << pos.getY() << ") ";
        }
        std::cout << std::endl;
    }
}
