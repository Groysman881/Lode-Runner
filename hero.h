
#ifndef HERO_H
#define HERO_H
#include <QGraphicsItem>
#include <QObject>
#include "map.h"

class Hero : public QGraphicsRectItem{
    Q_OBJECT_NO_OVERRIDE_WARNING

public:
    Hero();

    Hero(int x,int y);
    Hero(int x,int y, Map* map);
    void keyPressEvent(QKeyEvent *event) override;
    void fall();
private:
    unsigned int health = 1;
   // Hero* _game;
    Map* _map;
    int moveHCounter;
    int moveVCounter;
    int X;
    int Y;
    bool isRightMove;
    size_t goldCounter;
    //QList <QGraphicsItem* > items;
};

#endif // HERO_H
