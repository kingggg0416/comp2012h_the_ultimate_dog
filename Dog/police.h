#ifndef POLICE_H
#define POLICE_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <QGraphicsScene>

class Police : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
    //enum { Type = UserType + policeType };
    Police(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    //void nextFrame6();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //int type() const;

public slots:
    void nextFrame();

signals:
    void dead();

private:

    int m_current_frame_6;
    QPixmap m_pixmap_6;
    QRectF m_platform;
    int m_direction;
};
#endif // POLICE_H
