#include "game.h"

Game::Game(QGraphicsScene* _scene){
    gScene = _scene;
    _hero = new Hero;
    _enemy = new Enemy;
    gScene->addItem(_hero);
    gScene->addItem(_enemy);
    _hero->setFlag(QGraphicsItem::ItemIsFocusable);
    _hero->setFocus();
}

qreal Game::heroX(){
    return _hero->x();
}
qreal Game::heroY(){
    return _hero->y();
}
