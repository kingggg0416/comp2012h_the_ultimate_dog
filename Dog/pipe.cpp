#include "pipe.h"
#include <QPainter>
#include<QList>

Pipe::Pipe(int choice, QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame2(),
      choice(choice)
{
    setFlag(ItemClipsToShape);
    switch(choice){
        case(2):
            mPixmap2 = QPixmap(":/image/teleport_pipe_vertical.png");
            break;
        default:
            mPixmap2 = QPixmap(":/image/teleport_pipe.png");
            break;
    }

}

void Pipe::nextFrame2(){

    mCurrentFrame2 += 62;

    if (mCurrentFrame2 >= 992 ) {
        mCurrentFrame2 = 0;
    }

}

QRectF Pipe::boundingRect() const {
    if(choice == 1)
        return QRectF(0,0,261,62);
    else
        return QRectF(0,0,60,252);

}

void Pipe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(choice == 1)
        painter->drawPixmap(0,0, mPixmap2, mCurrentFrame2, 0,261,62);
    else
        painter->drawPixmap(0,0, mPixmap2, mCurrentFrame2, 0,60,252);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}


int Pipe::type() const
{
  return Type;
}
