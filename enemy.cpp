#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

Enemy::Enemy(int x,int y)
{
    setRect(x,y,20,20);
    QTimer *timer = new QTimer();
    X = x;
    Y = y;
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));
    timer->start(100);

}

Enemy::Enemy(int x,int y,Map* eMap){
    setRect(x,y,20,20);
    X = x;
    Y = y;
    _map = eMap;
    QTimer *timer1 = new QTimer();
    connect(timer1,SIGNAL(timeout()),this,SLOT(fall()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(find()));

    timer1->start(100);
}

void Enemy::find(){
    if(Y/20 == _map->getHeroY()){
        if(X/20 != _map->getHeroX()){
            if(X/20 > _map->getHeroX()){
                setPos(x() - 10,y());
                X-=10;
            }
            else{
                setPos(x() + 10,y());
                X+=10;
            }
        }
    }
    else if(Y!= _map->getHeroY()){}
}

void Enemy::fall(){
    if(!_map->isGround(X/20,Y/20)){
        setPos(x(),y() + 10);
        Y += 10;
        qDebug()<<X/20;
        qDebug()<<Y/20;
        qDebug()<<_map->getHeroY();
    }
    //setPos(x() - 10,y());
}



