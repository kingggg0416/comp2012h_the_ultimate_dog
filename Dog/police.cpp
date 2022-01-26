#include "police.h"
#include "character.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

Police::Police(QRectF platformRect, int direction, QGraphicsItem *parent) : QGraphicsItem(parent), m_current_frame_6(), m_platform(platformRect), m_direction(direction)
{
    setFlag(ItemClipsToShape);
    m_pixmap_6 = QPixmap(":image/police.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void Police::nextFrame() {


    m_current_frame_6 += 32;
    if (m_current_frame_6 >= 129) {
        m_current_frame_6 = 0;
    }

    if(this->pos().x() <  m_platform.x() || this->pos().x() >  m_platform.x()+  m_platform.width()) {
       m_direction = -m_direction;
        setTransform(QTransform(-m_direction, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (m_direction*10), this->pos().y());

    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If one of the colliding items is an Enemy, destroy both the bullet and the enemy

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Character)){

            emit dead();
            delete colliding_items[i];
            delete this;
            return;

        }
    }

}

QRectF Police::boundingRect() const {

    return QRectF(0,0,32,57);
}

void Police::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0,  m_pixmap_6,m_current_frame_6, 0,32,57);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

/*int Police::type() const {

    return Type;
}*/
