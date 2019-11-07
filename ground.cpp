#include "ground.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

Ground::Ground(int x,int y)
{
    setRect(x,y,20,20);
    X = x;
    Y = y;
    currentScene = scene();
}

void Ground::getDestroyed(){
    scene()->removeItem(this);
}

void Ground::appear(){
    currentScene->addItem(this);
    qDebug()<<"ALERT!!!!";
}

void Ground::setCurrentScene(QGraphicsScene* _scene){
    currentScene = _scene;
}
