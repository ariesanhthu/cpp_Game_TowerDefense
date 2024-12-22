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
void SaveGame::setEnemyIndex(vector<int> _enemyIndex) {
    this->enemyIndex = _enemyIndex;
}
vector<int> SaveGame::getEnemyIndex() {
    return enemyIndex;
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
void SaveGame::setTowerType(vector<int> type) {
    this->towerType = type;
}
vector<int> SaveGame::getTowerType() {
    return this->towerType;
}
void SaveGame::setEnemyType(vector<int> type) {
    this->enemyType = type;
}
vector<int> SaveGame::getEnemyType() {
    return this->enemyType;
}
SaveGame::SaveGame(string userName,
    vector<cpoint> enemyPos,
    vector<int> enemyHealth,
    vector<int> enemyPathNumber,
    vector<int> enemyIndex,
    vector<int> enemyType,
	vector<cpoint> towerPos,
    vector<int> towerType,
	//vector<cpoint> bulletPos,
	int point,
	int mapCode,
	int userHealth) {
	this->userName = userName;
	this->enemyPos = enemyPos;
	this->enemyHealth = enemyHealth;
	this->enemyPathNumber = enemyPathNumber;
    this->enemyType = enemyType;
    this->enemyIndex = enemyIndex;
	this->towerPos = towerPos;
    this->towerType = towerType;
	//this->bulletPos = bulletPos;
	this->point = point;
	this->mapCode = mapCode;
	this->userHealth = userHealth;
}
SaveGame::SaveGame() {
	this->userName = "guess";
	this->point = 0;

    this->enemyPos = {};
    this->enemyHealth = {};
    this->enemyPathNumber = {};
    this->enemyIndex = {};
    this->enemyType = {};

    this->towerPos = {};
    this->towerType = {};
}

void SaveGame::writefile(int mapCode) {
    std::string filename;
    if (mapCode == 1) {
        filename = "SaveMap1.catfam";
    }
    else if (mapCode == 2) {
        filename = "SaveMap2.catfam";
    }
    else if (mapCode == 3) {
        filename = "SaveMap3.catfam";
    }
    else if (mapCode == 4) {
        filename = "SaveMap4.catfam";
    }
    filename = "Storage/" + filename;

    supportWriteFile(filename);                     // for loadgame
    supportWriteFile("Storage/AllSaveGame.catfam"); // for leaderboard
}

void SaveGame::supportWriteFile(std::string filename) {
    std::ofstream outFile;

    if (filename == "Storage/AllSaveGame.catfam") {
        outFile.open(filename.c_str(), std::ios::binary | std::ios::app);
    } else {
        outFile.open(filename.c_str(), std::ios::binary | std::ios::out);
    }

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Write name
    size_t nameLength = userName.size();
    outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    outFile.write(userName.c_str(), nameLength);

    // Write point and user health and mapCode
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

    // Write enemy path number
    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& path : enemyIndex) {
        outFile.write(reinterpret_cast<char*>(&path), sizeof(path));
    }

    // Write enemy index
    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& index : enemyIndex) {
        outFile.write(reinterpret_cast<char*>(&index), sizeof(index));
    }

    // Write enemy type 
    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& type : enemyType) {
        outFile.write(reinterpret_cast<char*>(&type), sizeof(type));
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

    // Write tower type 
    outFile.write(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    for (auto& type : towerType) {
        outFile.write(reinterpret_cast<char*>(&type), sizeof(type));
    }

    //// Debug userName
    OutputDebugStringA(("Writing userName: " + userName + "\n").c_str());

    // Debug point, userHealth, mapCode
    OutputDebugStringA(("Writing point: " + std::to_string(point) + "\n").c_str());
    OutputDebugStringA(("Writing userHealth: " + std::to_string(userHealth) + "\n").c_str());
    OutputDebugStringA(("Writing mapCode: " + std::to_string(mapCode) + "\n").c_str());

    // Debug enemy positions
    OutputDebugStringA(("Enemy count: " + std::to_string(enemyCount) + "\n").c_str());
    for ( auto& pos : enemyPos) {
        OutputDebugStringA(("Enemy position - x: " + std::to_string(pos.getX()) +
            ", y: " + std::to_string(pos.getY()) +
            ", c: " + std::to_string(pos.getC()) + "\n")
            .c_str());
    }

    // Debug enemy health
    for (size_t i = 0; i < enemyHealth.size(); ++i) {
        OutputDebugStringA(("Enemy health [" + std::to_string(i) + "]: " +
            std::to_string(enemyHealth[i]) + "\n")
            .c_str());
    }

    // Debug enemy path number
    for (size_t i = 0; i < enemyPathNumber.size(); ++i) {
        OutputDebugStringA(("Enemy path [" + std::to_string(i) + "]: " +
            std::to_string(enemyPathNumber[i]) + "\n")
            .c_str());
    }

    // Debug enemy index
    for (size_t i = 0; i < enemyIndex.size(); ++i) {
        OutputDebugStringA(("Enemy index [" + std::to_string(i) + "]: " +
            std::to_string(enemyIndex[i]) + "\n")
            .c_str());
    }

    // Debug enemy type
    for (size_t i = 0; i < enemyType.size(); ++i) {
        OutputDebugStringA(("Enemy type [" + std::to_string(i) + "]: " +
            std::to_string(enemyType[i]) + "\n")
            .c_str());
    }

    // Debug tower positions
    OutputDebugStringA(("Tower count: " + std::to_string(towerCount) + "\n").c_str());
    for ( auto& pos : towerPos) {
        OutputDebugStringA(("Tower position - x: " + std::to_string(pos.getX()) +
            ", y: " + std::to_string(pos.getY()) +
            ", c: " + std::to_string(pos.getC()) + "\n")
            .c_str());
    }

    // Debug tower type
    for (size_t i = 0; i < towerType.size(); ++i) {
        OutputDebugStringA(("Tower type [" + std::to_string(i) + "]: " +
            std::to_string(towerType[i]) + "\n")
            .c_str());
    }


    outFile.close();
}

SaveGameSupport::SaveGameSupport() {
    listGame = readfile();
}

std::vector<SaveGame> SaveGameSupport::readfile() {

    std::ifstream inFile("Storage/AllSaveGame.catfam", std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening save file for reading!\n";
        return {};
    }

    std::vector<SaveGame> savedGames = {};

    while (true) {
        SaveGame game;

        // Read name
        size_t nameLength;
        if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;

        std::string name;
        name.resize(nameLength);
        if (!inFile.read(&name[0], nameLength)) break;
        game.setUserName(name); // Set the name using the setter

        // Read point and user health and mapCode
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

        // Read enemy index
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;
        std::vector<int> enemyIndex(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyIndex.data()), enemyCount * sizeof(int))) break;
        game.setEnemyIndex(enemyIndex); // Use setter

        // Read enemy type
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;
        std::vector<int> enemyType(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyType.data()), enemyCount * sizeof(int))) break;
        game.setEnemyType(enemyType); // Use setter

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


        // Read tower type
        if (!inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount))) break;
        std::vector<int> towerType(towerCount);
        if (!inFile.read(reinterpret_cast<char*>(towerType.data()), towerCount * sizeof(int))) break;
        game.setTowerType(towerType); // Use setter
        



        savedGames.push_back(game);
    }

    inFile.close();
    return savedGames;
}

