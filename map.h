#ifndef MAP_H
#define MAP_H
#include <QVector>
#include "ground.h"
#include "gold.h"
class Map : public QObject
{
public:
    Map();
    Map(const QVector<Ground*>& g_vec);
    Map(int mas[40][30]);
    bool isGround(int x,int y);
    bool isStairs(int x,int y);
    int getType(int x,int y);
    void hMoveUp();
    void hMoveDown();
    void hMoveLeft();
    void hMoveRight();
    void setHero(int x,int y);
    int getHeroX();
    int getHeroY();
    void makeGraph(int size);
    void destroyGItem(int x,int y);
    void setGVector(const QVector<Ground*>& g_vec);
    void setGoldVector(const QVector<Gold*>& gold_vec);
    int findStairsUp(int x,int y);
    int findStairsDown(int x,int y);
    void destroyGold(int x,int y);
    bool isDestrGround(int x,int y);
    void makeEnemyGround(int x,int y);
    void makeGround(int x,int y);
    bool hIsGround(int x,int y);
private:
    int gameMap[40][30];
    int** graph;
    QVector<Ground*> groundVec;
    QVector<Gold*> goldVec;
    int heroX;
    int heroY;
};

#endif // MAP_H
