#include "hero.h"
#include <QKeyEvent>
#include "game.h"
#include <QList>
#include <QTimer>
#include <QDebug>


Hero::Hero(int x,int y) : QObject()
{
    qDebug()<<"X"<<x;
    qDebug()<<"Y"<<y;
    setPos((qreal)x,(qreal)y);
    setPixmap(QPixmap(":/images/hero1.png"));

    _map = nullptr;
    X = x;
    Y = y;
    moveHCounter = 0;
    moveVCounter = 0;
    isRightMove = true;
}

Hero::Hero(int x,int y,Map* map) : QObject()
{
 //   qDebug()<<"X"<<x;
  //  qDebug()<<"Y"<<y;
    setPos((qreal)x,(qreal)y);
    setPixmap(QPixmap(":/images/hero1.png"));
    //setPos(x + 20,y);
    _map = map;
    moveHCounter = 0;
    moveVCounter = 0;
    X = x;
    Y = y;
    isRightMove = true;
    QTimer *timer = new QTimer();
    connect(timer,SLOT(timeout()),this,SLOT(fall()));
    timer->start(100);
}

Hero::~Hero(){
    delete _map;
}
void Hero::keyPressEvent(QKeyEvent *event)
{
    //QList <QGraphicsItem* > items = collidingItems();
   // qDebug()<<"X1"<<x();
  //  qDebug()<<"Y1"<<y();
  //  qDebug()<<"Type"<<_map->getType(X/20,Y/20);
    //qDebug()<<moveHCounter;

    if(_map != nullptr){
        if(_map->isStairs(X/20,Y/20 + 1) && !_map->isStairs(X/20,Y/20)){
            if(event->key() == Qt::Key_Down){
                setPos(x(),y() + 10);
                Y = Y + 10;
                moveVCounter -= 1;
                if(moveVCounter % 2 == 0 && moveVCounter != 0){
                moveVCounter = 0;
                _map->hMoveDown();
                }
            }
            else if(event->key() == Qt::Key_Right && _map->hIsGround(X/20 + 1,Y / 20)){
                setPos(x() + 10,y());
                X = X + 10;
                moveHCounter+=1;

                if(moveHCounter % 2 == 0 && moveHCounter != 0 ){
                    //qDebug()<<moveHCounter;
                    moveHCounter = 0;
                    _map->hMoveRight();
                }
            }
            else if(event->key() == Qt::Key_Left && _map->hIsGround(X/20 - 1,Y / 20)){
                setPos(x() - 10,y());
                X = X - 10;
                moveHCounter-=1;
                if(moveHCounter % 2 == 0 && moveHCounter != 0){
                    moveHCounter = 0;
                    _map->hMoveLeft();
                }
                isRightMove = false;
            }
        }
        else if(_map->isStairs(X/20,Y/20) && _map->hIsGround(X/20,Y/20)){
            //qDebug()<<"1st case";
            if(event->key() == Qt::Key_Up){
                setPos(x(),y() - 10);
                Y = Y - 10;
                moveVCounter += 1;
                if(moveVCounter % 2 == 0 && moveVCounter != 0){
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
                       // qDebug()<<moveHCounter;
                    moveHCounter = 0;
                    _map->hMoveRight();
                    }
                }
                isRightMove = true;

        }
        else if(_map->isStairs(X/20,Y/20)){
            if(event->key() == Qt::Key_Up){
                setPos(x(),y() - 10);
                Y = Y - 10;
                moveVCounter += 1;
                if(moveVCounter % 2 == 0 && moveVCounter != 0){
                    moveVCounter = 0;
                _map->hMoveUp();
                }
            }
            else if(event->key() == Qt::Key_Down){
                setPos(x(),y() + 10);
                Y = Y + 10;
                moveVCounter -= 1;
                if(moveVCounter % 2 == 0 && moveVCounter != 0){
                moveVCounter = 0;
                _map->hMoveDown();
                }
            }
        }

        else if((_map->hIsGround(X / 20,Y / 20))){
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
                  //  qDebug()<<moveHCounter;
                moveHCounter = 0;
                _map->hMoveRight();
                }
                isRightMove = true;
            }
            else if(event->key() == Qt::Key_Shift){
              //  qDebug()<<"TRUE1";
                if(isRightMove && _map->hIsGround(X/20 + 1,Y/20)){
                    qDebug()<<"RIGHTMOVE";
                    qDebug()<<_map->getType(X/20+1,Y/20 + 1);
                    _map->destroyGItem(X/20 + 1,Y/20 + 1);
                }
                else if(!isRightMove && _map->hIsGround(X/20 - 1,Y/20)){
                    _map->destroyGItem(X/20 - 1,Y/20 + 1);
                }
            }
            /*else if(event->key() == Qt::Key_Down){
                setPos(x(),y() + 10);
                Y += 10;
                moveVCounter -= 1;
                if(moveVCounter % 2 == 0 && moveVCounter != 0){
                moveVCounter = 0;
                }
           }*/
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
              //  qDebug()<<moveHCounter;
            moveHCounter = 0;

            }
        }

    }
}

void Hero::fall(){
    if(!_map->hIsGround(X/20,Y/20)){
        qDebug()<<"FALLLLL";
        setPos(x(),y() + 10);
        Y = Y + 10;
        moveVCounter -= 1;
        if(moveHCounter % 2 == 0 && moveVCounter != 0){
            moveVCounter = 0;
            _map->hMoveDown();
        }
    }
}


