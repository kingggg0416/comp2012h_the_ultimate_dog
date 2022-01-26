#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>

class Timer: public QGraphicsTextItem{
public:
    Timer(QGraphicsItem * parent=0);
    void decrease();
    int getTime();
    void timerEvent(QTimerEvent *);
    int timeCount;
private:

    int x;
};
#endif // TIMER_H
