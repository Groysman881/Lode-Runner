#include "game.h"
#include <QVector>
#include <QDebug>
#include "map.h"

Game::Game(QGraphicsScene* _scene){
    gScene = _scene;
    _map = new Map();
}

Hero* Game::createLevel(){
    //gScene->setSceneRect(0,0,800,600);
    //int numInMatrix = 0;
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
                groundVec.back()->setCurrentScene(gScene);
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

    //gScene->setBackgroundBrush(Qt::black);

    return _hero;
}

void Game::createGraph(int size){
    _map->makeGraph(size);
}
