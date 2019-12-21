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
    setPixmap(QPixmap(":/new/images/hero1.png"));
    _map = nullptr;
    X = x;
    Y = y;
    moveHCounter = 0;
    moveVCounter = 0;
    isRightMove = true;
    goldCounter = 0;
    exit = false;
}

Hero::Hero(int x,int y,Map* map) : QObject()
{
    setPos((qreal)x,(qreal)y);
    setPixmap(QPixmap(":/new/images/hero1.png"));
    //setPos(x + 20,y);
    _map = map;
    moveHCounter = 0;
    moveVCounter = 0;
    X = x;
    Y = y;
    isRightMove = true;
    QTimer *timer = new QTimer();
    //connect(timer,SIGNAL(timeout()),this,SLOT(getGold()));
    connect(this,SIGNAL(signalUpdate()),this,SLOT(getGold()));
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));
    connect(this,SIGNAL(signalUpdate()),this,SLOT(isExit()));
    timer->start(100);
    goldCounter = 0;
    exit = false;
}

Hero::~Hero(){
    delete _map;
}
void Hero::keyPressEvent(QKeyEvent *event)
{
    if(_map != nullptr){
        if(_map->isStairs(X/20,Y/20 + 1) && !_map->isStairs(X/20,Y/20)){
            if(event->key() == Qt::Key_Down && moveHCounter == 0){
                setPos(x(),y() + 10);
                Y = Y + 10;
                moveVCounter--;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                _map->hMoveDown();
                moveVCounter = 0;
                emit signalUpdate();
                }
            }
            else if(event->key() == Qt::Key_Right && _map->hIsGround(X/20 + 1,Y / 20)){
                setPos(x() + 10,y());
                X = X + 10;
                moveHCounter++;


                if(moveHCounter %2 == 0  && moveHCounter != 0){
                _map->hMoveRight();
                 moveHCounter = 0;
                 emit signalUpdate();
                }
            }
            else if(event->key() == Qt::Key_Left  && _map->hIsGround(X/20 - 1,Y / 20)){
                setPos(x() - 10,y());
                X = X - 10;
                moveHCounter--;
                if(moveHCounter %2 == 0  && moveHCounter != 0){
                _map->hMoveLeft();
                 moveHCounter = 0;
                 emit signalUpdate();
                }
                isRightMove = false;
            }
        }
        else if(_map->isStairs(X/20,Y/20) && _map->hIsGround(X/20,Y/20)){
            //qDebug()<<"1st case";
            if(event->key() == Qt::Key_Up && moveHCounter == 0){
                setPos(x(),y() - 10);
                Y = Y - 10;
                moveVCounter++;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                _map->hMoveUp();
                 moveVCounter = 0;
                 emit signalUpdate();
                }
            }
            else if(event->key() == Qt::Key_Left  && !_map->hIsGround(X/20 - 1,Y / 20 - 1) ){
                qDebug()<<_map->getHeroX();
                qDebug()<<_map->getHeroY();
                qDebug()<<"LLEFT";
                    setPos(x() - 10,y());
                    X = X - 10;
                    moveHCounter--;
                    if(moveHCounter %2 == 0  && moveHCounter != 0){
                    _map->hMoveLeft();
                     moveHCounter = 0;
                     emit signalUpdate();
                    }
                    isRightMove = false;
                }
                else if(event->key() == Qt::Key_Right  && !_map->hIsGround(X/20 + 1,Y / 20 - 1) ){
                    setPos(x() + 10,y());
                    X = X + 10;
                    moveHCounter++;
                    if(moveHCounter %2 == 0  && moveHCounter != 0){
                    _map->hMoveRight();
                     moveHCounter = 0;
                     emit signalUpdate();
                    }
                }
                isRightMove = true;

        }
        else if(_map->isStairs(X/20,Y/20)){
            if(event->key() == Qt::Key_Up ){
                setPos(x(),y() - 10);
                Y = Y - 10;
                moveVCounter++;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                _map->hMoveUp();
                 moveVCounter = 0;
                 emit signalUpdate();
                }
            }
            else if(event->key() == Qt::Key_Down ){
                setPos(x(),y() + 10);
                Y = Y + 10;
                moveVCounter--;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                _map->hMoveDown();
                 moveVCounter = 0;
                 emit signalUpdate();
                }
            }
            if(event->key() == Qt::Key_Left && !_map->hIsGround(X/20 - 1, Y/20 - 1) && _map->hIsGround(X/20 - 1,Y/20) && moveVCounter == 0){
                setPos(x() - 10,y());
                X = X - 10;
                moveHCounter--;
                if(moveHCounter %2 == 0  && moveHCounter != 0){
                _map->hMoveLeft();
                 moveHCounter = 0;
                 emit signalUpdate();
                }
                isRightMove = false;
            }
            else if(event->key() == Qt::Key_Right && !_map->hIsGround(X/20 + 1 , Y/20 - 1) && _map->hIsGround(X/20 + 1,Y/20) && moveVCounter == 0){
                setPos(x() + 10,y());
                X = X + 10;
                moveHCounter++;
                if(moveHCounter %2 == 0 && moveHCounter != 0){
                _map->hMoveRight();
                 moveHCounter = 0;
                 emit signalUpdate();
                }
                isRightMove = true;
            }
        }

        else if((_map->hIsGround(X / 20,Y / 20))){
          //  qDebug() << "TRUE0";
            if(event->key() == Qt::Key_Left && !_map->hIsGround(X/20 - 1, Y/20 - 1)){
                setPos(x() - 10,y());
                X = X - 10;
                moveHCounter--;
                if(moveHCounter %2 == 0  && moveHCounter!= 0){
                _map->hMoveLeft();
                 moveHCounter = 0;
                 emit signalUpdate();
                }
                isRightMove = false;
            }
            else if(event->key() == Qt::Key_Right && !_map->hIsGround(X/20 + 1 , Y/20 - 1)){
                setPos(x() + 10,y());
                X = X + 10;
                moveHCounter++;
                if(moveHCounter %2 == 0  && moveHCounter != 0){
                _map->hMoveRight();
                 moveHCounter = 0;
                 emit signalUpdate();
                }
                isRightMove = true;
            }
            else if(event->key() == Qt::Key_Shift){
              //  qDebug()<<"TRUE1";
                if(isRightMove && _map->hIsGround(X/20 + 1,Y/20)){
               //     qDebug()<<"RIGHTMOVE";
                //    qDebug()<<_map->getType(X/20+1,Y/20 + 1);
                    _map->destroyGItem(X/20 + 1,Y/20 + 1);
                }
                else if(!isRightMove && _map->hIsGround(X/20 - 1,Y/20)){
                    _map->destroyGItem(X/20 - 1,Y/20 + 1);
                }
            }
            else if(event->key() == Qt::Key_Down && !_map->hIsGround(X/20,Y/20 + 1)){
                setPos(x(),y() + 10);
                Y += 10;
                moveVCounter--;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                _map->hMoveDown();
                 moveVCounter = 0;
                 emit signalUpdate();
                }
           }
        }
    }
    else{
        if(event->key() == Qt::Key_Up){
            setPos(x(),y() - 20);
            moveVCounter++;

        }
        else if(event->key() == Qt::Key_Down){
            setPos(x(),y() + 20);
            moveVCounter--;

       }
        if(event->key() == Qt::Key_Left){
            setPos(x() - 10,y());
            moveHCounter--;

        }
        else if(event->key() == Qt::Key_Right){
            setPos(x() + 10,y());
            moveHCounter++;

        }

    }
}

void Hero::fall(){

    if(!_map->hIsGround(X/20,Y/20) && !_map->isStairs(X/20,Y/20) && !_map->isStairs(X/20,Y/20 + 1)){
        setPos(x(),y() + 10);
        Y = Y + 10;
        moveVCounter--;
        if(moveVCounter %2 == 0  && moveVCounter != 0){
        _map->hMoveDown();
         moveVCounter = 0;
        }
    }
}

void Hero::getGold(){
    if(!exit){
        if(goldCounter < _map->countOfGold){
            if(_map->getType(X/20,Y/20) == 5){
                //qDebug()<<"GOOOOOOLD";
                goldCounter++;
                _map->destroyGold(X/20,Y/20);
            }
        }
        else{
            emit goldDone();
            exit = true;
        }

    }
}

void Hero::isExit(){
    if(_map->getType(X/20,Y/20) == 10){
        emit levelComplited();
    }
}

