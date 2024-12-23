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

// Getter and Setter for nOfPhase
int SaveGame::getNOfPhase()  {
    return nOfPhase;
}

void SaveGame::setNOfPhase(int value) {
    nOfPhase = value;
}

// Getter and Setter for nOfEnemyEachPhase
 std::vector<int> SaveGame::getNOfEnemyEachPhase()  {
    return nOfEnemyEachPhase;
}

void SaveGame::setNOfEnemyEachPhase( std::vector<int> value) {
    nOfEnemyEachPhase = value;
}

// Getter and Setter for phase
int SaveGame::getPhase()  {
    return phase;
}

void SaveGame::setPhase(int value) {
    phase = value;
}

// Getter and Setter for remainEnemy
int SaveGame::getRemainEnemy()  {
    return remainEnemy;
}

void SaveGame::setRemainEnemy(int value) {
    remainEnemy = value;
}

// Getter and Setter for nOfEnemy
int SaveGame::getNOfEnemy()  {
    return nOfEnemy;
}

void SaveGame::setNOfEnemy(int value) {
    nOfEnemy = value;
}

// Getter and Setter for spawnedEnemy
int SaveGame::getSpawnedEnemy()  {
    return spawnedEnemy;
}

void SaveGame::setSpawnedEnemy(int value) {
    spawnedEnemy = value;
}



SaveGame::SaveGame
(
    string userName,
    vector<cpoint> enemyPos,
    vector<int> enemyHealth,
    vector<int> enemyPathNumber,
    vector<int> enemyIndex,
    vector<int> enemyType,
	vector<cpoint> towerPos,
    vector<int> towerType,
	//vector<cpoint> bulletPos,

    int nOfPhase,
    vector<int> nOfEnemyEachPhase,
    int phase,
    int remainEnemy,
    int nOfEnemy,
    int spawnedEnemy,

	int point,
	int mapCode,
	int userHealth) 
{
	this->userName = userName;

	this->enemyPos = enemyPos;
	this->enemyHealth = enemyHealth;
	this->enemyPathNumber = enemyPathNumber;
    this->enemyType = enemyType;
    this->enemyIndex = enemyIndex;

	this->towerPos = towerPos;
    this->towerType = towerType;
	//this->bulletPos = bulletPos;

    this->nOfPhase = nOfPhase;
    this->nOfEnemyEachPhase = nOfEnemyEachPhase;
    this->phase = phase;
    this->remainEnemy = remainEnemy;
    this->nOfEnemy = nOfEnemy;
    this->spawnedEnemy = spawnedEnemy;

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
    //supportWriteFile("Storage/AllSaveGame.catfam"); // for leaderboard
}

