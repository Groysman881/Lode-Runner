#include "stairs.h"
#include <QGraphicsPixmapItem>

Stairs::Stairs(int x,int y)
{
    setPos(x,y);
    setPixmap(QPixmap(":/new/images/stairs1.png"));
   // setRect(x,y,20,20);
    X = x;
    Y = y;
}
