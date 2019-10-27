#include "map.h"

Map::Map()
{
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[i][j] = 0;
        }
    }
    gameMap[20][20] = 1;
    gameMap[10][2] = 2;
    for(int i = 0;i < 40;i++){
        gameMap[i][21] = 3;
    }
    for(int i = 0;i < 21;i++){
        gameMap[30][i] = 4;
    }
}

Map::Map(int mas[40][30]){
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[i][j] = mas[i][j];
        }
    }
}

bool Map::isGround(int x, int y){
    if(getType(x,y + 1) == 3){
        return true;
    }
    return false;
}
bool Map::isStairs(int x, int y){
    if(getType(x,y) == 4){
        return true;
    }
    return false;
}
int Map::getType(int x,int y){
    return gameMap[x][y];
}
void Map::moveUp(int x,int y){
    gameMap[x][y - 1] = gameMap[x][y];
    gameMap[x][y] = 0;
}

void Map::moveDown(int x, int y){
    gameMap[x][y + 1] = gameMap[x][y];
    gameMap[x][y] = 0;
}
void Map::moveRight(int x, int y){
    gameMap[x + 1][y] = gameMap[x][y];
    gameMap[x][y] = 0;
}
void Map::moveLeft(int x, int y){
    gameMap[x - 1][y] = gameMap[x][y];
    gameMap[x][y] = 0;
}
