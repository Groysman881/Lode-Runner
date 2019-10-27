#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>

Enemy::Enemy(int x,int y)
{
    setRect(x,y,20,20);
    QTimer *timer = new QTimer();
    //connect(timer,SIGNAL(timeout()),this,SLOT(find()));
    //timer->start(100);
}

void Enemy::find(){
    setPos(x() - 10,y());
}


