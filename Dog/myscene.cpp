#include "myscene.h"
#include "character.h"
#include "timer.h"
#include "rock.h"
#include "flag.h"
#include "scorecounter.h"
#include "diamond.h"
#include <QScrollBar>
#include <QTimer>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QThread>
#include <iostream>
using namespace std;





MyScene::MyScene(QScrollBar*s , QObject *parent) : QGraphicsScene(0,0,8000,720, parent),
    player(),
    player_velocity(3),
    m_jumpAnimation(new QPropertyAnimation(this)),
    m_jumpHeight(200),
    scroll(s),
    rock(0),
    pipe_1(0),
    plus_five_presence(false),
    hit_diamond(false),
    train_hit(false)
{


    initPlayField();


    p_timer.setInterval(5);
    connect(&p_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &MyScene::fallPlayer);

    t_timer.setInterval(10);
    connect(&t_timer, &QTimer::timeout, this, &MyScene::train_push);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &MyScene::jumpFactorChanged, this, &MyScene::jumpPlayer);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &MyScene::jumpStatusChanged);

    //set timer position
    m_gameTimer = new Timer();
    m_gameTimer->setPos(1175, m_groundLevel - m_gameTimer->boundingRect().height()-600);
    //m_gameTimer->setPos(500,500);
    addItem(m_gameTimer);


    clock = new BackgroundItem(QPixmap(":image/clock_2.png"));
    clock->setPos(m_gameTimer->pos().x()-90, m_gameTimer->pos().y()-20);
    addItem(clock);

    //set score counter position
    m_score = new ScoreCounter();
    m_score->setPos(950, m_groundLevel - m_gameTimer->boundingRect().height()-600);
    addItem(m_score);

    m_diamondcounter = new BackgroundItem(QPixmap(":image/score_2.png"));
    m_diamondcounter->setPos(765, m_score->pos().y());
    addItem(m_diamondcounter);


    plus_five = new BackgroundItem(QPixmap(":image/+5_4.png"));
    plus_five->setPos(m_score->pos().x()-20, m_groundLevel - plus_five->boundingRect().height()-570);
    addItem(plus_five);
    plus_five->setVisible(0);

    plus_one = new BackgroundItem(QPixmap(":image/+1_2.png"));
    plus_one->setPos(m_score->pos().x(), m_groundLevel - plus_one->boundingRect().height()-550);
    addItem(plus_one);
    plus_one->setVisible(0);

    jumping = false;
    falling = false;

}


