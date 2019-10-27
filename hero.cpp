#include "hero.h"
#include <QKeyEvent>
#include "game.h"
#include <QList>
#include <QTimer>
#include <QDebug>


Hero::Hero(int x,int y)
{
    setRect(x,y,20,20);
    //items = collidingItems();
    QTimer *timer = new QTimer();
}

Hero::Hero(int x,int y,Map* map){
    qDebug()<<(qreal)x;
    qDebug()<<(qreal)y;
    setRect(x,y,20,20);
    //setPos(x + 20,y);
    _map = map;
    moveHCounter = 0;
    moveVCounter = 0;
}

void Hero::keyPressEvent(QKeyEvent *event)
{
    //QList <QGraphicsItem* > items = collidingItems();
    qDebug()<<x();
    qDebug()<<y();
    //qDebug()<<moveHCounter;

    if(_map->isStairs((int)x() / 20,(int)y() / 20)){
        if(event->key() == Qt::Key_Up){
            setPos(x(),y() - 20);
            moveVCounter += 1;
            if(moveHCounter % 2 == 0 && moveVCounter != 0){
            moveVCounter = 0;
            _map->moveUp((int)x() / 20,(int)y() / 20);
            }
        }
        else if(event->key() == Qt::Key_Down){
            setPos(x(),y() + 20);
            moveVCounter -= 1;
            if(moveHCounter % 2 == 0 && moveVCounter != 0){
            moveVCounter = 0;
            _map->moveUp((int)x() / 20,(int)y() / 20);
            }
        }
    }

    else if((_map->isGround((int)x() / 20,(int)y() / 20))){
        qDebug() << _map->getType((int)x(),(int)y() + 1);
        if(event->key() == Qt::Key_Left){
            setPos(x() - 10,y());
            moveHCounter-=1;
            if(moveHCounter % 2 == 0 && moveHCounter != 0){
            moveHCounter = 0;
            _map->moveLeft((int)x() / 20,(int)y() / 20);
            }
        }
        else if(event->key() == Qt::Key_Right){
            setPos(x() + 10,y());
            moveHCounter+=1;

            if(moveHCounter % 2 == 0 && moveHCounter != 0 ){
                qDebug()<<moveHCounter;
            moveHCounter = 0;
            _map->moveRight((int)x() / 20,(int)y() / 20);
            }
        }

        //else if(event->key() == Qt::Key_Up){
            //setPos(x(),y() - 10);
        //}
        //else if(event->key() == Qt::Key_Down){
            //setPos(x(),y() + 10);
        //}
    }



}

        /*if(event->key() == Qt::Key_Left){
        setPos(x() - 10,y());
    }
    else if(event->key() == Qt::Key_Right){
        setPos(x() + 10,y());
    }
    else if(event->key() == Qt::Key_Up){
        setPos(x(),y() - 10);
    }
    else if(event->key() == Qt::Key_Down){
        setPos(x(),y() + 10);
    }*/

void Hero::fall(){
    setPos(x(),y() + 20);
}
