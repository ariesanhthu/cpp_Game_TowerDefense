#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>

// Enemy class element
struct enemy {
    int health;
    POINT currentPosition;
    std::vector<POINT> path;
    int index;
};

struct tower {
    POINT location;
};

struct sUser {
    int UserId;
    std::string name;
    std::string password;
    int point;
    std::vector<int> gameId;
};

struct sGame {
    int gameId;

    // ENEMY variable 
    std::vector<enemy> Ecurr; // Vector of enemy

    // TOWER variable 
    std::vector<tower> Tcurr; // Vector of tower

    int mapCode;
    int UserId;
};

// Function to create and save dummy user data
inline void createDummyUserDataFile(const std::vector<sUser>& dummy) {
    std::ofstream file("users.catfam");
    if (!file) {
        std::cerr << "Error: Could not open users.catfam for writing.\n";
        return;
    }
    for (const auto& user : dummy) {
        file << user.UserId << '|' << user.name << '|' << user.password << '|' << user.point << '\n';
    }
    file.close();
}

// Function to create and save dummy game data
inline void createDummyGameDataFile(const std::vector<sGame>& dummy) {
    std::ofstream file("games.catfam");
    if (!file) {
        std::cerr << "Error: Could not open games.catfam for writing.\n";
        return;
    }
    for (const auto& game : dummy) {
        file << game.gameId << '|' << game.mapCode << '|' << game.UserId << '\n';
        for (const auto& enemy : game.Ecurr) {
            file << enemy.health << ',' << enemy.currentPosition.x << ',' << enemy.currentPosition.y;
            // Add path data
            file << ":";
            for (const auto& point : enemy.path) {
                file << point.x << ',' << point.y << '|';
            }
            file << ';';
        }
        file << '\n';
        for (const auto& tower : game.Tcurr) {
            file << tower.location.x << ',' << tower.location.y << ';';
        }
        file << '\n';
    }
    file.close();
}

// Function to append a single user to the user file
inline void appendUserToFile(const sUser& user) {
    std::ofstream file("users.catfam", std::ios::app); // Open file in append mode
    if (!file) {
        std::cerr << "Error: Could not open users.catfam for appending.\n";
        return;
    }
    file << user.UserId << '|' << user.name << '|' << user.password << '|' << user.point << '\n';
    file.close();
}

// Function to append a single game to the game file
inline void appendGameToFile(const sGame& game) {
    std::ofstream file("games.catfam", std::ios::app); // Open file in append mode
    if (!file) {
        std::cerr << "Error: Could not open games.catfam for appending.\n";
        return;
    }

    // Write game metadata
    file << game.gameId << '|' << game.mapCode << '|' << game.UserId << '\n';

    // Write enemy data
    for (const auto& enemy : game.Ecurr) {
        file << enemy.health << ',' << enemy.currentPosition.x << ',' << enemy.currentPosition.y;
        // Write path data
        file << ":";
        for (const auto& point : enemy.path) {
            file << point.x << ',' << point.y << '|';
        }
        file << ';';
    }
    file << '\n'; // End of enemy data

    // Write tower data
    for (const auto& tower : game.Tcurr) {
        file << tower.location.x << ',' << tower.location.y << ';';
    }
    file << '\n'; // End of tower data

    file.close();
}

// Function to read the user list from the file
inline std::vector<sUser> getUserList() {
    std::vector<sUser> users;
    std::ifstream file("users.catfam");
    if (!file) {
        std::cerr << "Error: Could not open users.catfam for reading.\n";
        return users;
    }
    std::string line;
    while (std::getline(file, line)) {
        sUser user;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
            std::cerr << "Error: Malformed line in users.catfam: " << line << '\n';
            continue;
        }
        user.UserId = std::stoi(line.substr(0, pos1));
        user.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        user.password = line.substr(pos2 + 1, pos3 - pos2 - 1);
        user.point = std::stoi(line.substr(pos3 + 1));
        users.push_back(user);
    }
    file.close();
    return users;
}

