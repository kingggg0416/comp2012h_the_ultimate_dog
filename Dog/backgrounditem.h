/*
create a class of background QGraphicsItem which is used in Mysecne.
*/

#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsPixmapItem>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    explicit BackgroundItem(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};

#endif // BACKGROUNDITEM_H
