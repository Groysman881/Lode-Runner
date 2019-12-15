#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QStack>
#include "hero.h"
#include "map.h"

/*struct Counter{
    int _counter;
    Counter(): _counter(0){};
    void operator++(int){_counter++;if(_counter%2 == 0 && _counter != 0){_counter = 0;}}
    void operator--(int){_counter--;if(_counter%2 == 0 && _counter != 0){_counter = 0;}}
    bool operator==(int num){if(_counter == num){return true;} return false;}
};*/

class Enemy : public QObject,public QGraphicsPixmapItem{
        Q_OBJECT
public:
    Enemy(int x,int y);
    Enemy(int x,int y,Map* eMap, Hero* h);
public slots:
    void find();
    void fall();
    void getDestroyed();
    void updatePath();
private:
    unsigned int health = 1;
    Map* _map;
    int X;
    int Y;
    Hero* _hero;
    QStack<int>* fStack;
    int moveHCounter;
    int moveVCounter;
};

#endif // ENEMY_H
