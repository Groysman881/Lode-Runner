#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "map.h"

class Enemy : public QObject,public QGraphicsPixmapItem{
        Q_OBJECT
public:
    Enemy(int x,int y);
    Enemy(int x,int y,Map* eMap);
public slots:
    void find();
    void fall();
    void getDestroyed();

private:
    unsigned int health = 1;
    Map* _map;
    int X;
    int Y;
    //int moveHCounter;
    //int moveVCounter;
};

#endif // ENEMY_H