void MyScene::initPlayField() {

    //set the mainscreen size
    setSceneRect(0,0,8000,720);

    //set the ground level
    m_groundLevel = 660;

    //set background photo
    m_sky = new BackgroundItem(QPixmap(":/image/game background.jpg"));

    m_sky->setPos(0,0);
    addItem(m_sky);

    //this is the floor of the game
    m_ground = new BackgroundItem(QPixmap(":image/rock.jpg"));
    addItem(m_ground);
    m_ground->setPos(0, m_groundLevel);

    m_direction_sign = new BackgroundItem(QPixmap(":image/direction-sign.png"));
    addItem(m_direction_sign);
    m_direction_sign->setPos(20, m_groundLevel-69);
    
    player = new Character();
    player->setPos(50, m_groundLevel - player->boundingRect().height() );
    addItem(player);

    /*rock = new Rock();
    rock->setPos(1500, m_groundLevel - rock->boundingRect().height()+12);
    //rock->setPos(600,600);
    addItem(rock);*/


    //Add platforms

    pipe_1 = new Pipe();
    pipe_1->setPos(160,m_groundLevel- pipe_1->boundingRect().height()-160);
    addItem(pipe_1);

    pipe_2 = new Pipe();
    pipe_2->setPos(2000, m_groundLevel - pipe_2->boundingRect().height() - 400);
    addItem(pipe_2);

    pipe_3 = new Pipe();
    pipe_3->setPos(3550, m_groundLevel - 300);
    addItem(pipe_3);

    pipe_4 = new Pipe();
    pipe_4->setPos(4300, m_groundLevel - 150);
    addItem(pipe_4); 

    pipe_5 = new Pipe();
    pipe_5->setPos(4460, m_groundLevel - 400);
    addItem(pipe_5); 



    //Just type the number corresponding to the waterpipe you want to use as the argument (Currently has : 1,2,3,4,5)
    m_pipe_1 = new BrickPlatform(1);
    m_pipe_1->setPos(550, m_groundLevel - m_pipe_1->boundingRect().height() - 110);
    addItem(m_pipe_1);


    m_pipe_2 = new BrickPlatform(1);
    m_pipe_2->setPos(915, m_groundLevel - m_pipe_2->boundingRect().height() - 180);
    addItem(m_pipe_2);

    m_pipe_3 = new BrickPlatform(1);
    m_pipe_3->setPos(1150, m_groundLevel - m_pipe_3->boundingRect().height() - 180);
    addItem(m_pipe_3);


    m_pipe_4 = new BrickPlatform(1);
    m_pipe_4->setPos(1550, m_groundLevel - m_pipe_4->boundingRect().height()-280);
    addItem(m_pipe_4);

    m_pipe_5 = new BrickPlatform(6);
    m_pipe_5->setPos(2350, m_groundLevel - m_pipe_5->boundingRect().height()-400);
    addItem(m_pipe_5);

    m_pipe_6 = new BrickPlatform(1);
    m_pipe_6->setPos(2350, m_groundLevel - 150);
    addItem(m_pipe_6);

    m_pipe_7 = new BrickPlatform(2);
    m_pipe_7->setPos(2830, m_groundLevel - 300);
    addItem(m_pipe_7);

    m_pipe_8 = new BrickPlatform(4);
    m_pipe_8->setPos(3100, m_groundLevel - 450);
    addItem(m_pipe_8);

    //m_pipe_9 will be the platform with the obstacle dog
    m_pipe_9 = new BrickPlatform(2);
    m_pipe_9->setPos(3250, m_groundLevel - 150);
    addItem(m_pipe_9);

    m_pipe_10 = new BrickPlatform(6);
    m_pipe_10->setPos(3390, m_groundLevel - 550);
    addItem(m_pipe_10);

    m_pipe_11 = new BrickPlatform(4);
    m_pipe_11->setPos(3880, m_groundLevel - 150);
    addItem(m_pipe_11);

    m_pipe_12 = new BrickPlatform(6);
    m_pipe_12->setPos(4150, m_groundLevel - 300);
    addItem(m_pipe_12);

    m_pipe_13 = new BrickPlatform(6);
    m_pipe_13->setPos(4650, m_groundLevel - 320);
    addItem(m_pipe_13);

    m_pipe_14 = new BrickPlatform(6);
    m_pipe_14->setPos(4650, m_groundLevel - 620);
    addItem(m_pipe_14);



    //Add diamonds
    m_diamonds = new Diamond();
    m_diamonds->setPos(600, m_groundLevel - m_pipe_1->boundingRect().height() - 140);
    addItem(m_diamonds);
    startTimer(100);

    m_diamonds2 = new Diamond();
    m_diamonds2->setPos(730, m_groundLevel - m_pipe_1->boundingRect().height() - 140);
    addItem(m_diamonds2);

    m_diamonds3 = new Diamond();
    m_diamonds3->setPos(1650,m_groundLevel - m_pipe_4->boundingRect().height()-280 -m_diamonds3->boundingRect().height());
    addItem(m_diamonds3);

    m_diamonds4 = new Diamond();
    m_diamonds4->setPos(2000, m_groundLevel - m_diamonds4->boundingRect().height()-460);
    addItem(m_diamonds4);

    m_diamonds5 = new Diamond();
    m_diamonds5->setPos(2100, m_groundLevel - m_diamonds5->boundingRect().height()-460);
    addItem(m_diamonds5);

    m_diamonds6 = new Diamond();
    m_diamonds6->setPos(2200, m_groundLevel - m_diamonds6->boundingRect().height()-460);
    addItem(m_diamonds6);

    m_diamonds7 = new Diamond();
    m_diamonds7->setPos(2360, m_groundLevel - m_pipe_5->boundingRect().height()-400 - m_diamonds7->boundingRect().height());
    addItem(m_diamonds7);

    m_diamonds8 = new Diamond();
    m_diamonds8->setPos(3140,  m_groundLevel - 450 - m_diamonds8->boundingRect().height());
    addItem(m_diamonds8);

    m_diamonds9 = new Diamond();
    m_diamonds9->setPos(3400, m_groundLevel - 550 - m_diamonds9->boundingRect().height());
    addItem(m_diamonds9);


    m_diamonds10 = new Diamond();
    m_diamonds10->setPos(5350, m_groundLevel - m_diamonds10->boundingRect().height());
    addItem(m_diamonds10);

    m_diamonds11 = new Diamond();
    m_diamonds11->setPos(5000, m_groundLevel - m_diamonds11->boundingRect().height());
    addItem(m_diamonds11);

    m_diamonds12 = new Diamond();
    m_diamonds12->setPos(5100, m_groundLevel - m_diamonds12->boundingRect().height());
    addItem(m_diamonds12);

    m_diamonds13 = new Diamond();
    m_diamonds13->setPos(5170, m_groundLevel - m_diamonds13->boundingRect().height());
    addItem(m_diamonds13);

    m_diamonds14 = new Diamond();
    m_diamonds14->setPos(5270, m_groundLevel - m_diamonds14->boundingRect().height());
    addItem(m_diamonds14);





    //Add coins
    m_coins = new Coin();
    m_coins->setPos(920, m_groundLevel - m_pipe_2->boundingRect().height()-205);
    addItem(m_coins);
    startTimer(100);

    m_coins2 = new Coin();
    m_coins2->setPos(970, m_groundLevel - m_pipe_2->boundingRect().height()-205);
    addItem(m_coins2);

    m_coins3 = new Coin();
    m_coins3->setPos(1030, m_groundLevel - m_pipe_2->boundingRect().height()-205);
    addItem(m_coins3);

    m_coins4 = new Coin();
    m_coins4->setPos(1080, m_groundLevel - m_pipe_2->boundingRect().height()-205);
    addItem(m_coins4);


    m_coins5 = new Coin();
    m_coins5->setPos(1130, m_groundLevel - m_pipe_2->boundingRect().height()-205);
    addItem(m_coins5);

    m_coins6 = new Coin();
    m_coins6->setPos(1180, m_groundLevel - m_pipe_2->boundingRect().height()-205);
    addItem(m_coins6);

    m_coins7 = new Coin();
    m_coins7->setPos(1230, m_groundLevel - m_pipe_2->boundingRect().height()-205);
    addItem(m_coins7);  

    m_coins8 = new Coin();
    m_coins8->setPos(4410, m_groundLevel - pipe_4->boundingRect().height()-135);
    addItem(m_coins8);  

    m_coins9 = new Coin();
    m_coins9->setPos(4430, m_groundLevel - pipe_4->boundingRect().height()-135);
    addItem(m_coins9);    

    m_coins10 = new Coin();
    m_coins10->setPos(4450, m_groundLevel - pipe_4->boundingRect().height()-135);
    addItem(m_coins10);    

    m_coins11 = new Coin();
    m_coins11->setPos(4470, m_groundLevel - pipe_4->boundingRect().height()-135);
    addItem(m_coins11);    

    m_coins12 = new Coin();
    m_coins12->setPos(4490, m_groundLevel - pipe_4->boundingRect().height()-135);
    addItem(m_coins12);        



    //wallplatform for m_police
    m_wallPlatform1 = new WallPlatform(1000);
    m_wallPlatform1->setPos(500, m_groundLevel);
    addItem(m_wallPlatform1);

    //wallplatform for m_police2
    m_wallPlatform2 = new WallPlatform(460);
    m_wallPlatform2->setPos(895,  m_pipe_2->boundingRect().height() - 180);
    addItem(m_wallPlatform2);

    //wallplatform fot m_police3
    m_wallPlatform6 = new WallPlatform(220);
    m_wallPlatform6->setPos(4300,  pipe_4->boundingRect().height() - 180);
    addItem(m_wallPlatform6);    

    //wall platform that restricts x pos movement of dogs
    m_wallPlatform3 = new WallPlatform(250);
    m_wallPlatform3->setPos(950, m_groundLevel);
    addItem(m_wallPlatform3);

    //wall platform for obstacle dogs
    m_wallPlatform4 = new WallPlatform(100);
    m_wallPlatform4->setPos(3250,m_groundLevel - 120 - m_pipe_9->boundingRect().height());
    addItem(m_wallPlatform4);

    m_wallPlatform5 = new WallPlatform(150);
    m_wallPlatform5->setPos(1550,m_groundLevel - 310 - m_pipe_4->boundingRect().height());
    addItem(m_wallPlatform5);    

    //Add police

    m_police = new Police(QRectF(m_wallPlatform1->pos(), m_wallPlatform1->boundingRect().size()), -1);
    m_police->setPos(500, m_groundLevel - m_police->boundingRect().height());
    addItem(m_police);
    connect(this->m_police, SIGNAL(dead()),this, SLOT(end_game()));

    m_police2 = new Police(QRectF(m_wallPlatform2->pos(), m_wallPlatform2->boundingRect().size()), -1);
    m_police2->setPos(895, m_groundLevel - m_police2->boundingRect().height()-220);
    addItem(m_police2);
    connect(this->m_police2, SIGNAL(dead()),this, SLOT(end_game()));

    m_police3 = new Police(QRectF(m_wallPlatform6->pos(), m_wallPlatform6->boundingRect().size()), -1);
    m_police3->setPos(4300, m_groundLevel - m_police3->boundingRect().height());
    addItem(m_police3);
    connect(this->m_police3, SIGNAL(dead()),this, SLOT(end_game()));


    m_movingdog = new Movingdog(QRectF(m_wallPlatform3->pos(), m_wallPlatform3->boundingRect().size()),-1);
    m_movingdog->setPos(995, m_groundLevel - m_movingdog->boundingRect().height());
    addItem(m_movingdog);
    connect(this->m_movingdog, SIGNAL(dead()),this, SLOT(end_game()));

    //Add trains
    m_train_1 = new Train(1);
    m_train_1->setPos(8000,m_groundLevel - m_train_1->boundingRect().height());
    addItem(m_train_1);
    

    //train hit connection
    connect(this->m_train_1, SIGNAL(hit()),this, SLOT(handle_hit_train()));
    connect(this->m_train_1, SIGNAL(no_hit()),this, SLOT(handle_nohit_train()));

    //Add obstacle dog => which is different from moving dog
    m_dog = new ObstacleDog(QRectF(m_wallPlatform4->pos(),m_wallPlatform4->boundingRect().size()),-1);
    m_dog->setPos(3250,m_groundLevel - 130 - m_pipe_9->boundingRect().height());
    addItem(m_dog);
    connect(this->m_dog, SIGNAL(dead()), this, SLOT(end_game()));

    m_dog2 = new ObstacleDog(QRectF(m_wallPlatform5->pos(),m_wallPlatform5->boundingRect().size()),-1);
    m_dog2->setPos(1550,m_groundLevel - 310 -  m_pipe_4->boundingRect().height());
    addItem(m_dog2);
    connect(this->m_dog2, SIGNAL(dead()), this, SLOT(end_game()));    
    //Add flag Pole

    m_flag = new Flag();
    m_flag->setPos(6000, m_groundLevel-254);
    addItem(m_flag);

//addItem(plus_five);


    //Add diamond counter
    /*m_diamondcounter = new BackgroundItem(QPixmap(":image/diamond_signs.png"));
    m_diamondcounter->setPos(900, m_groundLevel - m_diamondcounter->boundingRect().height()-610);
    addItem(m_diamondcounter);*/


    /*plus_five = new BackgroundItem(QPixmap(":image/+5_4.png"));
    plus_five->setPos(m_diamondcounter->pos().x(), m_groundLevel - plus_five->boundingRect().height()-570);
    addItem(plus_five);*/


}

