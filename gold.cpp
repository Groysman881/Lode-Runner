#include "gold.h"
#include<QGraphicsRectItem>
#include <QGraphicsScene>

Gold::Gold()
{

}

Gold::Gold(int x,int y){
    setPos(x,y);
    setPixmap(QPixmap(":/images/gold1.png"));
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
