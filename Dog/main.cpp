#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/image/windown icon.png"));
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/image/name.jpg"));

//test

    splash->show();

    MainWindow w;
    w.setSize();

    QTimer::singleShot(100,splash,SLOT(close()));
    QTimer::singleShot(100,&w,SLOT(show()));
    return a.exec();

}