void MyScene::timerEvent(QTimerEvent *){

    if (m_gameTimer->getTime()==0){
        end_game();
    }
    //enable the animtion effect of the coins    
    m_coins->nextFrame2();
    m_coins2->nextFrame2();
    m_coins3->nextFrame2();
    m_coins4->nextFrame2();
    m_coins5->nextFrame2();
    m_coins6->nextFrame2();
    m_coins7->nextFrame2();
    m_coins8->nextFrame2();
    m_coins9->nextFrame2();
    m_coins10->nextFrame2();
    m_coins11->nextFrame2();
    m_coins12->nextFrame2();

    //enable the animtion effect of the diamonds
    m_diamonds->nextFrame2();
    m_diamonds2->nextFrame2();
    m_diamonds3->nextFrame2();
    m_diamonds4->nextFrame2();
    m_diamonds5->nextFrame2();
    m_diamonds6->nextFrame2();
    m_diamonds7->nextFrame2();
    m_diamonds8->nextFrame2();
    m_diamonds9->nextFrame2();
    m_diamonds10->nextFrame2();
    m_diamonds11->nextFrame2();
    m_diamonds12->nextFrame2();
    m_diamonds13->nextFrame2();
    m_diamonds14->nextFrame2();

    if (plus_one_presence == true){
        if (plus_one_time < 10){
            plus_one_time++;
        } else {
            if (hit_coin == true){
            //removeItem(plus_one);
            plus_one->setVisible(0);
            plus_one_presence = false;
            plus_one_time = 0;
            }
        }
    }

    if (plus_five_presence == true){
        if (plus_one_presence == true){
            //removeItem(plus_one);
            plus_one->setVisible(0);
        }
        if (plus_five_time < 10){
            plus_five_time++;
        } else {
            if (hit_diamond == true){
            //removeItem(plus_five);
                plus_five->setVisible(0);
            plus_five_presence = false;
            plus_five_time = 0;
            }
        }
    }

    if ((player->pos().x() < m_movingdog->pos().x()+30)&&(player->pos().x() > m_movingdog->pos().x()-30)){
            m_movingdog->on_player_right = false;
            m_movingdog->on_player_left = false;

        } else
    if (player->pos().x()>m_movingdog->pos().x()){
            m_movingdog->on_player_left = true;
            m_movingdog->on_player_right = false;

        //m_movingdog->left_check = true;
    } else if (player->pos().x() < m_movingdog->pos().x()){
            m_movingdog->on_player_left = false;
            m_movingdog->on_player_right = true;

        //m_movingdog->right_check = true;
    }
}

