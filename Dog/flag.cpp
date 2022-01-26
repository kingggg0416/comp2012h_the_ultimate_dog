#include "flag.h"
#include <QPainter>

Flag::Flag(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame()

{
    setFlag(ItemClipsToShape);
    mPixmap8 = QPixmap(":image/flag.png");

}



QRectF Flag::boundingRect() const {
    return QRectF(0,0,178,254);

}

void Flag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap8, mCurrentFrame, 0,178, 254);
    setTransformOriginPoint(boundingRect().center());
}

int Flag::type() const
{
  return Type;
}
