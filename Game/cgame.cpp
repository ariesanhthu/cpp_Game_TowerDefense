#include "cgame.h"

cgame::cgame() {
    _ISEXIT1 = _ISEXIT2 = false;
}
void cgame::startGame() {
    //int nEnemy = map.getEnemy();
    int nEnemy = 1;
    for (int i = 0; i < nEnemy; i++) {
        cenemy e;
        listEnemy.push_back(e);
    }
}

bool cgame::readFile(string filename){
    ifstream inFile(filename + ".twdef", ios::binary);
    if (!inFile.is_open()) return false;

    int mapCode;
    inFile.read((char*) &mapCode, sizeof(int));
    map.readMap(mapCode);
    int size;
    ctower tower;
    inFile.read((char*) &size, sizeof(int));
    listTower.clear();
    listTower.resize(size);
    for(int i = 0; i < size; i++){
        inFile.read((char*) &tower, sizeof(ctower));
        listTower[i] = tower;
    }

    cenemy enemy;
    inFile.read((char*) &size, sizeof(int));
    listEnemy.clear();
    listEnemy.resize(size);
    for(int i = 0; i < size; i++){
        /*inFile.read((char*) &enemy, sizeof(cenemy));*/
        enemy.readFile(inFile);
        listEnemy[i] = enemy;
    }
    
    inFile.read((char*) &player, sizeof(cplayer));
    return true;
}


bool cgame::saveGame(string playerName){
    string filename = playerName + ".twdef";
    ofstream outFile(filename, ios::binary);

    if(!outFile.is_open()) return false;

    // save mapCode: sizeof(int) = 4
    int mapCode = map.getMapCode();
    outFile.write((char*) &mapCode, sizeof(int));
    
    //save listTower
    //size of list: sizeof(int) = 4 = n
    //list: sizeof(ctower) * n
    size_t size = listTower.size();
    outFile.write((char*) &size, sizeof(int));
    for(ctower tower: listTower){
        outFile.write((char*) &tower, sizeof(ctower));
    }

    //save listEnermy
    //size of list: sizeof(int) = 4 = n
    //list: sizeof(cenermy) * n
    size = listEnemy.size();
    outFile.write((char*) &size, sizeof(int));
    for(cenemy Enemy: listEnemy){
        Enemy.writeFile(outFile);
        //outFile.write((char*) &Enemy, sizeof(cenemy));
    }

    outFile.write((char*) &player, sizeof(cplayer));
    return true;
}