//this is when needed to change character
void MyScene::setCharacterModel(int number){
    //creates the character and sets the p_timer
    switch (number){
        case 0:
            player = new Character();
            p_timer.setInterval(5);
            player->setPos(player->pos().x() , player->pos().y()+60);
            player->addDirection(player->direction()); //set the correct image direction
            addItem(player);

    //add cases for other character model

    }

}

void MyScene::end_game(){
    t_timer.stop();
    player->hide();
    player_velocity = 0;
    QMediaPlayer *dead = new QMediaPlayer();
    dead->setMedia(QUrl("qrc:/new/music/sound/death.wav"));
    dead->play();
    gameOverWindow = new GameOverWindow();
    gameOverWindow->setFixedSize(816,624);
    gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));

    gameOverWindow->exec();


}


void MyScene::movePlayer(){



    moving = true;

    //disable moving collision when hit by train

    if (train_hit != true){
    checkCollidingRock();  
    checkCollidingPipe();
    checkCollidingFlag();    
    }

    checkCollidingCoin();
    checkCollidingDiamond();
    if (player->is_falling()){
        return;
    }

    player -> nextFrame();

    int direction = player->direction();

    if (direction == 0){
        return;
    }



    //if a player stand above sth and move left or right, it falls back to the ground

    if(!(m_platform && player->is_touching_platform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
        if(m_platform){
            player->fall();
            mFallTimer.start();
        }
    }

    const int dx = direction * player_velocity;

//scroll bar + background
    //right scroll bar
    if(direction >0){
        if(player->pos().x() > 6720){
            return;
        }
        player->moveBy(dx, 0);
        int checkscrollright = player->pos().x() - scroll->value();
         if(checkscrollright > 900){
             if(scroll->value() == 6720){
                 return;
             }
             scroll->setValue(dx + scroll->value());
             m_sky->setPos(dx + m_sky->pos().x(),0);
             plus_five->setPos(dx + plus_five->pos().x(), plus_five->pos().y());
             m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
             m_score->setPos(dx + m_score->pos().x(), m_score->y());
             m_diamondcounter->setPos(dx + m_diamondcounter->pos().x(), m_diamondcounter->y());
             plus_one->setPos(dx + plus_one->pos().x(), plus_one->y());
             clock->setPos(dx + clock->pos().x(), clock->y());
            }

    }


    // left scroll bar
    if(direction < 0){
            if(player->pos().x() < 0){
                return;
            }
            player->moveBy(dx, 0);
            if(player->pos().x() > 0){
                int checkscrolleft = player->pos().x() - scroll->value();
                if(checkscrolleft < 200){
                    if(scroll->value() == 0){
                        return;
                    }
                    scroll->setValue(dx + scroll->value());
                    m_sky->setPos(dx+scroll->value(),0);
                    m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                    m_score->setPos(dx + m_score->pos().x(), m_score->y());
                    m_diamondcounter->setPos(dx + m_diamondcounter->pos().x(), m_diamondcounter->y());
                    plus_five->setPos(dx + plus_five->pos().x(), plus_five->pos().y());
                    plus_one->setPos(dx + plus_one->pos().x(), plus_one->y());
                    clock->setPos(dx + clock->pos().x(), clock->y());
           }
       }

    }
}


void MyScene::checkTimer(){

    if (0 == player->direction()){
                player->stand();
                p_timer.stop();
            }
     else if (!p_timer.isActive()){
                p_timer.start();
                player->walk();
            }


}


void MyScene::keyPressEvent(QKeyEvent *event){

    if (event->isAutoRepeat())
        return;

    switch (event->key()){
    case Qt::Key_Right:

        player->addDirection(1);
        player->addStandingDirection(1);
        checkTimer();
        break;

    case Qt::Key_Left:

        player->addDirection(-1);
        player->addStandingDirection(1);
        checkTimer();
        break;

    case Qt::Key_Space:
        if (mFallTimer.isActive()){
            return;
        } else {
        if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
           m_jumpAnimation->start();

           QMediaPlayer *music = new QMediaPlayer();
           music->setMedia(QUrl("qrc:/new/music/sound/jump.wav"));
           music->play();

        }}
        //player->setPos(player->pos().x(), y);

//addlater
        break;
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()){
    case Qt::Key_Right:

        player->addDirection(-1);
        player->addStandingDirection(1);
        checkTimer();
        break;
    case Qt::Key_Left:
        player->addDirection(1);
        player->addStandingDirection(-1);
        checkTimer();
        break;
case Qt::Key_Down:
        break;

     default:
        break;
    }
}

