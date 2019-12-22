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
    bool isGround(int x,int y,int z);
    bool isStairs(int x,int y, int z);
    int getType(int x,int y, int z);
    void hMoveUp();
    void hMoveDown();
    void hMoveLeft();
    void hMoveRight();
    void setHero(int x,int y,int z);
    int getHeroX();
    int getHeroY();
    int getHeroZ();
    void destroyGItem(int x,int y,int z);
    void setGVector(const QVector<Ground*>& g_vec);
    void setGoldVector(const QVector<Gold*>& gold_vec);
    void destroyGold(int x,int y,int z);
    bool isDestrGround(int x,int y,int z);
    void makeEnemyGround(int x,int y,int z);
    void makeGround(int x,int y,int z);
    bool hIsGround(int x,int y,int z);
    void hideExStairs(int x,int y,int z);
    void addExStairs(int x,int y, int z);
    QStack<int>* findPath(int x,int y,int z);
    size_t countOfGold;
private:
    int gameMap[5][40][30];
    int dMap[40][30];
    QVector<Ground*> groundVec;
    QVector<Gold*> goldVec;
    int heroX;
    int heroY;
    int heroZ;
    struct Coord{
        Coord(int x,int y,int z){
            if(x >= 0 && x <= 40 && y >= 0 && y <= 30){
                _x = x;
                _y = y;
                _z = z;
            }
        }
        int _x;
        int _y;
        int _z;
    };
};

#endif // MAP_H
