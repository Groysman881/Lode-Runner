#ifndef MAP_H
#define MAP_H
#include <QVector>
#include <QStack>
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
    void hideExStairs(int x,int y);
    void addExStairs(int x,int y);
    QStack<int>* findPath(int x,int y);
    size_t countOfGold;
private:
    int gameMap[40][30];
    int dMap[40][30];
    QVector<Ground*> groundVec;
    QVector<Gold*> goldVec;
    int heroX;
    int heroY;
    struct Coord{
        Coord(int x,int y){
            if(x >= 0 && x <= 40 && y >= 0 && y <= 30){
                _x = x;
                _y = y;
            }
        }
        int _x;
        int _y;
    };
};

#endif // MAP_H
