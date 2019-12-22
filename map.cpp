#include "map.h"
#include "ground.h"
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QQueue>

Map::Map() : QObject()
{

    for(int i = 0;i < 40;i++){
            for(int j = 0;j < 30;j++){
                gameMap[0][i][j] = 0;
                gameMap[1][i][j] = 0;
                gameMap[2][i][j] = 0;
                gameMap[3][i][j] = 0;
                gameMap[4][i][j] = 0;
            }
        }
    for(int i = 0;i < 40;i++){
        gameMap[0][i][10] = 3;
    }
    for(int i  = 0;i < 40;i++){
        gameMap[2][i][20] = 3;
    }
    for(int i = 0;i < 20;i++){
      gameMap[2][10 + i][10] = 3;
    }
    for(int i = 0;i < 16;i++){
       gameMap[3][i][20] = 3;
       gameMap[3][39 - i][20] = 3;
    }
    for(int i = 0;i < 11;i++){
        gameMap[2][9][9 + i] = 4;
        gameMap[2][30][9 + i] = 4;
        gameMap[3][ i][11]  =3;
        gameMap[3][39 - i][11] = 3;
    }
    for(int i = 0;i < 10;i++){
        gameMap[2][15][i+ 18] = 4;
        gameMap[2][24][i + 18] = 4;
        gameMap[3][15][i + 18]  = 4;
        gameMap[3][24][i + 18] = 4;
        gameMap[2][20][i] = 10;
        gameMap[3][33][i + 10] = 4;
        gameMap[3][7][i + 10] = 4;
    }
    for(int i = 0;i < 40;i++){
        gameMap[0][i][29] = 3;
        gameMap[0][i][28] = 3;
        gameMap[1][i][29] = 3;
        gameMap[1][i][28] = 3;
        gameMap[2][i][29] = 3;
        gameMap[2][i][28] = 3;
        gameMap[3][i][29] = 3;
        gameMap[3][i][28] = 3;
        gameMap[1][i][5] = 3;
        gameMap[1][i][15] = 3;
        gameMap[0][i][0] = 3;
        gameMap[1][i][0] = 3;
        gameMap[2][i][0] = 3;
        gameMap[3][i][0] = 3;
    }
    for(int i = 0;i < 30;i++){
        gameMap[0][0][i] = 3;
        gameMap[0][39][i] = 3;
        gameMap[1][0][i] = 3;
        gameMap[1][39][i] = 3;
        gameMap[2][0][i] = 3;
        gameMap[2][39][i] = 3;
        gameMap[3][0][i] = 3;
        gameMap[3][39][i] = 3;
        gameMap[0][30][i] = 4;
        gameMap[0][10][i] = 4;
        gameMap[1][15][i] = 4;
        gameMap[1][2][i] = 4;
    }
    gameMap[0][9][9] = 2;
    gameMap[0][9][27] = 2;
    gameMap[0][8][27] = 2;
    gameMap[1][10][4] = 2;
    gameMap[1][30][14] = 2;
    gameMap[0][20][27] = 1;gameMap[3][20][27] =1;
    gameMap[1][20][27] = 1;
    gameMap[2][32][19] = 1;gameMap[2][4][19] = 2;
    gameMap[0][15][9] = 5;gameMap[2][4][27] = 2; gameMap[3][37][10] = 2;
    gameMap[1][5][4] = 5;gameMap[2][2][27] = 5; gameMap[3][4][27] = 5;
    gameMap[1][18][4] = 5;gameMap[2][18][9] = 5; gameMap[3][6][10]  = 5;
    gameMap[1][20][14] = 5;gameMap[2][36][19]= 5;gameMap[3][3][10] = 2;
    gameMap[1][3][14] = 5;gameMap[2][3][19] = 5;
    for(int i =0;i < 10;i++){
        gameMap[0][2][i] = 10;
    }
    for(int i = 0;i < 5;i++){
        gameMap[1][30][i] = 10;
    }
    for(int i = 0;i < 11;i++){
        gameMap[3][4][i]  = 10;
    }
}

Map::Map(int mas[40][30]) : QObject(){
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[0][i][j] = mas[i][j];
        }
    }
}

Map::Map(const QVector<Ground*>& g_vec) : QObject(){
    groundVec = g_vec;
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[0][i][j] = 0;
        }
    }
    gameMap[0][20][20] = 1;
    gameMap[0][10][2] = 2;
    for(int i = 0;i < 40;i++){
        gameMap[0][i][21] = 3;
    }
    for(int i = 0;i < 21;i++){
        gameMap[0][30][i] = 4;
    }
}

bool Map::hIsGround(int x, int y,int z){
    if(getType(x,y + 1,z) == 3 || getType(x,y + 1,z) == 7 || getType(x,y + 1,z) == 6){
        return true;
    }
    return false;
}

bool Map::isGround(int x, int y,int z){
    if(getType(x,y + 1,z) == 3){
        return true;
    }
    return false;
}
bool Map::isStairs(int x, int y,int z){
    if(getType(x,y,z) == 4 || getType(x,y,z) == 10){
        return true;
    }
    return false;
}
int Map::getType(int x,int y,int z){
    return gameMap[z][x][y];
}
void Map::hMoveUp(){
    heroY--;
}