void MyScene::fallPlayer(){
    checkCollidingDiamond();

    player->setPos(player->pos().x(), player->pos().y() +30);
    QGraphicsItem* item = collidingPlatforms();
    if(item && handleCollisionWithPlatform()){
        mFallTimer.stop();
        player->walk();
    }
    else if(player->pos().y() + player->boundingRect().height() >= m_groundLevel){
        player->setPos(player->pos().x(), m_groundLevel - player->boundingRect().height());
        mFallTimer.stop();
        player->walk();
        m_platform = 0;
    }
}

void MyScene::jumpPlayer(){
    checkCollidingRock();
    checkCollidingDiamond();
    checkCollidingPipe();
    checkCollidingCoin();

    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
        player->stand();
        return;
    }

    QGraphicsItem* item = collidingPlatforms();
    if(item){
        if(player->is_touching_head(item)){

            m_jumpAnimation->stop();

            if(m_platform){
                //if there is a platform to stand on
                player->fall();
                mFallTimer.start();
                //player->setPos(player->pos().x(), m_platform->pos().y() - player->boundingRect().height());
                return;
            }
            if(!m_platform){
                //player->setPos(player->pos().x(), m_groundLevel - player->boundingRect().height());
                //instead of reaching the floor immediately, started fall timer for animation
                player->fall();
                mFallTimer.start();
                return;
            }
        }
        else{
            if (handleCollisionWithPlatform()){
            return;
            }
        }
    }
    if (mFallTimer.isActive()){
        return;
    }

    qreal y = (m_groundLevel - player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    if(m_platform){
        y = (m_platform->pos().y() - player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
        if(!(m_platform && player->is_touching_platform(m_platform)) && m_jumpFactor < 0.1 ) {
            if((player->pos().x() < m_platform->pos().x()) || (player->pos().x() > m_platform->pos().x() + m_platform->boundingRect().width())){
                if(!m_platform){
                    m_platform = 0;
                }
                if(player->pos().y() < m_groundLevel){
                    player->fall();
                    mFallTimer.start();
                    return;
                }
            }
        }
    }
    player->setPos(player->pos().x(), y);
}

void MyScene::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState){
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running){
        //handleCollisionWithPlatform();
    }
}

