
#ifndef HERO_H
#define HERO_H
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "map.h"



class Hero : public QObject, public QGraphicsPixmapItem{
        Q_OBJECT
public:
    Hero();
    Hero(int x,int y,int z);
    Hero(int x,int y,int z, Map* map);
    void keyPressEvent(QKeyEvent *event) override;
    size_t goldCounter;
public slots:
    void fall();
    void getGold();
    void isExit();
signals:
    void signalUpdate();
    void goldDone();
    void levelComplited();
private:
    bool exit;
    unsigned int health = 1;
    Map* _map;
    int moveHCounter;
    int moveVCounter;
    int X;
    int Y;
    int Z;
    bool isRightMove;
};


#endif // HERO_H
