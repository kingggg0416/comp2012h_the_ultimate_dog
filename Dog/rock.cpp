#include "rock.h"
#include <QPainter>
#include<QList>

Rock::Rock(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame2()
{
    setFlag(ItemClipsToShape);
    mPixmap2 = QPixmap(":/image/rock2-graphic_reduced_2.png");
    //mPixmap = QPixmap("://image/walking_test.png");

}

void Rock::nextFrame2(){

    mCurrentFrame2 += 100;

    if (mCurrentFrame2 >= 1600 ) {
        mCurrentFrame2 = 0;
    }

}

QRectF Rock::boundingRect() const {
    return QRectF(0,0,106,100);

}

void Rock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap2, mCurrentFrame2, 0,106,100);
    //setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}


int Rock::type() const
{
  return Type;
}
