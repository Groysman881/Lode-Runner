#include "gold.h"
#include<QGraphicsRectItem>
#include <QGraphicsScene>

Gold::Gold()
{

}

Gold::Gold(int x,int y){
    setRect(x,y,20,20);
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
