#ifndef BRICKPLATFORM_H
#define BRICKPLATFORM_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"


class BrickPlatform : public QGraphicsItem
{
public:
    //enum { Type = UserType + brickPlatformType };
    BrickPlatform( int waterpipe_choice, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //int type() const;

private:
    int x_size;
    int y_size;

    int photo_choice;
    QPixmap mPixmap;
};
#endif // BRICKPLATFORM_H
