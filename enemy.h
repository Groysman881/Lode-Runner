#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QStack>
#include "hero.h"
#include "map.h"

class Enemy : public QObject,public QGraphicsPixmapItem{
        Q_OBJECT
public:
    Enemy(int x,int y,int z);
    Enemy(int x,int y,int z,Map* eMap);
    ~Enemy();

public slots:
    void find();
    void fall();
    void getDestroyed();
    void updatePath();
signals:
    void killHero();

private:
    unsigned int health = 1;
    Map* _map;
    int X;
    int Y;
    int Z;
    Hero* _hero;
    QStack<int>* fStack;
    int moveHCounter;
    int moveVCounter;
    QTimer* timer1;
};

#endif // ENEMY_H
