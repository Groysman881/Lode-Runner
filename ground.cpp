#include "ground.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QObject>

Ground::Ground(int x,int y) : QObject()
{
    setPos(x,y);
    setPixmap(QPixmap(":/new/images/ground1.png"));
   // setRect(x,y,20,20);
    X = x;
    Y = y;
    currentScene = scene();
    isDestroyed  = false;
}

void Ground::getDestroyed(){
    scene()->removeItem(this);
    isDestroyed = true;
}

void Ground::appear(){
    currentScene->addItem(this);
}

void Ground::setCurrentScene(QGraphicsScene* _scene){
    currentScene = _scene;
}

int Ground::getX(){
    return X;
}

int Ground::getY(){
    return Y;
}
