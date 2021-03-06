#ifndef ROCK_H
#define ROCK_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Rock : public QGraphicsItem
{

public:
    enum { Type = UserType + rocktype };
    Rock(QGraphicsItem *parent = 0);
    void nextFrame2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int mCurrentFrame2;
    QPixmap mPixmap2;

};

#endif // ROCK_H
