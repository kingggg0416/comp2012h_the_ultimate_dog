#ifndef VIEW_H
#define VIEW_H

#include "mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QPushButton>

//view is the class to init viewer object for use in title.cpp
class View : public QGraphicsView{
    Q_OBJECT
signals:
    void sceneChanged();

public:
    View();
    void sceneSet(QGraphicsScene *);
   
};

#endif // VIEW_H
