#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QPixmap>


class Character : public QGraphicsItem
{
public:
     Character(QGraphicsItem *parent = nullptr);
     ~Character();

     //directions
    int direction() const;
    int standingDirectdirectionion() const;
    void addStandingDirection(int standingDirection);
    void addDirection(int direction);

    //next Frame to store next action for updating pos
    void nextFrame();
    QRectF boundingRect() const;


    //showing the character
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //supporting function for collision detection
    //head foot touch item
    bool is_touching_foot(QGraphicsItem *item);
    bool is_touching_head(QGraphicsItem *item);
    bool is_touching_platform(QGraphicsItem *item);


    //actions
    void stand();
    void jump();
    void standShoot();
    void walk();
    void fall();
    bool is_falling();

private:
    enum State {
         Standing = 0,
         StandShoot,
         Walking,
         Jumping,
         Falling
    };

    int m_direction;
    int mCurrentFrame;
    int m_StandingDirection;
    State mState;
    QPixmap mPixmap;
    QPixmap mWalkPixmap;
    QPixmap mStandingPixmap;
    QPixmap mJumpPixmap;
    QPixmap standShootPixmap;

};


#endif // CHARACTER_H
