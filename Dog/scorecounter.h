#ifndef SCORECOUNTER_H
#define SCORECOUNTER_H

#include <QGraphicsTextItem>

class ScoreCounter: public QGraphicsTextItem{
public:
    ScoreCounter(QGraphicsItem * parent=0);
    void increase_diamondCount();
    void increase_score();
    int getCount();
    int getScore();
    int diamondCount;

private:

    int score;
};

#endif // SCORECOUNTER_H
