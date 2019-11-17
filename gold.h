#ifndef GOLD_H
#define GOLD_H
#include<QGraphicsRectItem>

class Gold : public QGraphicsRectItem
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
