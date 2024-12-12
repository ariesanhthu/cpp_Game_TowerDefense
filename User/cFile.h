#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <regex>

// Enemy class element
namespace towerdefense {
    struct saveEnemy {
        int health;
        POINT currentPosition;
        std::vector<POINT> path;
        int index;
    };

    struct saveTower {
        POINT location;
    };

    struct saveUser {
        int UserId; // Automatically generated
        std::string name;
        std::string password;
        std::vector<int> gameId;
    };

    struct saveGame {
        int gameId; // Automatically generated
        std::vector<saveEnemy> listEnemy; // Vector of enemies
        std::vector<saveTower> listTower; // Vector of towers
        int mapCode;
        int UserId;
    };

    // Function to create and save dummy user data
    inline void createDummyUserDataFile(const std::vector<saveUser>& dummy) {
        std::ofstream file("users.catfam");
        if (!file) {
            std::cerr << "Error: Could not open users.catfam for writing.\n";
            return;
        }

        for (const auto& user : dummy) {
            file << user.UserId << "|"
                << user.name << "|"
                << user.password << "|";
            for (size_t i = 0; i < user.gameId.size(); ++i) {
                file << user.gameId[i];
                if (i < user.gameId.size() - 1) file << ",";
            }
            file << "\n";
        }
        file.close();
    }

    // Function to create and save dummy game data
    inline void createDummyGameDataFile(const std::vector<saveGame>& dummy) {
        std::ofstream file("games.catfam");
        if (!file) {
            std::cerr << "Error: Could not open games.catfam for writing.\n";
            return;
        }

        for (const auto& game : dummy) {
            file << game.gameId << "|";
            for (size_t i = 0; i < game.listEnemy.size(); ++i) {
                const auto& enemy = game.listEnemy[i];
                file << "{"
                    << enemy.health << ",{"
                    << enemy.currentPosition.x << ","
                    << enemy.currentPosition.y << "},[";

                for (size_t j = 0; j < enemy.path.size(); ++j) {
                    file << "{" << enemy.path[j].x << "," << enemy.path[j].y << "}";
                    if (j < enemy.path.size() - 1) file << ",";
                }
                file << "]," << enemy.index << "}";
                if (i < game.listEnemy.size() - 1) file << ";";
            }
            file << "|";
            for (size_t i = 0; i < game.listTower.size(); ++i) {
                const auto& tower = game.listTower[i];
                file << "{" << tower.location.x << "," << tower.location.y << "}";
                if (i < game.listTower.size() - 1) {
                    file << ";";
                }
            }
            file << "|" << game.mapCode << "|" << game.UserId << "\n";
        }
        file.close();
    }

    // Function to append a single user to the user file
    inline void appendUserToFile(const saveUser& user) {
        std::ofstream file("users.catfam", std::ios::app);
        if (!file) {
            std::cerr << "Error: Could not open users.catfam for appending.\n";
            return;
        }

        file << user.UserId << "|"
            << user.name << "|"
            << user.password << "|";
        for (size_t i = 0; i < user.gameId.size(); ++i) {
            file << user.gameId[i];
            if (i < user.gameId.size() - 1) file << ",";
        }
        file << "\n";
        file.close();
    }

    // Function to append a single game to the game file
    inline void appendGameToFile(const saveGame& game) {
        std::ofstream file("games.catfam", std::ios::app);
        if (!file) {
            std::cerr << "Error: Could not open games.catfam for appending.\n";
            return;
        }

        file << game.gameId << "|";
        for (size_t i = 0; i < game.listEnemy.size(); ++i) {
            const auto& enemy = game.listEnemy[i];
            file << "{"
                << enemy.health << ",{"
                << enemy.currentPosition.x << ","
                << enemy.currentPosition.y << "},[";

            for (size_t j = 0; j < enemy.path.size(); ++j) {
                file << "{" << enemy.path[j].x << "," << enemy.path[j].y << "}";
                if (j < enemy.path.size() - 1) file << ",";
            }

            file << "]," << enemy.index << "}";

            if (i < game.listEnemy.size() - 1) {
                file << ";";
            }
        }
        file << "|";
        for (size_t i = 0; i < game.listTower.size(); ++i) {
            const auto& tower = game.listTower[i];
            file << "{" << tower.location.x << "," << tower.location.y << "}";
            if (i < game.listTower.size() - 1) {
                file << ";";
            }
        }
        file << "|" << game.mapCode << "|" << game.UserId << "\n";
        file.close();
    }

