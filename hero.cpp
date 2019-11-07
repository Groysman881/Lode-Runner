#include "hero.h"
#include <QKeyEvent>
#include "game.h"
#include <QList>
#include <QTimer>
#include <QDebug>


Hero::Hero(int x,int y)
{
    qDebug()<<"X"<<x;
    qDebug()<<"Y"<<y;
    setRect((qreal)x,(qreal)y,20,20);
    //items = collidingItems();
    QTimer *timer = new QTimer();
    _map = nullptr;
    X = x;
    Y = y;
    moveHCounter = 0;
    moveVCounter = 0;
    isRightMove = true;
}

Hero::Hero(int x,int y,Map* map){
    qDebug()<<"X"<<x;
    qDebug()<<"Y"<<y;
    setRect(x,y,20,20);
    //setPos(x + 20,y);
    _map = map;
    moveHCounter = 0;
    moveVCounter = 0;
    X = x;
    Y = y;
    isRightMove = true;

}

void Hero::keyPressEvent(QKeyEvent *event)
{
    //QList <QGraphicsItem* > items = collidingItems();
    qDebug()<<"X1"<<x();
    qDebug()<<"Y1"<<y();
    qDebug()<<"Type"<<_map->getType(X/20,Y/20);
    //qDebug()<<moveHCounter;

    if(_map != nullptr){
        if(_map->isStairs(X/20,Y/20) && _map->isGround(X/20,Y/20)){
            qDebug()<<"1st case";
            if(event->key() == Qt::Key_Up){
                setPos(x(),y() - 10);
                Y = Y - 10;
                moveVCounter += 1;
                if(moveHCounter % 2 == 0 && moveVCounter != 0){
                    moveVCounter = 0;
                _map->hMoveUp();
                }
            }
            /*else if(event->key() == Qt::Key_Down){
                setPos(x(),y() + 10);
                Y = Y + 10;
                moveVCounter -= 1;
                if(moveHCounter % 2 == 0 && moveVCounter != 0){
                moveVCounter = 0;
                _map->moveUp((int)x() / 20,(int)y() / 20);
                }
            }*/
                else if(event->key() == Qt::Key_Left){
                    setPos(x() - 10,y());
                    X = X - 10;
                    moveHCounter-=1;
                    if(moveHCounter % 2 == 0 && moveHCounter != 0){
                    moveHCounter = 0;
                    _map->hMoveLeft();
                    }
                    isRightMove = false;
                }
                else if(event->key() == Qt::Key_Right){
                    setPos(x() + 10,y());
                    X = X + 10;
                    moveHCounter+=1;

                    if(moveHCounter % 2 == 0 && moveHCounter != 0 ){
                        qDebug()<<moveHCounter;
                    moveHCounter = 0;
                    _map->hMoveRight();
                    }
                }
                isRightMove = true;

        }
        else if(_map->isStairs(X / 20,Y / 20)){
            if(event->key() == Qt::Key_Up){
                setPos(x(),y() - 10);
                Y = Y - 10;
                moveVCounter += 1;
                if(moveHCounter % 2 == 0 && moveVCounter != 0){
                    moveVCounter = 0;
                _map->hMoveUp();
                }
            }
            else if(event->key() == Qt::Key_Down){
                setPos(x(),y() + 10);
                Y = Y + 10;
                moveVCounter -= 1;
                if(moveHCounter % 2 == 0 && moveVCounter != 0){
                moveVCounter = 0;
                _map->hMoveUp();
                }
            }
        }

        else if((_map->isGround(X / 20,Y / 20))){
            qDebug() << "TRUE0";
            if(event->key() == Qt::Key_Left){
                setPos(x() - 10,y());
                X = X - 10;
                moveHCounter-=1;
                if(moveHCounter % 2 == 0 && moveHCounter != 0){
                moveHCounter = 0;
                _map->hMoveLeft();
                }
                isRightMove = false;
            }
            else if(event->key() == Qt::Key_Right){
                setPos(x() + 10,y());
                X = X + 10;
                moveHCounter+=1;

                if(moveHCounter % 2 == 0 && moveHCounter != 0 ){
                    qDebug()<<moveHCounter;
                moveHCounter = 0;
                _map->hMoveRight();
                }
                isRightMove = true;
            }
            else if(event->key() == Qt::Key_Shift){
                qDebug()<<"TRUE1";
                if(isRightMove){
                    _map->destroyGItem(X/20 + 1,Y/20 + 1);
                }
                else{
                    _map->destroyGItem(X/20 - 1,Y/20 + 1);
                }
            }
        }
    }
    else{
        if(event->key() == Qt::Key_Up){
            setPos(x(),y() - 20);
            moveVCounter += 1;
            if(moveHCounter % 2 == 0 && moveVCounter != 0){
                moveVCounter = 0;
            }
        }
        else if(event->key() == Qt::Key_Down){
            setPos(x(),y() + 20);
            moveVCounter -= 1;
            if(moveHCounter % 2 == 0 && moveVCounter != 0){
            moveVCounter = 0;
            }
       }
        if(event->key() == Qt::Key_Left){
            setPos(x() - 10,y());
            moveHCounter-=1;
            if(moveHCounter % 2 == 0 && moveHCounter != 0){
            moveHCounter = 0;

            }
        }
        else if(event->key() == Qt::Key_Right){
            setPos(x() + 10,y());
            moveHCounter+=1;

            if(moveHCounter % 2 == 0 && moveHCounter != 0 ){
                qDebug()<<moveHCounter;
            moveHCounter = 0;

            }
        }

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
