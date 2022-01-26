#include "coin.h"
#include <QPainter>
#include<QList>


Coin::Coin(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,m_current_frame_2(0)
{
    setFlag(ItemClipsToShape);
    m_pixmap_2 = QPixmap(":image/coin.png");

}

void Coin::nextFrame2(){

    m_current_frame_2 += 38;
    if (m_current_frame_2 >= 300 ) {
        m_current_frame_2 = 0;
    }
}

QRectF Coin::boundingRect() const {
    return QRectF(0,0,39,41);

}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, m_pixmap_2,m_current_frame_2, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}


int Coin::type() const
{
  return Type;
}
