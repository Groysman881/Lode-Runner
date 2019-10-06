#include <QGraphicsScene>
#include <QApplication>
#include <QGraphicsView>
#include "hero.h"
#include "enemy.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* my_scene = new QGraphicsScene();
    Game* myGame = new Game(my_scene);
    QGraphicsView* my_view = new QGraphicsView(myGame->gScene);
    my_view->show();
    return a.exec();
}
