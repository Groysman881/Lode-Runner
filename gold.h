#ifndef GOLD_H
#define GOLD_H
#include<QGraphicsRectItem>
#include <QGraphicsPixmapItem>

class Gold : public QGraphicsPixmapItem
{
public:
    Gold();
    Gold(int x,int y);
    int getX();
    int getY();
    void getDestroyed();
private:
    int X;
    int Y;
};

#endif // GOLD_H
