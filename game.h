#pragma once
#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include "hero.h"
#include "enemy.h"
#include "ground.h"
#include "stairs.h"
#include "map.h"
#include "gold.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game(QGraphicsScene* _scene);
    QGraphicsScene* gScene;
    Hero* createLevel();
    Map* _map;
    void deleteLevel();

public slots:
    void addExit();

private:
    //Map* _map;
    Hero* _hero;
    QVector<Enemy*> enemyVec;
    QVector<Ground*> groundVec;
    QVector<Stairs*> stairsVec;
    QVector<Gold*> goldVec;
    QVector<Stairs*> exStairsVec;
};

#endif // GAME_H
