#include "map.h"
#include "ground.h"
#include <QVector>
#include <QDebug>
#include <QTimer>

Map::Map() : QObject()
{
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[i][j] = 0;
        }
    }
    gameMap[20][20] = 1;
    gameMap[10][20] = 2;
    for(int i = 0;i < 40;i++){
        gameMap[i][21] = 3;
    }
    for(int i = 0;i < 21;i++){
        gameMap[30][i] = 4;
    }
    for(int i = 0;i < 30;i++){
        gameMap[i][0] = 3;
    }
    gameMap[22][20] = 5;
}

Map::Map(int mas[40][30]) : QObject(){
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[i][j] = mas[i][j];
        }
    }
}

Map::Map(const QVector<Ground*>& g_vec) : QObject(){
    groundVec = g_vec;
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

bool Map::hIsGround(int x, int y){
    if(getType(x,y + 1) == 3 || getType(x,y + 1) == 7){
        return true;
    }
    return false;
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
void Map::hMoveUp(){
    /*gameMap[x][y - 1] = gameMap[x][y];
    gameMap[x][y] = 1;
    gameMap[x][y + 1] = 0;*/
    heroY -= 1;
}

void Map::hMoveDown(){
    //gameMap[x][y + 1] = gameMap[x][y];
    /*gameMap[x][y] = 1;
    gameMap[x][y - 1] = 0;*/
    heroY += 1;
}
void Map::hMoveRight(){
    //gameMap[x + 1][y] = gameMap[x][y];
    /*gameMap[x][y] = 1;
    gameMap[x - 1][y] = 0;*/
    heroX+=1;
}
void Map::hMoveLeft(){
   // gameMap[x - 1][y] = gameMap[x][y];
    /*gameMap[x][y] = 1;
    gameMap[x + 1][y] = 0;*/
    heroX-=1;
}
void Map::setHero(int x, int y){
    heroX = x;
    heroY = y;
    gameMap[x][y] = 0;
}
int Map::getHeroX(){
    return heroX;
}
int Map::getHeroY(){
    return heroY;
}

void Map::destroyGItem(int x,int y){
    for(int i = 0;i < groundVec.size();i++){
        if((groundVec[i]->getX())/20 == x && (groundVec[i]->getY())/20 == y){
           // qDebug()<<"TRUE";
            gameMap[x][y] = 6;
            groundVec[i]->getDestroyed();
            QTimer *timer = new QTimer(this);
             timer->setSingleShot(true);

             connect(timer, &QTimer::timeout, [=]() {
               groundVec[i]->appear();
               gameMap[x][y] = 3;
               timer->deleteLater();
             } );
             timer->start(5000);
            break;
        }
    }
}

void Map::setGVector(const QVector<Ground *> &g_vec){
    for(int i =0;i < g_vec.size();i++){
        //qDebug()<<i;
        groundVec.push_back(g_vec[i]);
    }
}

void Map::setGoldVector(const QVector<Gold *> &gold_vec){
    for(int i =0;i < gold_vec.size();i++){
        goldVec.push_back(gold_vec[i]);
    }
}

int Map::findStairsUp(int x,int y){
   bool isStairs = false;
   int i = 0;
   while(!isStairs){
       if(x - i >= 0 && gameMap[x - i][y] == 4 && gameMap[x - i][y - 1] == 4){
           return x - i;
       }
       else if(x-i <= 40 && gameMap[x + i][y] == 4 && gameMap[x + i][y - 1] == 4){
           return x + i;
       }
       i++;
   }
}

int Map::findStairsDown(int x, int y){
    bool isStairs = false;
    int i = 0;
    while(!isStairs){
        if(gameMap[x][y - i] == 4 && gameMap[x - 1][y + i] == 4){
            return y-i;
        }
        else if(gameMap[x][y + i] == 4 && gameMap[x - 1][y + i] == 4){
            return y+i;
        }
        i++;
    }
}

void Map::destroyGold(int x,int y){
    for(int i = 0;i < goldVec.size();i++){
        if((goldVec[i]->getX())/20 == x && (goldVec[i]->getY())/20 == y){
           // qDebug()<<"TRUE_GOLD";
            goldVec[i]->getDestroyed();
            gameMap[x][y] = 0;
        }
   }
}
bool Map::isDestrGround(int x,int y){
    if(gameMap[x][y + 1] == 6 || gameMap[x][y+1] == 7){
        return true;
    }
    return false;
}

void Map::makeEnemyGround(int x,int y){
    gameMap[x][y] = 7;
}

void Map::makeGround(int x, int y){
    gameMap[x][y] = 3;
}

void Map::makeGraph(int size){
    graph = new int* [size];
    for(int i = 0;i < size;i++){
        graph[i] = new int [size];
    }
}
