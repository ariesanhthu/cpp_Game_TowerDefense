#include "cgame.h"

cgame::cgame() {
    _ISEXIT1 = _ISEXIT2 = false;
}
void cgame::startGame() {
    //int nEnemy = map.getEnemy();
    int nEnemy = 1;
    for (int i = 0; i < nEnemy; i++) {
        cenemy e;
        listEnemys.push_back(e);
    }
}

bool cgame::readFile(string filename){
    ifstream inFile(filename, ios::binary);
    if( !inFile.is_open()) return false;

    int mapCode;
    inFile.read((char*) &mapCode, sizeof(int));
    map.readMap(mapCode);

    int size;
    ctower tower;
    inFile.read((char*) &size, sizeof(int));
    listTowers.clear();
    listTowers.resize(size);
    for(int i = 0; i < size; i++){
        inFile.read((char*) &tower, sizeof(ctower));
        listTowers[i] = tower;
    }

    cenemy enemy;
    inFile.read((char*) &size, sizeof(int));
    listEnemys.clear();
    listEnemys.resize(size);
    for(int i = 0; i < size; i++){
        inFile.read((char*) &enemy, sizeof(cenemy));
        listEnemys[i] = enemy;
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
    size_t size = listTowers.size();
    outFile.write((char*) &size, sizeof(int));
    for(ctower tower: listTowers){
        outFile.write((char*) &tower, sizeof(ctower));
    }

    //save listEnermy
    //size of list: sizeof(int) = 4 = n
    //list: sizeof(cenermy) * n
    size = listEnemys.size();
    outFile.write((char*) &size, sizeof(int));
    for(cenemy Enemy: listEnemys){
        outFile.write((char*) &Enemy, sizeof(cenemy));
    }

    outFile.write((char*) &player, sizeof(cplayer));
    return true;
}
