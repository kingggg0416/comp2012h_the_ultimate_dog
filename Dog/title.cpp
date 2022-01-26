#include "title.h"

Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){
    viewer = view;
    viewer->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    scroll = new QScrollBar;
    scroll = viewer->horizontalScrollBar();

    //initialize a button to start the game
    startButton = new QPushButton(viewer);
    startButton->setStyleSheet("background-image: url(:/image/New Project (1).png)");
    startButton->setObjectName(QString("startButton"));
    startButton->setToolTip("Start Game");
    startButton->setGeometry(QRect(470, 470, 349, 144));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));

    //initialize background photo for the menu
    foreground = new QGraphicsPixmapItem;
    foreground->setPixmap(QPixmap(":/image/background.png"));
    addItem(foreground);
    //setting the scene of the menu
    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);

    quitButton = new QPushButton(viewer);
    quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(600, 670, 100, 32));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));

    //background music
    QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/music/sound/Music.mp3"));
    music->play();


}
void Title::startGame(){
    //slot for starting the game
    //creating graphicScene object from MyScene
    startButton->close();
    quitButton->close();
    scene = new MyScene(scroll,this);
    viewer->sceneSet(scene);


}

void Title::quitProgram(){

    qApp->quit();
}
