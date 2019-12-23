#include "game.h"
#include <QVector>
#include <QDebug>
#include "map.h"
#include <QtAlgorithms>
#include <QGraphicsView>

Game::Game(QGraphicsScene* _scene) : QObject(){
    gScene = _scene;
    _map = new Map();
    level = 0;
}

void Game::createLevel(){
    qDebug()<<"Create";
    _map->countOfGold = 0;
    if(level < 4) {

    for(int i = 0; i < 40;i++){
        qDebug()<<i;
        for(int j = 0;j < 30;j++){
            if(_map->getType(i,j,level) == 1){
                qDebug()<<"hero";
                _hero = new Hero(i * 20,j * 20,level,_map);
                connect(_hero,SIGNAL(goldDone()),this,SLOT(addExit()));
                connect(_hero,SIGNAL(levelComplited()),this,SLOT(deleteLevel()));
                _map->setHero(i,j,level);
            }
            else if(_map->getType(i,j,level) == 2){
                qDebug()<<"enemy";
                enemyVec.push_back(new Enemy(i * 20,j * 20,level, _map));
                connect(enemyVec.last(),SIGNAL(killHero()),this,SLOT(closeGame()));
            }
            else if(_map->getType(i,j,level) == 3){
                groundVec.push_back(new Ground(i * 20,j * 20));
                groundVec.back()->setCurrentScene(gScene);
                gScene->addItem(groundVec.back());
            }
            else if(_map->getType(i,j,level) == 4){
                stairsVec.push_back(new Stairs(i * 20,j * 20));
                gScene->addItem(stairsVec.back());
            }
            else if(_map->getType(i,j,level) == 5){
                goldVec.push_back(new Gold(i * 20,j * 20));
                gScene->addItem(goldVec.back());
                _map->countOfGold++;
            }
            else if(_map->getType(i,j,level) == 10){
                exStairsVec.push_back(new Stairs(i * 20,j * 20));
                _map->hideExStairs(i,j,level);
            }
        }
    }
    qDebug()<<"END";
    gScene->addItem(_hero);
    qDebug()<<"END1";
    for(int i =0;i < enemyVec.size();i++){
        gScene->addItem(enemyVec[i]);
    }
    qDebug()<<"END2";
    _map->setGVector(groundVec);
    _map->setGoldVector(goldVec);
    qDebug()<<"END3";
    _hero->setFlag(QGraphicsItem::ItemIsFocusable);
    _hero->setFocus();
   qDebug()<<"END4";
    gScene->setBackgroundBrush(Qt::black);
    return;
}
    else{
        gScene->views().front()->close();
    }
}

void Game::addExit(){
    for(int i = 0;i < exStairsVec.size();i++){
        gScene->addItem(exStairsVec[i]);
        _map->addExStairs(exStairsVec[i]->getX()/20,exStairsVec[i]->getY()/20,level);
    }
}

void Game::deleteLevel(){
    disconnect(_hero,SIGNAL(goldDone()),this,SLOT(addExit()));
    disconnect(_hero,SIGNAL(levelComplited()),this,SLOT(deleteLevel()));
    qDebug()<<"DISCONNECT";
    gScene->removeItem(_hero);
    delete _hero;
    qDebug()<<enemyVec.isEmpty();
    for(int i = 0;i < enemyVec.size();i++){
        if(enemyVec[i] != nullptr){
            gScene->removeItem(enemyVec[i]);
        }
    }
    qDebug()<<"Pre ground";
    for(int i =0;i < groundVec.size();i++){
        qDebug()<<i;
        if(groundVec[i] != nullptr){
           gScene->removeItem(groundVec[i]);
           qDebug()<<"Pre delete";
        }
    }
    qDebug()<<"pre stairs";
    for(int i =0;i < stairsVec.size();i++){
        if(stairsVec[i] != nullptr){
           gScene->removeItem(stairsVec[i]);
           //delete stairsVec[i];
        }
    }
    qDebug()<<"pre ex stairs";
    for(int i =0;i < exStairsVec.size();i++){
        if(exStairsVec[i] != nullptr){
           gScene->removeItem(exStairsVec[i]);
          // delete exStairsVec[i];
        }
    }
    qDebug()<<"Pre clear";
    enemyVec.clear();
    groundVec.clear();
    stairsVec.clear();
    goldVec.clear();
    exStairsVec.clear();
    level++;
    createLevel();
}

void Game::closeGame(){
    gScene->views().front()->close();
}
