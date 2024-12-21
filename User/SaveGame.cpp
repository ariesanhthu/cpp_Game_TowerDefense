#include "SaveGame.h"

void SaveGame::setUserName(string userName) {
	this->userName = userName;
}
string SaveGame::getUserName() {
	return userName;
}
void SaveGame::setEnemyPos(vector<cpoint> enemyPos) {
	this->enemyPos = enemyPos;
}
vector<cpoint> SaveGame::getEnemyPos() {
	return enemyPos;
}
void SaveGame::setEnemyHealth(vector<int> enemyHealth) {
	this->enemyHealth = enemyHealth;
}
vector<int> SaveGame::getEnemyHealth() {
	return enemyHealth;
}
void SaveGame::setEnemyPathNumber(vector<int> enemyPathNumber) {
	this->enemyPathNumber = enemyPathNumber;
}
vector<int> SaveGame::getEnemyPathNumber() {
	return enemyPathNumber;
}
void SaveGame::setTowerPos(vector<cpoint> towerPos) {
	this->towerPos = towerPos;
}
vector<cpoint> SaveGame::getTowerPos() {
	return towerPos;
}
//void SaveGame::setBulletPos(vector<cpoint> bulletPos) {
//	this->bulletPos = bulletPos;
//}
//vector<cpoint> SaveGame::getBulletPos() {
//	return bulletPos;
//}
void SaveGame::setPoint(int point) {
	this->point = point;
}
int SaveGame::getPoint() {
	return point;
}
void SaveGame::setMapCode(int mapCode) {
	this->mapCode = mapCode;
}
int SaveGame::getMapCode() {
	return mapCode;
}
int SaveGame::getUserHealth() {
	return userHealth;
}
void SaveGame::setUserHealth(int userHealth) {
	this->userHealth = userHealth;
}
SaveGame::SaveGame(string userName,
	vector<cpoint> enemyPos,
	vector<int> enemyHealth,
	vector<int> enemyPathNumber,
	vector<cpoint> towerPos,
	//vector<cpoint> bulletPos,
	int point,
	int mapCode,
	int userHealth) {
	this->userName = userName;
	this->enemyPos = enemyPos;
	this->enemyHealth = enemyHealth;
	this->enemyPathNumber = enemyPathNumber;
	this->towerPos = towerPos;
	//this->bulletPos = bulletPos;
	this->point = point;
	this->mapCode = mapCode;
	this->userHealth = userHealth;
}
SaveGame::SaveGame() {
	this->userName = "guess";
	this->point = 0;
}
void SaveGame::writefile() {
    std::ofstream outFile("Storage/saveGame.catfam", std::ios::binary | std::ios::app);

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Write name
    size_t nameLength = userName.size();
    outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    outFile.write(userName.c_str(), nameLength);

    // Write point and health and mapCode
    outFile.write(reinterpret_cast<char*>(&point), sizeof(point));
    outFile.write(reinterpret_cast<char*>(&userHealth), sizeof(userHealth));
    outFile.write(reinterpret_cast<char*>(&mapCode), sizeof(mapCode));

    // Write enemy positions
    size_t enemyCount = enemyPos.size();
    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& pos : enemyPos) {
        int x = pos.getX(), y = pos.getY(), c = pos.getC();
        outFile.write(reinterpret_cast<char*>(&x), sizeof(x));
        outFile.write(reinterpret_cast<char*>(&y), sizeof(y));
        outFile.write(reinterpret_cast<char*>(&c), sizeof(c));
    }

    // Write enemy health
    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& health : enemyHealth) {
        outFile.write(reinterpret_cast<char*>(&health), sizeof(health));
    }

    // Write enemy path numbers
    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& path : enemyPathNumber) {
        outFile.write(reinterpret_cast<char*>(&path), sizeof(path));
    }

    // Write tower positions
    size_t towerCount = towerPos.size();
    outFile.write(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    for (auto& pos : towerPos) {
        int x = pos.getX(), y = pos.getY(), c = pos.getC();
        outFile.write(reinterpret_cast<char*>(&x), sizeof(x));
        outFile.write(reinterpret_cast<char*>(&y), sizeof(y));
        outFile.write(reinterpret_cast<char*>(&c), sizeof(c));
    }

    outFile.close();
}

std::vector<SaveGame> SaveGameSupport::readfile() {

    std::ifstream inFile("Storage/saveGame.catfam", std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening save file for reading!\n";
        return {};
    }

    std::vector<SaveGame> savedGames;

    while (true) {
        SaveGame game;

        // Read name
        size_t nameLength;
        if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;

        std::string name;
        name.resize(nameLength);
        if (!inFile.read(&name[0], nameLength)) break;
        game.setUserName(name); // Set the name using the setter

        // Read point and health and mapCode
        int point, health, mapCode;
        if (!inFile.read(reinterpret_cast<char*>(&point), sizeof(point))) break;
        if (!inFile.read(reinterpret_cast<char*>(&health), sizeof(health))) break;
        if (!inFile.read(reinterpret_cast<char*>(&mapCode), sizeof(mapCode))) break;
        game.setPoint(point); // Use setter
        game.setUserHealth(health); // Use setter
        game.setMapCode(mapCode);

        // Read enemy positions
        size_t enemyCount;
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;

        std::vector<cpoint> enemyPos(enemyCount);
        for (size_t i = 0; i < enemyCount; ++i) {
            int x, y, c;
            if (!inFile.read(reinterpret_cast<char*>(&x), sizeof(x))) break;
            if (!inFile.read(reinterpret_cast<char*>(&y), sizeof(y))) break;
            if (!inFile.read(reinterpret_cast<char*>(&c), sizeof(c))) break;
            enemyPos[i] = cpoint(x, y, c);
        }
        game.setEnemyPos(enemyPos); // Set using the setter

        // Read enemy health
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;

        std::vector<int> enemyHealth(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyHealth.data()), enemyCount * sizeof(int))) break;
        game.setEnemyHealth(enemyHealth); // Use setter

        // Read enemy path numbers
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;

        std::vector<int> enemyPathNumbers(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyPathNumbers.data()), enemyCount * sizeof(int))) break;
        game.setEnemyPathNumber(enemyPathNumbers); // Use setter

        // Read tower positions
        size_t towerCount;
        if (!inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount))) break;

        std::vector<cpoint> towerPositions(towerCount);
        for (size_t i = 0; i < towerCount; ++i) {
            int x, y, c;
            if (!inFile.read(reinterpret_cast<char*>(&x), sizeof(x))) break;
            if (!inFile.read(reinterpret_cast<char*>(&y), sizeof(y))) break;
            if (!inFile.read(reinterpret_cast<char*>(&c), sizeof(c))) break;
            towerPositions[i] = cpoint(x, y, c);
        }
        game.setTowerPos(towerPositions); // Use setter

        savedGames.push_back(game);
    }

    inFile.close();
    return savedGames;
}