void Map::hMoveDown(){
    heroY++;
}
void Map::hMoveRight(){
    heroX++;
}
void Map::hMoveLeft(){
    heroX--;
}
void Map::setHero(int x, int y,int z){
    heroX = x;
    heroY = y;
    heroZ = z;
    gameMap[z][x][y] = 0;
}
int Map::getHeroX(){
    return heroX;
}
int Map::getHeroY(){
    return heroY;
}

void Map::destroyGItem(int x,int y,int z){
    for(int i = 0;i < groundVec.size();i++){
        if((groundVec[i]->getX())/20 == x && (groundVec[i]->getY())/20 == y){
           qDebug()<<"TRUE";
            gameMap[z][x][y] = 6;
            if(!groundVec[i]->isDestroyed){
            groundVec[i]->getDestroyed();
            qDebug()<<"getDestroyed()";
            QTimer *timer = new QTimer(this);
             timer->setSingleShot(true);

             connect(timer, &QTimer::timeout, [=]() {
               groundVec[i]->appear();
               gameMap[z][x][y] = 3;
               groundVec[i]->isDestroyed = false;
               timer->deleteLater();
             }
              );
             timer->start(5000);}
            break;
        }
    }
}

void Map::setGVector(const QVector<Ground *> &g_vec){
    if(!groundVec.isEmpty()){
        groundVec.clear();
    }
    for(int i =0;i < g_vec.size();i++){
        //qDebug()<<i;
        groundVec.push_back(g_vec[i]);
    }
}

void Map::setGoldVector(const QVector<Gold *> &gold_vec){
    if(!goldVec.isEmpty()){
        goldVec.clear();
    }
    for(int i =0;i < gold_vec.size();i++){
        goldVec.push_back(gold_vec[i]);
    }
}

void Map::destroyGold(int x,int y,int z){
    for(int i = 0;i < goldVec.size();i++){
        if((goldVec[i]->getX())/20 == x && (goldVec[i]->getY())/20 == y){
            goldVec[i]->getDestroyed();
            gameMap[z][x][y] = 0;
        }
   }
}
bool Map::isDestrGround(int x,int y,int z){
    if(gameMap[z][x][y + 1] == 6){
        return true;
    }
    return false;
}

void Map::makeEnemyGround(int x,int y,int z){
    gameMap[z][x][y] = 7;
}

void Map::makeGround(int x, int y,int z){
    gameMap[z][x][y] = 3;
}

QStack<int>* Map::findPath(int x,int y,int z){
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            dMap[i][j] = 2147483646;
        }
    }
    QQueue<Map::Coord> queue;
        dMap[x][y] = 0;
        queue.push_back(Coord(x,y,z));
    while(!queue.isEmpty() && dMap[heroX][heroY] == 2147483646){
        Coord point = queue.front();
        queue.pop_front();
        if(isStairs(point._x,point._y,point._z)){
            if((dMap[point._x - 1][point._y] >  dMap[point._x][point._y] + 1) && hIsGround(point._x - 1,point._y,point._z)){
                dMap[point._x - 1][point._y] =  dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x - 1,point._y,point._z));
            }
            if((dMap[point._x + 1][point._y] >  dMap[point._x][point._y] + 1) && hIsGround(point._x + 1,point._y,point._z)){
                dMap[point._x + 1][point._y] =  dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x + 1,point._y,point._z));
            }
            if(dMap[point._x][point._y + 1] > dMap[point._x][point._y] + 1 ){
                dMap[point._x][point._y + 1] = dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x,point._y + 1,point._z));
            }
            if(dMap[point._x][point._y - 1] > dMap[point._x][point._y] + 1){
                dMap[point._x][point._y - 1] = dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x,point._y - 1,point._z));
            }
        }
        if(hIsGround(point._x,point._y,point._z)){
            if(dMap[point._x + 1][point._y] > dMap[point._x][point._y] + 1){
                dMap[point._x + 1][point._y] = dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x + 1,point._y,point._z));
            }
            if(dMap[point._x - 1][point._y] > dMap[point._x][point._y] + 1){
                dMap[point._x - 1][point._y] = dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x - 1,point._y,point._z));
            }
        }
    }
    QStack<int>* stack = new QStack<int>;
    int hX = heroX;
    int hY = heroY;
    int tmp = dMap[hX][hY];
    while(tmp > 0){
        if(tmp > dMap[hX][hY + 1]){  
            stack->push(1);
            hY++;
        }
        else if(tmp > dMap[hX][hY - 1]){
            stack->push(2);
            hY--;
        }
        else if(tmp > dMap[hX + 1][hY]){
            stack->push(3);
            hX++;
        }

        else if(tmp > dMap[hX - 1][hY]){
            stack->push(4);
            hX--;
        }
        tmp--;
    }
    return stack;
}

void Map::hideExStairs(int x, int y,int z){
    gameMap[z][x][y] = 0;
}

void Map::addExStairs(int x,int y,int z){
    gameMap[z][x][y] = 10;
}

int Map::getHeroZ(){
    return heroZ;
}
