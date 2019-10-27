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
private:
    unsigned int health = 1;
    Map* _map;
};

#endif // ENEMY_H