qreal MyScene::jumpFactor() const{

    return m_jumpFactor;
}

void MyScene::setJumpFactor(const qreal &jumpFactor){

    if (m_jumpFactor == jumpFactor)
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);
}




//detect whether the player hit something
bool MyScene::handleCollisionWithPlatform(){
    QGraphicsItem* platform =  collidingPlatforms();
    if(platform) {
        QPointF platformPos = platform->pos();   
        if(player->is_touching_foot(platform) && player->pos().x()>platform->pos().x()){

            if(typeid(*platform) == typeid(BrickPlatform)){
                player->setPos(player->pos().x(), platformPos.y() - player->boundingRect().height());
            }
            else if(typeid(*platform) == typeid(Police) || typeid(*platform) == typeid(Movingdog) || typeid(*platform) == typeid(ObstacleDog)){
                m_platform = 0;
            }
            else if(typeid(*platform) == typeid(Train)){

            }
            else{
                player->setPos(player->pos().x(), platformPos.y() - player->boundingRect().height());
            }

            m_platform = platform;
            m_jumpAnimation->stop();
            return true;
        }
        else if(player->pos().y()+player->boundingRect().height()<= platform->pos().y()+platform->boundingRect().height()){
            player->setPos(platform->pos().x()-player->boundingRect().width(), player->pos().y());
            m_platform = 0;
            return false;
        }
    }
    else{
        m_platform = 0;
    }
    return false;
}

