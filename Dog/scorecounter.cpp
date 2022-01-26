#include "scorecounter.h"
#include <QTimer>
#include <QFont>
#include <QMessageBox>
#include<QFontDatabase>

ScoreCounter::ScoreCounter(QGraphicsItem *parent): QGraphicsTextItem(parent), diamondCount(0),score(0){

    // draw the text
    int id = QFontDatabase::addApplicationFont(":font/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(score));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2",30));
}

void ScoreCounter::increase_diamondCount(){
    diamondCount++;
    //setPlainText(QString("") + QString::number(diamondCount));
}

void ScoreCounter::increase_score(){
    score++;
    setPlainText(QString("") + QString::number(score));
}

int ScoreCounter::getCount(){
    return diamondCount;
}

int ScoreCounter::getScore(){
    return score;
}

