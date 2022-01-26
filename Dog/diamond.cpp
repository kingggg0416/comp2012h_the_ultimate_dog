#include "diamond.h"
#include <QPainter>
#include<QList>


Diamond::Diamond(QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,m_current_frame_2(0)
{
    setFlag(ItemClipsToShape);
    m_pixmap_2 = QPixmap(":image/diamond.png");

}

void Diamond::nextFrame2(){

    m_current_frame_2 += 65;
    if (m_current_frame_2 >= 442 ) {
        m_current_frame_2 = 0;
    }
}

QRectF Diamond::boundingRect() const {
    return QRectF(0,0,42,42);

}

void Diamond::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, m_pixmap_2,m_current_frame_2, 0,42, 42);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}


int Diamond::type() const
{
  return Type;
}