QGraphicsItem* MyScene::collidingPlatforms(){
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach(QGraphicsItem *item, items){
        if(Rock *rock = qgraphicsitem_cast<Rock *>(item)){
            return rock;
        }
        if(Pipe *pipe = qgraphicsitem_cast<Pipe *>(item)){
            return pipe;
        }
        if(BrickPlatform *brick_platform = qgraphicsitem_cast<BrickPlatform *>(item)){
            return brick_platform;
        }
    }
    return 0;
}

void MyScene::checkCollidingRock(){
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach (QGraphicsItem* item, items) {
        Rock* r = qgraphicsitem_cast<Rock*>(item);
        if(r){
            if (!(player->pos().y() > r->pos().y()+27) && !(player->pos().y() < r->pos().y()+27)){
                if(player->pos().x() < r->pos().x())
                    player->setPos(r->pos().x()- player->boundingRect().width(),player->pos().y());
                if(player->pos().x() > r->pos().x()){
                    player->setPos(r->pos().x() + r->boundingRect().width(),player->pos().y());
                }
            }

                }
            }
}


void MyScene::checkCollidingDiamond(){
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach (QGraphicsItem* item, items){
        Diamond* d = qgraphicsitem_cast<Diamond*>(item);
        if(d){
            hit_diamond = true;
            removeItem(d);
            //deallocate memory
            delete d;
            d = nullptr;

            for (int i = 0; i < 5; ++i){
                m_score->increase_score();
            }
            m_score->increase_diamondCount();


            QMediaPlayer *coin = new QMediaPlayer();
            coin->setMedia(QUrl("qrc:/new/music/sound/coin.wav"));
            coin->play();

            plus_five->setVisible(1);
            plus_five_presence = true;
            plus_five_time = 0;
        }
    }
}




