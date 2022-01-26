/*
AS we had to do some work on the scene, we subclass QGraphicsScen and create the new class MyScene. 
There, we implement one part of the game logic.This is convenient since QGraphicsScene inherits QObject and thus we can use Qt's signal and slot mechanism.
*/
#ifndef MYSCENE_H
#define MYSCENE_H

//#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QAbstractAnimation>
#include <QDebug>
#include <QMediaPlayer>
#include "title.h"
#include "backgrounditem.h"
#include "character.h"
#include "rock.h"
#include "scorecounter.h"
#include "coin.h"
#include "diamond.h"
#include "police.h"
#include "movingdog.h"
#include "pipe.h"
#include "wallplatform.h"
#include "gameoverwindow.h"
#include "levelcompletewindow.h"
#include "brickplatform.h"
#include "flag.h"
#include "train.h"
#include "obstacledog.h"


class Character;
class QGraphicsPixmapItem;
class QPropertyAnimation;
class Rock;
class Coin;
class BackgroundItem;
class Player;
class Movingdog;
class QScrollBar;
class Flag;
class CoinCounter;
class WallPlatform;
class Score;
class Timer;
class GameOverWindow;
class LevelCompleteWindow;
class MyScene;
class Diamond;
class Police;
class Movingdog;
class Pipe;
class BrickPlatform;
class Train;
class ObstacleDog;

class MyScene: public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit MyScene(QScrollBar* s, QObject *parent = nullptr);
    void timerEvent(QTimerEvent *);
        //copy for jumping animation
    void setJumpFactor(const qreal &jumpFactor = 0);
    qreal jumpFactor() const;

    bool moving;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void initPlayField();
    void movePlayer();
    void setCharacterModel(int number);
    qreal m_groundLevel;
    int player_velocity;
    bool train_hit;

    //Background items
    BackgroundItem* m_sky;
    BackgroundItem* m_ground;
    BackgroundItem* m_direction_sign;
    BackgroundItem* plus_five;
    BackgroundItem* plus_one;
    BackgroundItem* clock;
    //BackgroundItem* plus_one;
    //BackgroundItem* m_flag;

    //brickplatform items - waterpipes
    BrickPlatform* m_pipe_1;
    BrickPlatform* m_pipe_2;
    BrickPlatform* m_pipe_3;
    BrickPlatform* m_pipe_4;
    BrickPlatform* m_pipe_5;
    BrickPlatform* m_pipe_6;
    BrickPlatform* m_pipe_7;
    BrickPlatform* m_pipe_8;
    BrickPlatform* m_pipe_9;
    BrickPlatform* m_pipe_10;
    BrickPlatform* m_pipe_11;
    BrickPlatform* m_pipe_12;
    BrickPlatform* m_pipe_13;
    BrickPlatform* m_pipe_14;
    BrickPlatform* m_pipe_15;
    BrickPlatform* m_pipe_16;
    BrickPlatform* m_pipe_17;
    BrickPlatform* m_pipe_18;
    BrickPlatform* m_pipe_19;
    BrickPlatform* m_pipe_20;

    //teleport items - cool pipes
    Pipe* pipe_1;
    Pipe* pipe_2;
    Pipe* pipe_3;
    Pipe* pipe_4;
    Pipe* pipe_5;
    Pipe* pipe_6;

    //gameover ui
    GameOverWindow *gameOverWindow;
    //end ui
    LevelCompleteWindow *levelCompleteWindow;

    //score pic
    BackgroundItem* m_diamondcounter;



    Timer *m_gameTimer;
    ScoreCounter* m_score;

    //animated items
    Diamond* m_diamonds;
    Diamond* m_diamonds2;
    Diamond* m_diamonds3;
    Diamond* m_diamonds4;
    Diamond* m_diamonds5;
    Diamond* m_diamonds6;    
    Diamond* m_diamonds7;
    Diamond* m_diamonds8;
    Diamond* m_diamonds9;
    Diamond* m_diamonds10;
    Diamond* m_diamonds11;
    Diamond* m_diamonds12;
    Diamond* m_diamonds13;
    Diamond* m_diamonds14;
    Diamond* m_diamonds15;
    Diamond* m_diamonds16;
    Diamond* m_diamonds17;
    Diamond* m_diamonds18;
    Diamond* m_diamonds19;
    Diamond* m_diamonds20;


    Coin* m_coins;
    Coin* m_coins2;
    Coin* m_coins3;
    Coin* m_coins4;
    Coin* m_coins5;
    Coin* m_coins6;
    Coin* m_coins7;
    Coin* m_coins8;
    Coin* m_coins9;
    Coin* m_coins10;
    Coin* m_coins11;
    Coin* m_coins12;
    Coin* m_coins13;
    Coin* m_coins14;
    Coin* m_coins15;
    Coin* m_coins16;
    Coin* m_coins17;
    Coin* m_coins18;
    Coin* m_coins19;
    Coin* m_coins20;


    Police* m_police;
    Police* m_police2;
    Police* m_police3;
    ObstacleDog* m_dog;
    ObstacleDog* m_dog2;
    //moving items
    Movingdog* m_movingdog;

    //add trains
    Train* m_train;
    Train* m_train_1;
    Train* m_train_2;
    Train* m_train_3;
    



   //wallplatforms for moving items
    WallPlatform *m_wallPlatform1;
    WallPlatform *m_wallPlatform2;
    WallPlatform *m_wallPlatform3;
    WallPlatform *m_wallPlatform4;
    WallPlatform *m_wallPlatform5;
    WallPlatform *m_wallPlatform6;
    WallPlatform *m_wallPlatform7;
    WallPlatform *m_wallPlatform8;

    //testing character.cpp
    Character* player;

    Rock* rock;
    Rock* rock2;
    Flag* m_flag;
    

    //copy for jumping animation
    QTimer mFallTimer;
    QPropertyAnimation *m_jumpAnimation;
    int m_jumpHeight;
    qreal m_jumpFactor;

    bool falling;
    bool jumping;

    QTimer p_timer;

    QTimer plus_timer;


    QTimer t_timer;



    QScrollBar *scroll;

    QGraphicsItem *m_platform = 0;

    bool plus_five_presence;
    int plus_five_time;

    bool plus_one_presence;
    int plus_one_time;

    bool hit_diamond;
    bool hit_coin;
private slots:
    void checkTimer();
    void fallPlayer();
    void jumpPlayer();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

    void checkCollidingRock();

    void end_game();

    void checkCollidingDiamond();

    void checkCollidingFlag();

    void checkCollidingPipe();
    void checkCollidingCoin();

    void handle_hit_train();
    void handle_nohit_train();

    QGraphicsItem* collidingPlatforms();
    bool handleCollisionWithPlatform();



public slots:
    //havebug
   //     void remove_plus_five();

    void train_push();



signals:
    void jumpFactorChanged(qreal);
};

#endif // MYSCENE_H
