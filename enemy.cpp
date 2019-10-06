#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>

Enemy::Enemy()
{
    setRect(30,-100,20,20);
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(find()));
    timer->start(100);
}

void Enemy::find(){
    setPos(x() - 10,y());
}
