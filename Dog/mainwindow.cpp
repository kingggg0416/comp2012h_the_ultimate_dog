#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <QPropertyAnimation>
MainWindow::MainWindow()
{
    createScene();
    setCentralWidget(view);
    setWindowTitle("THE ULTIMATE DOG ESCAPER");
}

//    ui->setupUi(this);
//    this->setFixedSize(1280,740);
//    MainWindow::setWindowTitle("THE ULTIMATE DOG ESCAPER");
//   this->setStyleSheet("background-image: url(:/image/background new .jpg)");


//MainWindow::~MainWindow()
//{
//    delete ui;
//}


//void MainWindow::on_pushButton_clicked()
//{

//}

void MainWindow::createScene(){
    view = new View;
    title = new Title(view);
}

void MainWindow::setSize(){
    this->setFixedSize(1280,740);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}
