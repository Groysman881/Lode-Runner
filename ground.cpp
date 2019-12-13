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
    X = x;
    Y = y;
    currentScene = scene();
}

Ground::~Ground(){
    delete currentScene;
}

void Ground::getDestroyed(){
    qDebug()<<"DESTROY";
    scene()->removeItem(this);
}

void Ground::appear(){
    currentScene->addItem(this);
    qDebug()<<"ALERT!!!!";
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
