#include "map.h"
#include "ground.h"
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QQueue>

Map::Map() : QObject()
{
   /* for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[i][j] = 0;
        }
    }

    for(int i = 0;i < 40;i++){
        gameMap[i][21] = 3;
    }
    for(int i = 0;i < 21;i++){
        gameMap[30][i] = 4;
    }
    for(int i = 0;i < 30;i++){
        gameMap[i][0] = 3;
    }
    for(int i = 0 ;i < 30;i++){
        gameMap[i][9] = 3;
    }
    gameMap[22][20] = 5;
    gameMap[20][8] = 2;
    heroX = 20;
    heroY = 20;*/
    countOfGold = 1;
    for(int i = 0;i < 40;i++){
            for(int j = 0;j < 30;j++){
                gameMap[i][j] = 0;
            }
        }
    for(int i = 0;i < 40;i++){

        gameMap[i][10] = 3;

    }
    for(int i = 0;i < 30;i++){
        gameMap[0][i] = 3;
        gameMap[39][i] = 3;
        gameMap[30][i] = 4;
        gameMap[10][i] = 4;

    }

    for(int i = 0;i < 40;i++){
        gameMap[i][29] = 3;
        gameMap[i][28] = 3;
        gameMap[i][0] = 3;

    }
    gameMap[9][9] = 2;
    gameMap[9][27] = 2;
    gameMap[8][27] = 2;
    gameMap[15][9] = 5;
    for(int i =0;i < 10;i++){
        gameMap[2][i] = 10;
    }
    heroX = 20;
    heroY = 27;

}

Map::Map(int mas[40][30]) : QObject(){
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[i][j] = mas[i][j];
        }
    }
    countOfGold = 1;
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
    if(getType(x,y + 1) == 3 || getType(x,y + 1) == 7 || getType(x,y + 1) == 6){
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
    if(getType(x,y) == 4 || getType(x,y) == 10){
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
    heroY--;
}

void Map::hMoveDown(){
    //gameMap[x][y + 1] = gameMap[x][y];
    /*gameMap[x][y] = 1;
    gameMap[x][y - 1] = 0;*/
    heroY++;
}
void Map::hMoveRight(){
    //gameMap[x + 1][y] = gameMap[x][y];
    /*gameMap[x][y] = 1;
    gameMap[x - 1][y] = 0;*/
    heroX++;
}
void Map::hMoveLeft(){
   // gameMap[x - 1][y] = gameMap[x][y];
    /*gameMap[x][y] = 1;
    gameMap[x + 1][y] = 0;*/
    heroX--;
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

QStack<int>* Map::findPath(int x,int y){


    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            dMap[i][j] = 2147483646;
        }
    }
    QQueue<Map::Coord> queue;
    //qDebug()<<"QUEUE";
   /* if(isGround(x,y)){
        dMap[x][y + 1] = 0;
        queue.push_back(Coord(x,y + 1));
    }
    else{*/

        dMap[x][y] = 0;
        queue.push_back(Coord(x,y));

    qDebug()<<queue.isEmpty();

    while(!queue.isEmpty() && dMap[heroX][heroY] == 2147483646){
       // qDebug()<<"MainWhile";
        Coord point = queue.front();
        queue.pop_front();
        if(isStairs(point._x,point._y)){
          //  qDebug()<<"dStairs";
            if((dMap[point._x - 1][point._y] >  dMap[point._x][point._y] + 1) && isGround(point._x - 1,point._y)){
                dMap[point._x - 1][point._y] =  dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x - 1,point._y));
            }
            if((dMap[point._x + 1][point._y] >  dMap[point._x][point._y] + 1) && isGround(point._x + 1,point._y)){
                dMap[point._x + 1][point._y] =  dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x + 1,point._y));
            }
            if(dMap[point._x][point._y + 1] > dMap[point._x][point._y] + 1 ){
                dMap[point._x][point._y + 1] = dMap[point._x][point._y] + 1;
               // qDebug()<<"down";
                queue.push_back(Coord(point._x,point._y + 1));
            }
            if(dMap[point._x][point._y - 1] > dMap[point._x][point._y] + 1){
                dMap[point._x][point._y - 1] = dMap[point._x][point._y] + 1;
              //  qDebug()<<"up";
                queue.push_back(Coord(point._x,point._y - 1));
            }
            /*if((dMap[point._x - 1][point._y] >  dMap[point._x][point._y] + 1) && isGround(point._x - 1,point._y)){
                dMap[point._x - 1][point._y] =  dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x - 1,point._y));
            }
            if((dMap[point._x + 1][point._y] >  dMap[point._x][point._y] + 1) && isGround(point._x + 1,point._y)){
                dMap[point._x + 1][point._y] =  dMap[point._x][point._y] + 1;
                queue.push_back(Coord(point._x + 1,point._y));
            }*/
        }
        if(hIsGround(point._x,point._y)){
          //   qDebug()<<"dGround";
            if(dMap[point._x + 1][point._y] > dMap[point._x][point._y] + 1){
                dMap[point._x + 1][point._y] = dMap[point._x][point._y] + 1;
           //     qDebug()<<"right";
                queue.push_back(Coord(point._x + 1,point._y));
            }
            if(dMap[point._x - 1][point._y] > dMap[point._x][point._y] + 1){
                dMap[point._x - 1][point._y] = dMap[point._x][point._y] + 1;
           //     qDebug()<<"left";
                queue.push_back(Coord(point._x - 1,point._y));
            }
        }
    }
  //  qDebug()<<"BeforeStack";
    QStack<int>* stack = new QStack<int>;
    int hX = heroX;
    int hY = heroY;
    int tmp = dMap[hX][hY];
  //  qDebug()<<tmp;
    while(tmp > 0){
        if(tmp > dMap[hX][hY + 1]){
         //   qDebug()<<"1";
            stack->push(1);

            hY++;
        }
        else if(tmp > dMap[hX][hY - 1]){
         //    qDebug()<<"2";
            stack->push(2);

            hY--;
        }
        else if(tmp > dMap[hX + 1][hY]){
         //    qDebug()<<"3";
            stack->push(3);

            hX++;
        }

        else if(tmp > dMap[hX - 1][hY]){
         //    qDebug()<<"4";
            stack->push(4);

            hX--;
        }
        tmp--;
    }

    return stack;

}

void Map::hideExStairs(int x, int y){
    gameMap[x][y] = 0;
}

void Map::addExStairs(int x,int y){
    gameMap[x][y] = 10;
}
