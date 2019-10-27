#pragma once
#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include "hero.h"
#include "enemy.h"
#include "ground.h"
#include "stairs.h"
#include "map.h"

class Game
{
public:
    Game(QGraphicsScene* _scene);
    QGraphicsScene* gScene;
    Hero* createLevel();
private:
    Map* _map;
    Hero* _hero;
    QVector<Enemy*> enemyVec;
    QVector<Ground*> groundVec;
    QVector<Stairs*> stairsVec;
};

#endif // GAME_H
