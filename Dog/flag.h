/*
create a class of flagpole QGraphicsItem which is used in Mysecne.
player can reach this  QGraphicsItem to win the game
*/
#ifndef FLAG_H
#define FLAG_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Flag : public QGraphicsItem
{
public:
    enum { Type = UserType + flagType };
    Flag(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame;
    QPixmap mPixmap8;
};
#endif // FLAG_H
