#include "map.h"
#include "ground.h"
#include <QVector>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

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

Map::Map(const QVector<Ground*>& g_vec){
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
    heroY+=1;
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
void Map::up(int x, int y){
    gameMap[x][y - 1] = gameMap[x][y];
    gameMap[x][y] = 0;
}
void Map::down(int x, int y){
    gameMap[x][y + 1] = gameMap[x][y];
    gameMap[x][y] = 0;
}
void Map::left(int x, int y){
    gameMap[x - 1][y] = gameMap[x][y];
    gameMap[x][y] = 0;
}
void Map::right(int x, int y){
    gameMap[x + 1][y] = gameMap[x][y];
    gameMap[x][y] = 0;
}

void Map::destroyGItem(int x,int y){
    for(int i = 0;i < groundVec.size();i++){
        if((groundVec[i]->getX())/20 == x && (groundVec[i]->getY())/20 == y){
            qDebug()<<"TRUE";
            groundVec[i]->getDestroyed();
            gameMap[x][y] = 0;
            QTime dieTime= QTime::currentTime().addSecs(5);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            qDebug()<<"ALERT";
            groundVec[i]->setCurrentScene(groundVec[i-1]->scene());
            groundVec[i]->appear();
            gameMap[x][y] = 3;
            break;
        }
    }
}

void Map::setGVector(const QVector<Ground *> &g_vec){
    for(int i =0;i < g_vec.size();i++){
        qDebug()<<i;
        groundVec.push_back(g_vec[i]);
    }
}
