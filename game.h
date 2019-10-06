#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include "hero.h"
#include "enemy.h"

class Game
{
public:
    Game(QGraphicsScene* _scene);
    void createLevel();
    QGraphicsScene* gScene;
    qreal heroX();
    qreal heroY();
private:
    int*** gameMap;
    Hero* _hero;
    Enemy* _enemy;
};

#endif // GAME_H