    inline std::vector<saveUser> getUserList() {
        std::vector<saveUser> users;
        std::ifstream file("users.catfam");
        if (!file) {
            std::cerr << "Error: Could not open users.catfam for reading.\n";
            return users;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            saveUser user;

            std::string userID = std::to_string(user.UserId);

            std::getline(ss, userID, '|');
            user.UserId = std::stoi(userID);
            std::getline(ss, user.name, '|');
            std::getline(ss, user.password, '|');
            std::string gameIds;
            std::getline(ss, gameIds, '|');

            std::istringstream gameIdStream(gameIds);
            std::string gameId;
            while (std::getline(gameIdStream, gameId, ',')) {
                user.gameId.push_back(std::stoi(gameId));
            }

            users.push_back(user);
        }

        file.close();
        return users;
    }

    inline std::vector<saveGame> getGameList() {
        std::ifstream file("games.catfam");
        if (!file) {
            std::cerr << "Error: Could not open games.catfam for reading.\n";
            return {};
        }

        std::vector<saveGame> games;
        std::string line;

        while (std::getline(file, line)) {
            try {
                saveGame game;
                std::stringstream ss(line);
                std::string part;

                // Parse gameId
                std::getline(ss, part, '|');
                game.gameId = std::stoi(part);

                // Parse listEnemy
                std::getline(ss, part, '|');
                int allComma = 0;
                for (char c : part) {
                    if (c == ';') allComma++;
                }
                int enemySize = allComma + 1;
                for (int i = 0; i < enemySize; i++) {
                    int indComma = part.find(';');
                    std::string enemyData = (indComma != std::string::npos) ? part.substr(0, indComma) : part;
                    if (indComma != std::string::npos) part = part.substr(indComma + 1);

                    if (enemyData.front() == '{' && enemyData.back() == '}') {
                        saveEnemy enemy;
                        enemyData = enemyData.substr(1, enemyData.size() - 2);
                        std::stringstream enemyStream(enemyData);
                        std::string enemyPart;

                        // Parse health
                        std::getline(enemyStream, enemyPart, ',');
                        enemy.health = std::stoi(enemyPart);


                        // Parse currentPosition
                        std::getline(enemyStream, enemyPart, '[');
                        int commaPos = enemyPart.find(',');
                        enemy.currentPosition.x = std::stoi(enemyPart.substr(1, commaPos - 1));
                        enemy.currentPosition.y = std::stoi(enemyPart.substr(commaPos + 1, enemyPart.size() - commaPos - 1));
                        // std::cout << enemy.currentPosition.x << " " << enemy.currentPosition.y << "\n";


                        std::getline(enemyStream, enemyPart, ']');

                        std::regex pathRegex("\\{([0-9]+),([0-9]+)\\}");
                        std::smatch match;
                        std::string pathData = enemyPart;
                        std::regex_iterator<std::string::iterator> rit(pathData.begin(), pathData.end(), pathRegex);
                        std::regex_iterator<std::string::iterator> rend;
                        while (rit != rend) {
                            int x = std::stoi((*rit)[1].str());
                            int y = std::stoi((*rit)[2].str());
                            POINT pathPoint = { x, y };
                            enemy.path.push_back(pathPoint);
                            ++rit;
                        }

                        // Parse index
                        std::getline(enemyStream, enemyPart);
                        enemy.index = std::stoi(enemyPart.substr(1, enemyPart.size() - 1));

                        game.listEnemy.push_back(enemy);
                    }
                }

                // Parse listTower
                std::getline(ss, part, '|');
                int allComma2 = 0;
                for (char c : part) {
                    if (c == ';') allComma2++;
                }
                int towerSize = allComma2 + 1;
                for (int i = 0; i < towerSize; i++) {
                    int indComma = part.find(';');
                    std::string towerData = (indComma != std::string::npos) ? part.substr(0, indComma) : part;
                    if (indComma != std::string::npos) part = part.substr(indComma + 1);

                    if (towerData.front() == '{' && towerData.back() == '}') {
                        saveTower tower;
                        towerData = towerData.substr(1, towerData.size() - 2);
                        size_t commaPos = towerData.find(',');
                        tower.location.x = std::stoi(towerData.substr(0, commaPos));
                        tower.location.y = std::stoi(towerData.substr(commaPos + 1));

                        game.listTower.push_back(tower);
                    }
                }

                // Parse mapCode
                std::getline(ss, part, '|');
                game.mapCode = std::stoi(part);

                // Parse UserId
                std::getline(ss, part);
                game.UserId = std::stoi(part);

                // Add parsed game to list
                games.push_back(game);
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << "\nReason: " << e.what() << "\n";
            }
        }

        file.close();
        return games;
    }

