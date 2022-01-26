#include "wallplatform.h"
#include <QPainter>

WallPlatform::WallPlatform( int length, QGraphicsItem *parent)
    :QGraphicsItem(parent), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/wallplatform.png");
}

/*void WallPlatform::nextFrame() {
    mCurrentFrame += 48;
    if (mCurrentFrame >= 768 ) {
        mCurrentFrame = 0;
    }
}*/

QRectF WallPlatform::boundingRect() const {
    return QRectF(0,0,mLength,48);
}

void WallPlatform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    //modification is made to make the size of the wallplatform customizable
    int remaining_length = mLength;
    int i = 0;
    while(! (remaining_length/48 == 0)){
        painter->drawPixmap(i*48,0, mPixmap,0, 0,48, 48);
        remaining_length /=48;
        i++;
    }
    painter->drawPixmap(i*48,0,mPixmap,0,0,remaining_length,48);
    setTransformOriginPoint(boundingRect().center());
}

/*
int WallPlatform::type() const {
    return Type;
}
*/
