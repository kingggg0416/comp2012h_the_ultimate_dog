#ifndef TITLE_H
#define TITLE_H

#include <QPushButton>

#include "mainwindow.h"
#include "myscene.h"


//#include "soundmanager.h"


class View;
class LoginWindow;
class MyScene;
class AnimatedGraphicsItem : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
};

class View;
class MyScene;
class Title: public QGraphicsScene{
    Q_OBJECT
public:
    Title(View *view, QWidget *parent = nullptr);
    //Connection createConnection();
signals:
    void quitGame();
private slots:
    //this replaces the developer login in the source
    void startGame();
    void quitProgram();

private:
    //only essential variables are declared
    View *viewer;
    AnimatedGraphicsItem *background;
    QGraphicsPixmapItem *foreground;
    QGraphicsPixmapItem *cursor;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
    QPushButton *startButton;
    QPushButton *quitButton;

    QPropertyAnimation *animation;
    QScrollBar *scroll;
    MyScene *scene;

};

#endif // TITLE_H
