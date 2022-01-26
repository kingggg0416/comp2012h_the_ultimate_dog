#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtGui>
#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>

#include <QMenuBar>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSlider>

#include <QSpacerItem>
#include <QSpinBox>
#include <QSplashScreen>
#include <QStatusBar>
#include <QStyle>
#include "myscene.h"
#include <QGraphicsItemAnimation>
#include "view.h"
#include "title.h"
//also include stuff from view.cpp, title.cpp

class Title;
class View;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    void setSize();
    //~MainWindow();

private slots:
    //void on_pushButton_clicked();

private:
//    Ui::MainWindow *ui;
//    MyScene * myscene;
    void createScene();
    Title *title;
    View *view;
    //QRect screenGeometry = QApplication::desktop()->screenGeometry();(QT 5/6 remove :desktop()->screenGeometry())
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();

    QAction *quitAction;
    QAction *fullScreenAction;
};
#endif // MAINWINDOW_H
