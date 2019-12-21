#include "game.h"
#include <QVector>
#include <QDebug>
#include "map.h"

Game::Game(QGraphicsScene* _scene) : QObject(){
    gScene = _scene;
    _map = new Map();
}

Hero* Game::createLevel(){
    _hero = new Hero(_map->getHeroX() * 20,_map->getHeroY() * 20,_map);
    connect(_hero,SIGNAL(goldDone()),this,SLOT(addExit()));
    connect(_hero,SIGNAL(levelComplited()),this,SLOT(deleteLevel()));
    for(int i = 0; i < 40;i++){
        for(int j = 0;j < 30;j++){
            if(_map->getType(i,j) == 1){
               // _hero = new Hero(i * 20,j * 20,_map);
               // gScene->addItem(_hero);
            }
            else if(_map->getType(i,j) == 2){
                enemyVec.push_back(new Enemy(i * 20,j * 20, _map,_hero));

               // gScene->addItem(enemyVec.back());
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
            else if(_map->getType(i,j) == 10){
                exStairsVec.push_back(new Stairs(i * 20,j * 20));
                _map->hideExStairs(i,j);
            }
        }
    }
    gScene->addItem(_hero);
    for(int i = 0;i < enemyVec.size();i++){
        gScene->addItem(enemyVec[i]);
    }
    _map->setGVector(groundVec);
    _map->setGoldVector(goldVec);
    _hero->setFlag(QGraphicsItem::ItemIsFocusable);
    _hero->setFocus();
    gScene->setBackgroundBrush(Qt::black);
    return _hero;
}

void Game::addExit(){
    for(int i = 0;i < exStairsVec.size();i++){
        gScene->addItem(exStairsVec[i]);
        _map->addExStairs(exStairsVec[i]->getX()/20,exStairsVec[i]->getY()/20);
    }
}

void Game::deleteLevel(){
    qDebug()<<"DELETE";
}

