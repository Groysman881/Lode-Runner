#include "gold.h"
#include<QGraphicsRectItem>
#include <QGraphicsScene>

Gold::Gold()
{

}

Gold::Gold(int x,int y){
    setPos(x,y);
    setPixmap(QPixmap(":/new/images/gold1.png"));
    X = x;
    Y = y;
}

int Gold::getX(){
    return X;
}

int Gold::getY(){
    return Y;
}

void Gold::getDestroyed(){
    scene()->removeItem(this);
    delete(this);
}