// Function to read the game list from the file
inline std::vector<sGame> getGameList() {
    std::vector<sGame> games;
    std::ifstream file("games.catfam");
    if (!file) {
        std::cerr << "Error: Could not open games.catfam for reading.\n";
        return games;
    }
    std::string line;
    while (std::getline(file, line)) {
        sGame game;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        game.gameId = std::stoi(line.substr(0, pos1));
        game.mapCode = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        game.UserId = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));

        // Read enemies
        std::getline(file, line);
        size_t pos = 0;
        while ((pos = line.find(';')) != std::string::npos) {
            std::string enemyData = line.substr(0, pos);
            size_t p1 = enemyData.find(',');
            size_t p2 = enemyData.find(',', p1 + 1);
            size_t p3 = enemyData.find(':');
            enemy enemy;
            enemy.health = std::stoi(enemyData.substr(0, p1));
            enemy.currentPosition.x = std::stoi(enemyData.substr(p1 + 1, p2 - p1 - 1));
            enemy.currentPosition.y = std::stoi(enemyData.substr(p2 + 1, p3 - p2 - 1));

            // Parse path data
            std::string pathData = enemyData.substr(p3 + 1);
            size_t pathPos = 0;
            while ((pathPos = pathData.find('|')) != std::string::npos) {
                std::string pointData = pathData.substr(0, pathPos);
                size_t pp = pointData.find(',');
                POINT point;
                point.x = std::stoi(pointData.substr(0, pp));
                point.y = std::stoi(pointData.substr(pp + 1));
                enemy.path.push_back(point);
                pathData.erase(0, pathPos + 1);
            }

            game.Ecurr.push_back(enemy);
            line.erase(0, pos + 1);
        }

        // Read towers
        std::getline(file, line);
        while ((pos = line.find(';')) != std::string::npos) {
            std::string towerData = line.substr(0, pos);
            size_t p1 = towerData.find(',');
            tower tower;
            tower.location.x = std::stoi(towerData.substr(0, p1));
            tower.location.y = std::stoi(towerData.substr(p1 + 1));
            game.Tcurr.push_back(tower);
            line.erase(0, pos + 1);
        }

        games.push_back(game);
    }
    file.close();
    return games;
}

// Function to print user data
inline void printUserData(const std::vector<sUser>& users) {
    for (const auto& user : users) {
        std::cout << "User ID: " << user.UserId
            << ", Name: " << user.name
            << ", Password: " << user.password
            << ", Point: " << user.point << '\n';
    }
}

// Function to print game data
inline void printGameData(const std::vector<sGame>& games) {
    for (const auto& game : games) {
        std::cout << "Game ID: " << game.gameId
            << ", Map Code: " << game.mapCode
            << ", User ID: " << game.UserId << '\n';
        std::cout << "Enemies:\n";
        for (const auto& enemy : game.Ecurr) {
            std::cout << "\tHealth: " << enemy.health
                << ", Position: (" << enemy.currentPosition.x << ", " << enemy.currentPosition.y << ")\n";
            std::cout << "\tPath: ";
            for (const auto& point : enemy.path) {
                std::cout << "(" << point.x << ", " << point.y << ") ";
            }
            std::cout << '\n';
        }
        std::cout << "Towers:\n";
        for (const auto& tower : game.Tcurr) {
            std::cout << "\tLocation: (" << tower.location.x << ", " << tower.location.y << ")\n";
        }
    }
}

//int main() {
//    // Example usage
//    std::vector<sUser> users = {
//        {1, "Alice", "password123", 100, {1}},
//        {2, "Bob", "secret456", 150, {2}}
//    };
//
//    std::vector<sGame> games = {
//        {1, {{100, {0, 0}, {{10, 10}, {20, 20}}, 0}}, {{5, 5}}, 1, 1},
//        {2, {{200, {1, 1}, {{15, 15}, {25, 25}}, 1}}, {{10, 10}}, 2, 2}
//    };
//
//    createDummyUserDataFile(users);
//    createDummyGameDataFile(games);
//
//    // Optionally append user or game
//    appendUserToFile({ 3, "Charlie", "pass789", 200, {3} });
//    appendGameToFile({ 3, {{300, {2, 2}, {{30, 30}, {40, 40}}, 2}}, {{15, 15}}, 3, 3 });
//
//    // Print data
//    printUserData(getUserList());
//    printGameData(getGameList());
//
//    return 0;
//}
