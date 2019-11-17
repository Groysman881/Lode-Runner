#ifndef MAP_H
#define MAP_H
#include <QVector>
#include "ground.h"
#include "gold.h"
class Map
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
    void up(int x,int y);
    void down(int x,int y);
    void left(int x,int y);
    void right(int x,int y);
    void destroyGItem(int x,int y);
    void setGVector(const QVector<Ground*>& g_vec);
    void setGoldVector(const QVector<Gold*>& gold_vec);
    void findStairs(int x,int y);
    void destroyGold(int x,int y);
private:
    int gameMap[40][30];
    QVector<Ground*> groundVec;
    QVector<Gold*> goldVec;
    int heroX;
    int heroY;
};

#endif // MAP_H
