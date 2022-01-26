#ifndef MOVINGDOG_H
#define MOVINGDOG_H




#include <QGraphicsItem>
#include <QPixmap>
//#include "objecttype.h"
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <QGraphicsScene>

class Movingdog : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
    //enum { Type = UserType + turtleType };
    Movingdog(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    //void nextFrame6();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //int type() const;
    bool on_player_right;
    bool on_player_left;
    bool left_check;
    bool right_check;
    bool same_check;
    void changespeed(int);

public slots:
    void nextFrame();

signals:
    void dead();

private:
    QTimer* timer;
    int mCurrentFrame6;
    QPixmap mPixmap6;
    QRectF mPlatform;
    int mDirection;
};


#endif // MOVINGDOG_H