SaveGame SaveGameSupport::readMapInfo(int x) {
    string filename;
    SaveGame game;
    //for (int i = 1; i <= 4; i++) {
        filename = "Storage/SaveMap" + to_string(x) + ".catfam";
        game = readMap(filename); 
    //}
    return game;
}

// Debug helper function to print messages
void debugOutput(const std::string& message) {
    OutputDebugStringA(message.c_str());
}

// Debug information for readMap function
SaveGame SaveGameSupport::readMap(std::string filename) {
    SaveGame saveGame;
    std::ifstream inFile(filename.c_str(), std::ios::binary);

    if (!inFile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return saveGame;
    }

    std::string debugMessage = "Start reading from file: " + filename + "\n";

    // Read name
    size_t nameLength;
    inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    std::string name(nameLength, '\0');
    inFile.read(&name[0], nameLength);
    saveGame.setUserName(name);
    //debugMessage += "UserName: " + name + "\n";

    // Read point, userHealth, and mapCode
    int point, userHealth, mapCode;
    inFile.read(reinterpret_cast<char*>(&point), sizeof(point));
    inFile.read(reinterpret_cast<char*>(&userHealth), sizeof(userHealth));
    inFile.read(reinterpret_cast<char*>(&mapCode), sizeof(mapCode));
    saveGame.setPoint(point);
    saveGame.setUserHealth(userHealth);
    saveGame.setMapCode(mapCode);
    //debugMessage += "Point: " + std::to_string(point) + ", UserHealth: " + std::to_string(userHealth) + ", MapCode: " + std::to_string(mapCode) + "\n";

    // Read enemy positions
    size_t enemyCount;
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    //debugMessage += "Enemy Count: " + std::to_string(enemyCount) + "\n";
    std::vector<cpoint> enemyPositions;
    for (size_t i = 0; i < enemyCount; ++i) {
        int x, y, c;
        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        inFile.read(reinterpret_cast<char*>(&c), sizeof(c));
        enemyPositions.emplace_back(x, y, c);
        //debugMessage += "Enemy " + std::to_string(i) + " - Pos: (" + std::to_string(x) + ", " + std::to_string(y) + "), Type: " + std::to_string(c) + "\n";
    }
    saveGame.setEnemyPos(enemyPositions);

    // Read enemy health
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    //debugMessage += "Enemy Health Count: " + std::to_string(enemyCount) + "\n";
    std::vector<int> enemyHealth;
    for (size_t i = 0; i < enemyCount; ++i) {
        int health;
        inFile.read(reinterpret_cast<char*>(&health), sizeof(health));
        enemyHealth.push_back(health);
        //debugMessage += "Enemy " + std::to_string(i) + " - Health: " + std::to_string(health) + "\n";
    }
    saveGame.setEnemyHealth(enemyHealth);

    // Read enemy path
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    //debugMessage += "Enemy Path Count: " + std::to_string(enemyCount) + "\n";
    std::vector<int> enemyPathNumber;
    for (size_t i = 0; i < enemyCount; ++i) {
        int path;
        inFile.read(reinterpret_cast<char*>(&path), sizeof(path));
        enemyPathNumber.push_back(path);
        //debugMessage += "Enemy " + std::to_string(i) + " - Path: " + std::to_string(path) + "\n";
    }
    saveGame.setEnemyPathNumber(enemyPathNumber);

    // Read enemy index
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    //debugMessage += "Enemy Index Count: " + std::to_string(enemyCount) + "\n";
    std::vector<int> enemyIndex;
    for (size_t i = 0; i < enemyCount; ++i) {
        int path;
        inFile.read(reinterpret_cast<char*>(&path), sizeof(path));
        enemyIndex.push_back(path);
        //debugMessage += "Enemy " + std::to_string(i) + " - Index: " + std::to_string(path) + "\n";
    }
    saveGame.setEnemyIndex(enemyIndex);

    // Read enemy types
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    //debugMessage += "Enemy Type Count: " + std::to_string(enemyCount) + "\n";
    std::vector<int> enemyTypes;
    for (size_t i = 0; i < enemyCount; ++i) {
        int type;
        inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
        enemyTypes.push_back(type);
        //debugMessage += "Enemy " + std::to_string(i) + " - Type: " + std::to_string(type) + "\n";
    }
    saveGame.setEnemyType(enemyTypes);

    // Read tower positions
    size_t towerCount;
    inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    //debugMessage += "Tower Count: " + std::to_string(towerCount) + "\n";
    std::vector<cpoint> towerPositions;
    for (size_t i = 0; i < towerCount; ++i) {
        int x, y, c;
        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        inFile.read(reinterpret_cast<char*>(&c), sizeof(c));
        towerPositions.emplace_back(x, y, c);
        //debugMessage += "Tower " + std::to_string(i) + " - Pos: (" + std::to_string(x) + ", " + std::to_string(y) + "), Type: " + std::to_string(c) + "\n";
    }
    saveGame.setTowerPos(towerPositions);

    // Read tower types
    inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    //debugMessage += "Tower Type Count: " + std::to_string(towerCount) + "\n";
    std::vector<int> towerTypes;
    for (size_t i = 0; i < towerCount; ++i) {
        int type;
        inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
        towerTypes.push_back(type);
        //debugMessage += "Tower " + std::to_string(i) + " - Type: " + std::to_string(type) + "\n";
    }
    saveGame.setTowerType(towerTypes);

    inFile.close();
    debugMessage += "Finished reading file.\n";
    debugOutput(debugMessage);

    return saveGame;
}


void SaveGameSupport::sortByScore() {
    for (int i = 0; i < listGame.size(); i++) {
        for (int j = i + 1; j < listGame.size(); j++) {
            if (listGame[i].getPoint() < listGame[j].getPoint()) {
                swap(listGame[i], listGame[j]);
            }
        }
    }
}

std::vector<SaveGame> SaveGameSupport::loadFourLastestMapGame() {
    string filename[5];
    vector<SaveGame> games = {};
    for (int i = 1; i <= 4; i++) {
        filename[i] = "Storage/SaveMap" + to_string(i) + ".catfam";
        games.push_back(readMap(filename[i]));
    }
    return games;
}

std::vector<SaveGame> SaveGameSupport::loadFourHighestScoreMap() {
    sortByScore();

    vector<SaveGame> res = {};

    int size = (listGame.size() < 4) ? listGame.size() : 4; 

    for (int i = 0; i < size; i++) {
        res.push_back(listGame[i]);
    }

    return res;
}