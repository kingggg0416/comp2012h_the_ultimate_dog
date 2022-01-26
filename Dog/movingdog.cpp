/*
 * Author: equati0n
 * Date: December 2016
*/

#include "movingdog.h"
#include "character.h"

#include <QPainter>
#include <QDebug>

#include <iostream>
using namespace std;

Movingdog::Movingdog(QRectF platformRect, int direction, QGraphicsItem *parent) : QGraphicsItem(parent), mCurrentFrame6(), mPlatform(platformRect), mDirection(direction)
,on_player_right(true),on_player_left(false), right_check(true),left_check(false)
{
    setFlag(ItemClipsToShape);
    mPixmap6 = QPixmap(":image/moving_dog.png");
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(50);
}

void Movingdog::nextFrame() {
    mCurrentFrame6 += 80;
    if (mCurrentFrame6 >= 637 ) {
        mCurrentFrame6 = 0;
    }

    if(on_player_right == true) {
        if (right_check == false){
        if (right_check == false){
            right_check = true;
            left_check = false;
        }
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
        setPos(this->pos().x() + (mDirection*15), this->pos().y());
    }
    }
    if(on_player_left == true) {
        if (left_check == false){
        if (left_check == false){
            right_check = false;
            left_check = true;
        }
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
        setPos(this->pos().x() + (mDirection*15), this->pos().y());
    }
    }
    if (on_player_left == false && on_player_right == false){
        /*
        right_check = false;
        left_check = false;
        */
        setPos(this->pos().x(), this->pos().y());
    } else {
        setPos(this->pos().x() + (mDirection*15), this->pos().y());
    }



    //setPos(this->pos().x() + mDirection, this->pos().y());


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


QRectF Movingdog::boundingRect() const {

    return QRectF(0,0,71,45);
}

void Movingdog::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap6, mCurrentFrame6, 0,68,60);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}
/*
int Movingdog::type() const {

    return Type;
}
*/

void Movingdog::changespeed(int i){
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100*(1+i*0.2));
}

