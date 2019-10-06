#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QObject>

class Enemy : public QObject,public QGraphicsRectItem{
        Q_OBJECT
public:
    Enemy();
public slots:
    void find();
private:
    unsigned int health = 1;
};

#endif // ENEMY_H
