#ifndef COINCOUNTER_H
#define COINCOUNTER_H

#include <QGraphicsTextItem>



class Coincounter : public QGraphicsTextItem
{
    public:
        Coincounter(QGraphicsItem * parent = nullptr);
        void increase_counter();
        int get_counter();

    private:
        int coin_counter;

};

#endif // COINCOUNTER_H
