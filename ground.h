#ifndef GROUND_H
#define GROUND_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Ground :public QObject, public QGraphicsPixmapItem {
        Q_OBJECT

public:
    Ground(int x,int y);
    int getX();
    int getY();
    void getDestroyed();
    void setCurrentScene(QGraphicsScene* _scene);
    void appear();
    bool isDestroyed;
private:
    int X;
    int Y;
    QGraphicsScene* currentScene;
};

#endif // GROUND_H
