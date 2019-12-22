#include "stairs.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

Stairs::Stairs(int x,int y)
{
    setPos(x,y);
    setPixmap(QPixmap(":/new/images/stairs1.png"));
    X = x;
    Y = y;
}
