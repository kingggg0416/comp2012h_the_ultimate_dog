#include "character.h"
#include <QPainter>
Character::Character(QGraphicsItem *parent) : QGraphicsItem(parent) ,m_direction(0),
mCurrentFrame(),m_StandingDirection(), mState(Standing){
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("://image/walking_test.png");

}

Character::~Character(){

}


QRectF Character::boundingRect() const{

    return QRectF(0,0,44,73);
}

//stock photo for walking is 44pixel per frame
void Character::nextFrame(){
    //mCurrentFrame refers to the photos frame position, this is used for printing animations
    //for walking
    mCurrentFrame += 44;
    //resets to 0 when it reaches 132 pix
    if (mCurrentFrame >= 132 ) {
        mCurrentFrame = 0;
    }
}

int Character::direction() const{

    return m_direction;
}

int Character::standingDirectdirectionion() const{

    return m_StandingDirection;
}



void Character::addDirection(int direction){

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (m_direction != 0){
        if (m_direction != 1)

            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else
            setTransform(QTransform());
    }
}


void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,44, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}



void Character::addStandingDirection(int standingDirection){
    m_StandingDirection = standingDirection;

    
}

void Character::stand(){

    //mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void Character::walk(){

    if(mState == Walking) {
        return;
    }

    //mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;

}

void Character::jump(){
    mState = Jumping;
}

void Character::fall(){
    mState = Falling;
}

bool Character::is_falling(){
    return mState == Falling;
}



bool Character::is_touching_foot(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool Character::is_touching_head(QGraphicsItem *item){

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool Character::is_touching_platform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height())-5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}


