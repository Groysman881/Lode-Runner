#include "game.h"
#include <QVector>
#include <QDebug>
#include "map.h"

Game::Game(QGraphicsScene* _scene){
    gScene = _scene;
    /*int gameMap[40][30];
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 30;j++){
            gameMap[i][j] = 0;
        }
    }
    gameMap[0][0] = 1;
    gameMap[10][2] = 2;
    for(int i = 0;i < 40;i++){
        gameMap[i][1] = 3;
    }*/
    _map = new Map();
}

Hero* Game::createLevel(){
    //gScene->setSceneRect(0,0,800,600);
    for(int i = 0; i < 40;i++){
        for(int j = 0;j < 30;j++){
            if(_map->getType(i,j) == 1){
                _hero = new Hero(i * 20,j * 20,_map);
                gScene->addItem(_hero);
                _map->setHero(i,j);
            }
            else if(_map->getType(i,j) == 2){
                enemyVec.push_back(new Enemy(i * 20,j * 20, _map));
                gScene->addItem(enemyVec.back());
            }
            else if(_map->getType(i,j) == 3){
                groundVec.push_back(new Ground(i * 20,j * 20));
                gScene->addItem(groundVec.back());
            }
            else if(_map->getType(i,j) == 4){
                stairsVec.push_back(new Stairs(i * 20,j * 20));
                gScene->addItem(stairsVec.back());
            }
            else if(_map->getType(i,j) == 5){
                goldVec.push_back(new Gold(i * 20,j * 20));
                gScene->addItem(goldVec.back());
            }
        }
    }
    _map->setGVector(groundVec);
    _map->setGoldVector(goldVec);
    _hero->setFlag(QGraphicsItem::ItemIsFocusable);
    _hero->setFocus();

    return _hero;
}
