
#include "character.h"
#include "obstacledog.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

ObstacleDog::ObstacleDog(QRectF platformRect, int direction, QGraphicsItem *parent) : QGraphicsItem(parent), mCurrentFrame6(), mPlatform(platformRect), mDirection(direction)
{
    setFlag(ItemClipsToShape);
    mPixmap6 = QPixmap(":image/moving_dog.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void ObstacleDog::nextFrame() {

    mCurrentFrame6 += 80;
    if (mCurrentFrame6 >= 637 ) {
        mCurrentFrame6 = 0;
    }

    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());

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


QRectF ObstacleDog::boundingRect() const {

    return QRectF(0,0,71,45);
}

void ObstacleDog::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap6, mCurrentFrame6, 0,68,60);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}
/*
int ObstacleDog::type() const {

    return Type;
}
*/
