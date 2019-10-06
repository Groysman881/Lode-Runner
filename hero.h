#ifndef HERO_H
#define HERO_H
#include <QGraphicsItem>


class Hero : public QGraphicsRectItem
{
public:
    Hero();
    void keyPressEvent(QKeyEvent *event) override;
private:
    unsigned int health = 1;
};

#endif // HERO_H
