#ifndef PIPE_H
#define PIPE_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Pipe : public QGraphicsItem
{

public:
    enum { Type = UserType + pipeType };
    Pipe(int choice = 1, QGraphicsItem *parent = 0);
    void nextFrame2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    int choice;
    int mCurrentFrame2;
    QPixmap mPixmap2;

};


#endif // PIPE_H
