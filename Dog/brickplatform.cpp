#include "brickplatform.h"
#include <QPainter>


BrickPlatform::BrickPlatform(int waterpipe_choice , QGraphicsItem *parent)
    : QGraphicsItem(parent),photo_choice(waterpipe_choice)
{
    switch(photo_choice) {
        case(1):
            mPixmap = QPixmap(":image/waterpipe-1.png");
            x_size = 261;
            y_size = 62;
            break;
        case(2):
            mPixmap = QPixmap(":image/waterpipe-2.png");
            x_size = 213;
            y_size = 68;            
            break;
        case(3):
            mPixmap = QPixmap(":image/waterpipe-3.png");
            x_size = 166;
            y_size = 65;            
            break;
        case(4):
            mPixmap = QPixmap(":image/waterpipe-4.png");
            x_size = 124;
            y_size = 58;            
            break;
        case(5):
            mPixmap = QPixmap(":image/waterpipe-5.png");
            x_size = 134;
            y_size = 122;            
            break;
        case(6):
            mPixmap = QPixmap(":image/waterpipe-6.png");
            x_size = 68;
            y_size = 212;            
            break;
            
    }
    setFlag(ItemClipsToShape);
}



QRectF BrickPlatform::boundingRect() const {
    return QRectF(0,0,x_size,y_size);
}

void BrickPlatform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap, 0, 0, -1, -1);
    //setTransformOriginPoint(boundingRect().center());
}

/*int BrickPlatform::type() const {
    return Type;
}*/

