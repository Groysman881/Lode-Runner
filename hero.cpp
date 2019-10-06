#include "hero.h"
#include <QKeyEvent>

Hero::Hero()
{
    setRect(0,0,20,20);
}

void Hero::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        setPos(x() - 10,y());
    }
    else if(event->key() == Qt::Key_Right){
        setPos(x() + 10,y());
    }
    else if(event->key() == Qt::Key_Up){
        setPos(x(),y() - 10);
    }
    else if(event->key() == Qt::Key_Down){
        setPos(x(),y() + 10);
    }
}
