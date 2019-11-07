#ifndef GROUND_H
#define GROUND_H
#include <QGraphicsItem>

class Ground : public QGraphicsRectItem
{
public:
    Ground(int x,int y);
    int getX(){return X;};
    int getY(){return Y;};
    void getDestroyed();
    void appear();
    void setCurrentScene(QGraphicsScene* _scene);
private:
    int X;
    int Y;
    QGraphicsScene* currentScene;
};

#endif // GROUND_H
