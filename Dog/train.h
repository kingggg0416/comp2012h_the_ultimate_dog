#ifndef TRAIN_H
#define TRAIN_H

#include <QGraphicsItem>
#include <QPixmap>
//#include "objecttype.h"
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <QGraphicsScene>



class Train : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //enum { Type = UserType + trainType };
    Train(int train_choice = 1, int speed = 15, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //int type() const;
    int get_speed();
public slots:
    void nextFrame();


private:
    int choice = 1;
    int x_dimension;
    int y_dimension;
    qreal x_pos;
    QTimer* timer;
    QPixmap m_pixmap;
    int speed;
    //enum {Type UserType + trainType};

signals:
    void hit();
    void no_hit();




};

#endif // TRAIN_H