void SaveGame::supportWriteFile(std::string filename) {
    std::ofstream outFile;

    if (filename == "Storage/AllSaveGame.catfam") {
        outFile.open(filename.c_str(), std::ios::binary | std::ios::app);
    }
    else {
        outFile.open(filename.c_str(), std::ios::binary | std::ios::out);
    }

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    /*thứ tự ghi
    name 
    point
    user health 
    map Code
    
    enemyPos
    enemyHealth
    enemyPath 
    enemy index
    enemy type
    towerpos
    towertype 

    no of phase
    nOfEnemyEachPhase
    phase,
    remainEnemy,
    nOfEnemy, 
    spawnedEnemy*/

    // Ghi các trường đã có
    size_t nameLength = userName.size();
    outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    outFile.write(userName.c_str(), nameLength);
    outFile.write(reinterpret_cast<char*>(&point), sizeof(point));
    outFile.write(reinterpret_cast<char*>(&userHealth), sizeof(userHealth));
    outFile.write(reinterpret_cast<char*>(&mapCode), sizeof(mapCode));

    size_t enemyCount = enemyPos.size();
    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& pos : enemyPos) {
        int x = pos.getX(), y = pos.getY(), c = pos.getC();
        outFile.write(reinterpret_cast<char*>(&x), sizeof(x));
        outFile.write(reinterpret_cast<char*>(&y), sizeof(y));
        outFile.write(reinterpret_cast<char*>(&c), sizeof(c));
    }

    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& health : enemyHealth) {
        outFile.write(reinterpret_cast<char*>(&health), sizeof(health));
    }

    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& path : enemyPathNumber) {
        outFile.write(reinterpret_cast<char*>(&path), sizeof(path));
    }

    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& index : enemyIndex) {
        outFile.write(reinterpret_cast<char*>(&index), sizeof(index));
    }

    outFile.write(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    for (auto& type : enemyType) {
        outFile.write(reinterpret_cast<char*>(&type), sizeof(type));
    }

    size_t towerCount = towerPos.size();
    outFile.write(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    for (auto& pos : towerPos) {
        int x = pos.getX(), y = pos.getY(), c = pos.getC();
        outFile.write(reinterpret_cast<char*>(&x), sizeof(x));
        outFile.write(reinterpret_cast<char*>(&y), sizeof(y));
        outFile.write(reinterpret_cast<char*>(&c), sizeof(c));
    }

    outFile.write(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    for (auto& type : towerType) {
        outFile.write(reinterpret_cast<char*>(&type), sizeof(type));
    }

    // Ghi nOfPhase
    outFile.write(reinterpret_cast<char*>(&nOfPhase), sizeof(nOfPhase));

    // Ghi nOfEnemyEachPhase
    /*size_t phaseCount = nOfEnemyEachPhase.size();
    outFile.write(reinterpret_cast<char*>(&phaseCount), sizeof(phaseCount));*/
    for (auto& count : nOfEnemyEachPhase) {
        outFile.write(reinterpret_cast<char*>(&count), sizeof(count));
    }

    // Ghi phase, remainEnemy, nOfEnemy, spawnedEnemy
    outFile.write(reinterpret_cast<char*>(&phase), sizeof(phase));
    outFile.write(reinterpret_cast<char*>(&remainEnemy), sizeof(remainEnemy));
    outFile.write(reinterpret_cast<char*>(&nOfEnemy), sizeof(nOfEnemy));
    outFile.write(reinterpret_cast<char*>(&spawnedEnemy), sizeof(spawnedEnemy));

    // Debug output
    std::ostringstream debugMessage;
    debugMessage << "File written successfully: " << filename << "\n"
        << "1. Name: " << userName << "\n"
        << "2. Points: " << point << "\n"
        << "3. User Health: " << userHealth << "\n"
        << "4. Map Code: " << mapCode << "\n"
        << "5. Enemy Count: " << enemyCount << "\n"
        << "6. Enemy Health: [ ";
    for (const auto& health : enemyHealth) debugMessage << health << " ";
    debugMessage << "]\n"
        << "7. Enemy Path: [ ";
    for (const auto& path : enemyPathNumber) debugMessage << path << " ";
    debugMessage << "]\n"
        << "8. Enemy Index: [ ";
    for (const auto& index : enemyIndex) debugMessage << index << " ";
    debugMessage << "]\n"
        << "9. Enemy Type: [ ";
    for (const auto& type : enemyType) debugMessage << type << " ";
    debugMessage << "]\n"
        << "10. Tower Count: " << towerCount << "\n"
        << "11. Tower Type: [ ";
    for (const auto& type : towerType) debugMessage << type << " ";
    debugMessage << "]\n"
        << "12. Number of Phases: " << nOfPhase << "\n"
        << "13. Enemies Each Phase: [ ";
    for (const auto& count : nOfEnemyEachPhase) debugMessage << count << " ";
    debugMessage << "]\n"
        << "14. Current Phase: " << phase << "\n"
        << "15. Remaining Enemies: " << remainEnemy << "\n"
        << "16. Total Enemies: " << nOfEnemy << "\n"
        << "17. Spawned Enemies: " << spawnedEnemy << "\n";

    OutputDebugStringA(debugMessage.str().c_str());

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

    std::vector<SaveGame> savedGames;

    while (true) {
        SaveGame game;

        // 1. Read name
        size_t nameLength;
        if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;

        std::string name(nameLength, '\0');
        if (!inFile.read(&name[0], nameLength)) break;
        game.setUserName(name);

        // 2. Read point
        int point;
        if (!inFile.read(reinterpret_cast<char*>(&point), sizeof(point))) break;
        game.setPoint(point);

        // 3. Read user health
        int health;
        if (!inFile.read(reinterpret_cast<char*>(&health), sizeof(health))) break;
        game.setUserHealth(health);

        // 4. Read map code
        int mapCode;
        if (!inFile.read(reinterpret_cast<char*>(&mapCode), sizeof(mapCode))) break;
        game.setMapCode(mapCode);

        // 5. Read enemy positions
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
        game.setEnemyPos(enemyPos);

        // 6. Read enemy health
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;
        std::vector<int> enemyHealth(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyHealth.data()), enemyCount * sizeof(int))) break;
        game.setEnemyHealth(enemyHealth);

        // 7. Read enemy path numbers
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;
        std::vector<int> enemyPathNumbers(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyPathNumbers.data()), enemyCount * sizeof(int))) break;
        game.setEnemyPathNumber(enemyPathNumbers);

        // 8. Read enemy indices
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;
        std::vector<int> enemyIndex(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyIndex.data()), enemyCount * sizeof(int))) break;
        game.setEnemyIndex(enemyIndex);

        // 9. Read enemy types
        if (!inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount))) break;
        std::vector<int> enemyType(enemyCount);
        if (!inFile.read(reinterpret_cast<char*>(enemyType.data()), enemyCount * sizeof(int))) break;
        game.setEnemyType(enemyType);

        // 10. Read tower positions
        size_t towerCount;
        if (!inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount))) break;

        std::vector<cpoint> towerPos(towerCount);
        for (size_t i = 0; i < towerCount; ++i) {
            int x, y, c;
            if (!inFile.read(reinterpret_cast<char*>(&x), sizeof(x))) break;
            if (!inFile.read(reinterpret_cast<char*>(&y), sizeof(y))) break;
            if (!inFile.read(reinterpret_cast<char*>(&c), sizeof(c))) break;
            towerPos[i] = cpoint(x, y, c);
        }
        game.setTowerPos(towerPos);

        // 11. Read tower types
        if (!inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount))) break;
        std::vector<int> towerType(towerCount);
        if (!inFile.read(reinterpret_cast<char*>(towerType.data()), towerCount * sizeof(int))) break;
        game.setTowerType(towerType);

        // 12. Read number of phases
        int nOfPhase;
        if (!inFile.read(reinterpret_cast<char*>(&nOfPhase), sizeof(nOfPhase))) break;
        game.setNOfPhase(nOfPhase);

        // 13. Read enemies per phase
        /*size_t phaseCount;
        if (!inFile.read(reinterpret_cast<char*>(&phaseCount), sizeof(phaseCount))) break;*/

        //std::vector<int> nOfEnemyEachPhase(phaseCount);
        std::vector<int> nOfEnemyEachPhase(nOfPhase);
        if (!inFile.read(reinterpret_cast<char*>(nOfEnemyEachPhase.data()), nOfPhase * sizeof(int))) break;
        game.setNOfEnemyEachPhase(nOfEnemyEachPhase);

        // 14. Read current phase
        int phase;
        if (!inFile.read(reinterpret_cast<char*>(&phase), sizeof(phase))) break;
        game.setPhase(phase);

        // 15. Read remaining enemies
        int remainEnemy;
        if (!inFile.read(reinterpret_cast<char*>(&remainEnemy), sizeof(remainEnemy))) break;
        game.setRemainEnemy(remainEnemy);

        // 16. Read number of enemies
        int nOfEnemy;
        if (!inFile.read(reinterpret_cast<char*>(&nOfEnemy), sizeof(nOfEnemy))) break;
        game.setNOfEnemy(nOfEnemy);

        // 17. Read spawned enemies
        int spawnedEnemy;
        if (!inFile.read(reinterpret_cast<char*>(&spawnedEnemy), sizeof(spawnedEnemy))) break;
        game.setSpawnedEnemy(spawnedEnemy);

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
void debugOutput( std::string& message) {
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

    // 1. Read name
    size_t nameLength;
    inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    std::string name(nameLength, '\0');
    inFile.read(&name[0], nameLength);
    saveGame.setUserName(name);

    // 2. Read point
    int point;
    inFile.read(reinterpret_cast<char*>(&point), sizeof(point));
    saveGame.setPoint(point);

    // 3. Read user health
    int userHealth;
    inFile.read(reinterpret_cast<char*>(&userHealth), sizeof(userHealth));
    saveGame.setUserHealth(userHealth);

    // 4. Read map code
    int mapCode;
    inFile.read(reinterpret_cast<char*>(&mapCode), sizeof(mapCode));
    saveGame.setMapCode(mapCode);

    // 5. Read enemy positions
    size_t enemyCount;
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    std::vector<cpoint> enemyPositions(enemyCount);
    for (size_t i = 0; i < enemyCount; ++i) {
        int x, y, c;
        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        inFile.read(reinterpret_cast<char*>(&c), sizeof(c));
        enemyPositions[i] = cpoint(x, y, c);
    }
    saveGame.setEnemyPos(enemyPositions);

    // 6. Read enemy health
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    std::vector<int> enemyHealth(enemyCount);
    for (size_t i = 0; i < enemyCount; ++i) {
        int health;
        inFile.read(reinterpret_cast<char*>(&health), sizeof(health));
        enemyHealth[i] = health;
    }
    saveGame.setEnemyHealth(enemyHealth);

    // 7. Read enemy path
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    std::vector<int> enemyPathNumber(enemyCount);
    for (size_t i = 0; i < enemyCount; ++i) {
        int path;
        inFile.read(reinterpret_cast<char*>(&path), sizeof(path));
        enemyPathNumber[i] = path;
    }
    saveGame.setEnemyPathNumber(enemyPathNumber);

    // 8. Read enemy index
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    std::vector<int> enemyIndex(enemyCount);
    for (size_t i = 0; i < enemyCount; ++i) {
        int index;
        inFile.read(reinterpret_cast<char*>(&index), sizeof(index));
        enemyIndex[i] = index;
    }
    saveGame.setEnemyIndex(enemyIndex);

    // 9. Read enemy types
    inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
    std::vector<int> enemyTypes(enemyCount);
    for (size_t i = 0; i < enemyCount; ++i) {
        int type;
        inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
        enemyTypes[i] = type;
    }
    saveGame.setEnemyType(enemyTypes);

    // 10. Read tower positions
    size_t towerCount;
    inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    std::vector<cpoint> towerPositions(towerCount);
    for (size_t i = 0; i < towerCount; ++i) {
        int x, y, c;
        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        inFile.read(reinterpret_cast<char*>(&c), sizeof(c));
        towerPositions[i] = cpoint(x, y, c);
    }
    saveGame.setTowerPos(towerPositions);

    // 11. Read tower types
    inFile.read(reinterpret_cast<char*>(&towerCount), sizeof(towerCount));
    std::vector<int> towerTypes(towerCount);
    for (size_t i = 0; i < towerCount; ++i) {
        int type;
        inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
        towerTypes[i] = type;
    }
    saveGame.setTowerType(towerTypes);

    // 12. Read number of phases
    int nOfPhase;
    inFile.read(reinterpret_cast<char*>(&nOfPhase), sizeof(nOfPhase));
    saveGame.setNOfPhase(nOfPhase);

    // 13. Read number of enemies in each phase
    std::vector<int> nOfEnemyEachPhase(nOfPhase);
    for (int i = 0; i < nOfPhase; ++i) {
        int enemyCount;
        inFile.read(reinterpret_cast<char*>(&enemyCount), sizeof(enemyCount));
        nOfEnemyEachPhase[i] = enemyCount;
    }
    saveGame.setNOfEnemyEachPhase(nOfEnemyEachPhase);

    // 14, 15, 16, 17 Read phase details
    int phase, remainEnemy, nOfEnemy, spawnedEnemy;
    inFile.read(reinterpret_cast<char*>(&phase), sizeof(phase));
    inFile.read(reinterpret_cast<char*>(&remainEnemy), sizeof(remainEnemy));
    inFile.read(reinterpret_cast<char*>(&nOfEnemy), sizeof(nOfEnemy));
    inFile.read(reinterpret_cast<char*>(&spawnedEnemy), sizeof(spawnedEnemy));

    // Set phase details in SaveGame object
    saveGame.setPhase(phase);
    saveGame.setRemainEnemy(remainEnemy);
    saveGame.setNOfEnemy(nOfEnemy);
    saveGame.setSpawnedEnemy(spawnedEnemy);

    inFile.close();
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