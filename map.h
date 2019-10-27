#ifndef MAP_H
#define MAP_H


class Map
{
public:
    Map();
    Map(int mas[40][30]);
    bool isGround(int x,int y);
    bool isStairs(int x,int y);
    int getType(int x,int y);
    void moveUp(int x,int y);
    void moveDown(int x,int y);
    void moveLeft(int x,int y);
    void moveRight(int x,int y);
private:
    int gameMap[40][30];
};

#endif // MAP_H
