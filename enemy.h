#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QObject>

#include "map.h"

class Enemy : public QObject,public QGraphicsRectItem{
        Q_OBJECT
public:
    Enemy(int x,int y);
    Enemy(int x,int y,Map* eMap);
public slots:
    void find();
    void fall();
private:
    unsigned int health = 1;
    Map* _map;
    int X;
    int Y;
};

#endif // ENEMY_H
