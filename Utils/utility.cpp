#include "utility.h"
const int LEADERSIZE = 10;
void writeLeaderBoard(cplayer nPlayer){
    ifstream inFile("leaderboard.bin", ios::binary);
    if(!inFile){

        //read curr leaderboard
        int count = 0;
        cplayer listP[LEADERSIZE], temp;
        while(inFile.read((char*) &temp, sizeof(temp))){
            listP[count] = temp;
            count++;
        }
        //find idx for new record
        int idx = count - 1;
        for(idx; idx >= 0; idx--){
            if(nPlayer.getPoint() <= listP[idx].getPoint())
                break;
        }
        //insert new player
        if(count < LEADERSIZE){
            for (int i = count; i > idx + 1; i--) {
                listP[i] = listP[i - 1];
            }
            listP[idx + 1] = nPlayer;
            count++;
        }else if(idx != count - 1){
            for (int i = count - 1; i > idx + 1; i--) {
                listP[i] = listP[i - 1];
            }
            listP[idx + 1] = nPlayer;
        }
        inFile.close();

        ofstream outFile("leaderboard.bin", ios::binary);
        for(int i = 0; i < count; i++){
            outFile.write((char *) &listP[i], sizeof(listP[i]));
        }
        outFile.close();
    }else{
        ofstream outFile("leaderboard.bin", ios::binary);
        outFile.write((char *) &nPlayer, sizeof(cplayer));
        outFile.close();
    }
}

void readLeaderBoard(){
    ifstream inFile("leaderboard.bin", ios::binary);
    if(!inFile) return;
    cplayer player;
    while(inFile.read((char*) &player, sizeof(cplayer))){
        //print player on screen
    }
    inFile.close();
}