//check collision with flag ->game over

void MyScene::checkCollidingFlag(){


    QList<QGraphicsItem*> items = collidingItems(player);
    foreach (QGraphicsItem* item, items) {

    Flag* f = qgraphicsitem_cast<Flag*>(item);
    if(f){
//fix this
        player->hide();
        removeItem(f);
        //deallocate memeory
        delete f;
        f = nullptr;
        levelCompleteWindow = new LevelCompleteWindow();
        levelCompleteWindow->setFixedSize(800,533);
        levelCompleteWindow->setWindowFlags(((levelCompleteWindow ->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
        levelCompleteWindow->exec();
        }

    }

}


void MyScene::checkCollidingPipe(){
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach (QGraphicsItem* item, items) {
        Pipe* p = qgraphicsitem_cast<Pipe*>(item);
        if(p){
            if (player->pos().y()<p->pos().y()&& player->pos().y() > p->pos().y()-60){
                //entering the pipe from left
                if(player->direction()==1 && player->pos().x() < p->pos().x()){
                    player->setPos(p->pos().x()+p->boundingRect().width(),player->pos().y());
                }
                //entering the pipe from right
                if(player->direction()==-1 && player->pos().x() > p->pos().x()){
                    player->setPos(p->pos().x() -player->boundingRect().width(),player->pos().y());
                }

            }

        }
    }
}

void MyScene::checkCollidingCoin(){

    QList<QGraphicsItem*> items = collidingItems(player);
    foreach (QGraphicsItem* item, items){
        Coin* d = qgraphicsitem_cast<Coin*>(item);
        if(d){
            hit_coin = true;

            removeItem(d);

            //deallocate memory
            delete d;
            d = nullptr;

                m_score->increase_score();

            QMediaPlayer *coin = new QMediaPlayer();
            coin->setMedia(QUrl("qrc:/new/music/sound/coin.wav"));
            coin->play();
            if (plus_five_presence == true){
                if (plus_one_presence == true){
                    plus_one->setVisible(0);
                }

                plus_one->setPos(m_score->pos().x(), m_groundLevel - plus_one->boundingRect().height()-550);
                plus_one->setVisible(1);
            } else {
                plus_one->setVisible(1);
            }


            plus_one_presence = true;
            plus_one_time = 0;

        }
    }

}

void MyScene::handle_hit_train(){
    //detect which train is hitting
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach (QGraphicsItem* item, items) {
        m_train = qgraphicsitem_cast<Train*>(item);
    }
    train_hit = true;
    if(!t_timer.isActive()){
        t_timer.start();
    }

    if (player->pos().x()>0){
        player->setPos(m_train_1->pos().x()-player->boundingRect().width(),player->pos().y());
        movePlayer();

    }
    else{
        player->setPos(0,player->pos().y());
        movePlayer();

    }

}

void MyScene::handle_nohit_train(){
    train_hit = false;
    if(t_timer.isActive()){
    t_timer.stop();
    }
}

void MyScene::train_push(){
    int speed = m_train->get_speed();

    //move screen (scroll) follow train speed
    if (scroll->value()<=0){
        t_timer.stop();
        return;
    }
    //player->setPos(m_train->pos().x()-player->boundingRect().width(),player->pos().y());

    scroll->setValue(-speed + scroll->value());
    m_sky->setPos(-speed + m_sky->pos().x(),0);
    m_gameTimer->setPos(-speed + m_gameTimer->pos().x(), m_gameTimer->y());
    m_diamondcounter->setPos(-speed + m_diamondcounter->pos().x(), m_diamondcounter->y());
    m_score->setPos(-speed + m_score->pos().x(), m_score->y());
    movePlayer();


}