    // Function to print user data
    inline void printUserData(const std::vector<saveUser>& users) {
        for (const auto& user : users) {
            std::cout << "UserId: " << user.UserId
                << ", Name: " << user.name
                << ", Password: " << user.password
                << ", GameIds: ";
            for (const auto& id : user.gameId) {
                std::cout << id << " ";
            }
            std::cout << "\n";
        }
    }

    // Function to print game data
    inline void printGameData(const std::vector<saveGame>& games) {
        for (const auto& game : games) {
            std::cout << "GameId: " << game.gameId
                << ", MapCode: " << game.mapCode
                << ", UserId: " << game.UserId << "\n";

            // Print enemy data
            for (const auto& enemy : game.listEnemy) {
                std::cout << "  Enemy Health: " << enemy.health
                    << ", Position: (" << enemy.currentPosition.x << ", "
                    << enemy.currentPosition.y << ")\n";

                // Print the path of the enemy
                std::cout << "    Path: ";
                for (const auto& point : enemy.path) {
                    std::cout << "(" << point.x << ", " << point.y << ") ";
                }
                std::cout << "\n";
            }

            // Print tower data
            for (const auto& tower : game.listTower) {
                std::cout << "  Tower Location: (" << tower.location.x << ", "
                    << tower.location.y << ")\n";
            }
        }
    }
}



//int main() {
//    // Create dummy data
//    std::vector<saveUser> users = {
//        {1, "Alice", "password123", {}},
//        {123, "Alice", "password123", {1, 2}},
//        {2332, "Bob", "secret456", {3}},
//        {3, "Charlie", "pass789", {4, 7, 10}}
//    };
//
//    std::vector<saveGame> games = {
//        {1, {{100, {0, 0}, {{10, 10}, {20, 20}}, 0}}, {{5, 5}}, 17, 1},
//        {2, {{200, {1, 1}, {{15, 15}, {25, 25}}, 1}}, {{10, 10}}, 2, 2}
//    };
//
//    createDummyUserDataFile(users);
//    createDummyGameDataFile(games);
//
//    // Append new user and game
//    appendUserToFile({ 55, "Dark", "pass789", {4} });
//    appendGameToFile({ 3, {{300, {2, 2}, {{30, 30}, {40, 40}}, 2}}, {{15, 15}}, 3, 3 });
//    appendGameToFile({ 23, {{4021310, {323, 223}, {{30, 30}, {40, 40}}, 233},
//                           {500, {323, 22213}, {{30, 302}, {40, 41230}}, 222},
//                           {501230, {321233, 223}, {{30, 31230}, {40, 40}}, 212},
//                           {500, {3323, 223}, {{32130, 30}, {43330, 404}}, 23}},
//                    {{15, 15}, {4, 5}}, 3, 3 });
//
//    // Print data
//    printUserData(getUserList());
//    printGameData(getGameList());
//
//    return 0;
//}

