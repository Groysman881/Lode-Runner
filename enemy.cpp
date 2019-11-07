#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>

Enemy::Enemy(int x,int y)
{
    setRect(x,y,20,20);
    QTimer *timer = new QTimer();
    X = x;
    Y = y;
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));
    timer->start(100);
   /*if(!_map->isGround(X/20,Y/20)){
        fall();
    }*/
}

Enemy::Enemy(int x,int y,Map* eMap){
    setRect(x,y,20,20);
    X = x;
    Y = y;
    _map = eMap;
    QTimer *timer = new QTimer();
    /*if(!_map->isGround(X/20,Y/20)){
            fall();
    }*/
    if(!_map->isGround(X/20,Y/20)){
        connect(timer,SIGNAL(timeout()),this,SLOT(fall()));
        timer->start(100);
    }
}

void Enemy::find(){
    setPos(x() - 10,y());
    _map->left(X/20,Y/20);
}

void Enemy::fall(){
    setPos(x(),y() + 10);
    _map->down(X/20,Y/20);
}


