#include "train.h"
#include "character.h"
#include <QtDebug>
#include <QPainter>
#include<QList>


Train::Train( int train_choice, int speed, QGraphicsItem *parent) :QGraphicsItem(parent)
{
    switch(train_choice){
        case(1):
            m_pixmap = QPixmap(":/image/train1.png");
            x_dimension = 821;
            y_dimension = 60;
            break;
        case(2):
            m_pixmap = QPixmap(":/image/train2.png");
            x_dimension = 584;
            y_dimension = 60;
            break;
    }
    choice = train_choice;
    this->speed = speed;
    x_pos = 8000;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(10);
}






void Train::nextFrame(){
    if(x_pos < -x_dimension){
        x_pos = 8000;
        m_pixmap = (choice == 1)? QPixmap(":/image/train2.png") : QPixmap(":/image/train1.png");
        if(choice == 1){
            x_dimension = 821;
            y_dimension = 60;
            choice = 2;
        }
        else{
            x_dimension = 584;
            y_dimension = 60;
            choice = 1;
        }
    }
    x_pos -= speed;
    setPos(x_pos,this->pos().y());

  //train collision dectection
  QList<QGraphicsItem *> colliding_items = collidingItems();

  //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
  //if train exits the screen then stop hit action


  for (int i = 0, n = colliding_items.size(); i < n; ++i){
      if (typeid(*(colliding_items[i])) == typeid(Character)){

          emit hit();

          return;
      }
  }
  emit no_hit(); //signal for no hit

}

QRectF Train::boundingRect() const {
    return QRectF(0,0,x_dimension,y_dimension);

}

void Train::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, m_pixmap,0, 0,x_dimension,y_dimension);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Train::get_speed(){
    return speed;
}


/*int Train::type() const
{
  return Type;
}*/


