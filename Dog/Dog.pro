QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backgrounditem.cpp \
    brickplatform.cpp \
    character.cpp \
    coincounter.cpp \
    flag.cpp \
    gameoverwindow.cpp \
    levelcompletewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    movingdog.cpp \
    myscene.cpp \
    obstacledog.cpp \
    pipe.cpp \
    rock.cpp \
    police.cpp \
    scorecounter.cpp \
    timer.cpp \
    title.cpp \
    train.cpp \
    view.cpp \
    coin.cpp \
    diamond.cpp \
    wallplatform.cpp

HEADERS += \
    backgrounditem.h \
    brickplatform.h \
    character.h \
    coincounter.h \
    flag.h \
    gameoverwindow.h \
    levelcompletewindow.h \
    mainwindow.h \
    movingdog.h \
    myscene.h \
    objecttype.h \
    obstacledog.h \
    pipe.h \
    rock.h \
    police.h \
    scorecounter.h \
    timer.h \
    title.h \
    train.h \
    view.h \
    coin.h \
    diamond.h \
    wallplatform.h

FORMS += \
    gameoverwindow.ui \
    levelcompletewindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    music.qrc \
    photo.qrc

DISTFILES += \
    image/background new .jpg \
    image/background new .jpg \
    image/background new .jpg \
    image/character-photo.png \
    image/coin.png \
    image/corgi.jpg \
    image/diamond.png \
    image/doge.jpg \
    image/flag.png \
    image/game background.jpg \
    image/game background.jpg \
    image/game background.jpg \
    image/moving_dog.png \
    image/movingdog_original.png \
    image/name.jpg \
    image/play button 1.png \
    image/play button 1.png \
    image/play button.jpg \
    image/play button.jpg \
    image/play button.jpg \
    image/police.png \
    image/rail-transparent.png \
    image/railway-graphic.jpg \
    image/rock.jpg \
    image/rock2-graphic.png \
    image/train1-graphic.png \
    image/train3-graphic.png \
    image/walking_test.png
