#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>



Enemy::Enemy(int x,int y) : QObject()
{
    setPos(x,y);
    setPixmap(QPixmap(":/images/enemy1.png"));
    QTimer *timer = new QTimer();
    X = x;
    Y = y;
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));
    timer->start(50);
    moveHCounter = 0;
    moveVCounter = 0;
    fStack = nullptr;

}

Enemy::Enemy(int x,int y,Map* eMap,Hero* h) : QObject(){
    setPos(x,y);
    setPixmap(QPixmap(":/new/images/enemy1.png"));
    X = x;
    Y = y;
    _map = eMap;
    _hero = h;
    moveHCounter = 0;
    moveVCounter = 0;
    QTimer *timer1 = new QTimer();
    fStack = nullptr;
   // connect(_hero,SIGNAL(signalUpdate()),this,SLOT(updatePath()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(updatePath()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(fall()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(find()));
    //connect(_hero,SIGNAL(signalUpdate()),this,SLOT(find()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(getDestroyed()));
    timer1->start(100);
}

void Enemy::find(){
   /* if(_map->isGround(X/20,Y/20) || _map->isStairs(X/20,Y/20)){
    //qDebug()<<"SLOTFIND";
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
    else if(Y/20 > _map->getHeroY()){
        //qDebug()<<"Y !=";

           // qDebug()<<"STAIRSUP";
            qDebug()<<_map->findStairsUp(X/20,Y/20);
            if(X/20 < _map->findStairsUp(X/20,Y/20)){
             //   qDebug()<<"X<";
                setPos(x() + 10,y());
                X += 10;

            }
            else if(X/20 > _map->findStairsUp(X/20,Y/20)){
               // qDebug()<<"X>";
                qDebug()<<X/20;
                qDebug()<<Y/20;
                setPos(x() - 10,y());
                X -= 10;

            }
            else{
                //qDebug()<<"X==";
                setPos(x(),y() - 10);
                qDebug()<<"X++";
                Y -= 10;

            }
        }
        else if(Y/20 < _map->getHeroY()){
            if(X/20 < _map->findStairsDown(X/20,Y/20)){
                setPos(x() + 10,y());
                X += 10;

            }
            else if(X/20 > _map->findStairsDown(X/20,Y/20)){
                setPos(xR() - 10,y());
                X -= 10;

            }
            else{
                setPos(x(),y() + 10);
                Y += 10;


            }
        }
    }*/
    //qDebug()<<"FSTACK";
    //if(fStack != nullptr){
      //  qDebug()<<fStack->isEmpty();
    //}
    if(((!_map->isGround(X/20 - 1,Y/20 - 1) && !_map->isGround(X/20 + 1,Y/20 - 1))
        || _map->isStairs(X/20,Y/20)) && fStack != nullptr && !fStack->isEmpty()){
    //qDebug()<<"IT WORKS";
    int temp;
    //qDebug()<<_map->getHeroX();
    //qDebug()<<_map->getHeroY();
    if( !fStack->isEmpty()){
        temp = fStack->pop();
        switch (temp) {
             case 1 :{
                setPos(x(),y() - 10);
                qDebug()<<"UP";
                Y -= 10;
                moveVCounter++;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                    moveVCounter = 0;
                }
                break;
             }
             case 2 :{
                setPos(x(),y() + 10);
                qDebug()<<"DOWN";
                Y += 10;
                moveVCounter--;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                    moveVCounter = 0;
                }
                        break;
                    }
                    case 3 :{
                        setPos(x() - 10,y());
                        qDebug()<<"LEFT";
                        X -= 10;
                        moveHCounter--;
                        if(moveHCounter %2 == 0  && moveHCounter != 0){
                            moveHCounter = 0;
                        }
                        break;
                    }
                    case 4 :{
                        setPos(x() + 10,y());
                        qDebug()<<"RIGHT";
                        X += 10;                      
                        moveHCounter++;
                        if(moveHCounter %2 == 0  && moveHCounter != 0){
                        moveHCounter = 0;
                        }
                        break;
                     }
                }
        }
    }
}
void Enemy::fall(){
    if(_map->isDestrGround(X/20,Y/20 - 1)){
        return;
    }
    else if(_map->isDestrGround(X/20,Y/20)){
        //qDebug()<<"YEEES";
        setPos(x(),y() + 20);
        Y += 20;
        _map->makeEnemyGround(X/20,Y/20);
        QTimer *timer = new QTimer(this);
        timer->setSingleShot(true);
         connect(timer, &QTimer::timeout, [=]() {
             //qDebug()<<"XEXEXEXEXEXEXEXEXE";
             if(_map->hIsGround(X/20,Y/20 - 1)){
                 if(X/20 > _map->getHeroX()){
                    setPos(x() - 20,y() - 20);
                    X -= 20;
                    Y -= 20;
                 }
                 else{
                     setPos(x() + 20,y() - 20);
                     X += 20;
                     Y -= 20;
                 }

       timer->deleteLater();
     }
         });
     timer->start(3000);

        return;
    }
    else if(!_map->isGround(X/20,Y/20) && !_map->isStairs(X/20,Y/20)){
        //qDebug()<<"NOOOO";
        setPos(x(),y() + 10);
        Y += 10;

       // qDebug()<<X/20;
      //  qDebug()<<Y/20;
        //qDebug()<<_map->getHeroY();
    }
    //setPos(x() - 10,y());
}

void Enemy::getDestroyed(){
    if(_map->isGround(X/20,Y/20 - 1)){
       // qDebug()<<"DDESSTR";
        scene()->removeItem(this);
        delete(this);
    }
}

void Enemy::updatePath(){
    qDebug()<<"UPDATEPATH";
    qDebug()<<!_map->isGround(X/20 - 1,Y/20 - 1);
    qDebug()<< !_map->isGround(X/20 + 1,Y/20 - 1);
    qDebug()<<  !_map->isStairs(X/20,Y/20);
    if((!_map->isGround(X/20 - 1,Y/20 - 1) && !_map->isGround(X/20 + 1,Y/20 - 1)) || _map->isStairs(X/20,Y/20)){
        qDebug()<<"UpdatePath";
        fStack = _map->findPath(X/20,Y/20);
   }
}

