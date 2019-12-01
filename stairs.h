#ifndef STAIRS_H
#define STAIRS_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Stairs : public QGraphicsRectItem
{

public:
    Stairs(int x,int y);
    int getX(){return X;};
    int getY(){return Y;};
private:
    int X;
    int Y;
};

#endif // STAIRS_H
