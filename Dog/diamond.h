/*
create a class of diamond QGraphicsItem which is used in Mysecne.
player can collect this  QGraphicsItem
*/

#ifndef DIAMOND_H
#define DIAMOND_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Diamond : public QGraphicsItem {

    public:
        enum { Type = UserType + diamondType };
        Diamond(QGraphicsItem *parent = nullptr);
        void nextFrame2();
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        int type() const;

    private:
    
        int m_current_frame_2;
        QPixmap m_pixmap_2;


};

#endif // COIN_H
