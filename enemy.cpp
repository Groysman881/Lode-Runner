#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>



Enemy::Enemy(int x,int y,int z) : QObject()
{
    setPos(x,y);
    setPixmap(QPixmap(":/images/enemy1.png"));
    QTimer *timer = new QTimer();
    X = x;
    Y = y;
    Z = z;
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));
    timer->start(50);
    moveHCounter = 0;
    moveVCounter = 0;
    fStack = nullptr;


}

Enemy::Enemy(int x,int y,int z,Map* eMap) : QObject(){
    setPos(x,y);
    setPixmap(QPixmap(":/new/images/enemy1.png"));
    X = x;
    Y = y;
    Z = z;
    _map = eMap;
    moveHCounter = 0;
    moveVCounter = 0;
    timer1 = new QTimer();
    fStack = nullptr;
    connect(timer1,SIGNAL(timeout()),this,SLOT(updatePath()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(fall()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(find()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(getDestroyed()));
    timer1->start(125);

}

Enemy::~Enemy(){
    disconnect(timer1,SIGNAL(timeout()),this,SLOT(updatePath()));
    disconnect(timer1,SIGNAL(timeout()),this,SLOT(fall()));
    disconnect(timer1,SIGNAL(timeout()),this,SLOT(find()));
    disconnect(timer1,SIGNAL(timeout()),this,SLOT(getDestroyed()));
    delete(timer1);
}
void Enemy::find(){
    if(X/20 == _map->getHeroX() && Y/20 == _map->getHeroY() && Z == _map->getHeroZ()){qDebug()<<"Death";}
    if(((!_map->isGround(X/20 - 1,Y/20 - 1,Z) && !_map->isGround(X/20 + 1,Y/20 - 1,Z))
        || _map->isStairs(X/20,Y/20,Z)) && fStack != nullptr && !fStack->isEmpty()){
    int temp;
    if( !fStack->isEmpty()){
        temp = fStack->pop();
        switch (temp) {
             case 1 :{
                setPos(x(),y() - 20);
                Y -= 20;
                moveVCounter++;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                    moveVCounter = 0;
                }
                break;
             }
             case 2 :{
                setPos(x(),y() +20);
                Y += 20;
                moveVCounter--;
                if(moveVCounter %2 == 0  && moveVCounter != 0){
                    moveVCounter = 0;
                }
                        break;
                    }
                    case 3 :{
                        setPos(x() - 20,y());
                        X -= 20;
                        moveHCounter--;
                        if(moveHCounter %2 == 0  && moveHCounter != 0){
                            moveHCounter = 0;
                        }
                        break;
                    }
                    case 4 :{
                        setPos(x() + 20,y());
                        X += 20;
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
    if(_map->isDestrGround(X/20,Y/20 - 1,Z)){
        return;
    }
    else if(_map->isDestrGround(X/20,Y/20,Z)){
        setPos(x(),y() + 20);
        Y += 20;
        _map->makeEnemyGround(X/20,Y/20,Z);
        QTimer *timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer, &QTimer::timeout, [=]() {
             if(_map->hIsGround(X/20,Y/20 - 1,Z)){
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
}

void Enemy::getDestroyed(){
    if(_map->isGround(X/20,Y/20 - 1,Z)){
        scene()->removeItem(this);
        this->~Enemy();
    }
}

void Enemy::updatePath(){
    if(((!_map->isGround(X/20 - 1,Y/20 - 1,Z) && !_map->isGround(X/20 + 1,Y/20 - 1,Z)) || _map->isStairs(X/20,Y/20,Z)) &&
            ((_map->isGround(_map->getHeroX(),_map->getHeroY(),Z)) || _map->isStairs(_map->getHeroX(),_map->getHeroY(),Z))) {
        fStack = _map->findPath(X/20,Y/20,Z);
   }
}


