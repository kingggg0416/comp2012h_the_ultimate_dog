/*
when people lose the game, it will pop up this game over window. 
there are 2 buttons which are "play again" and "quit the game".
*/

#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class GameOverWindow;
}

class GameOverWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverWindow(QWidget *parent = nullptr);
    ~GameOverWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::GameOverWindow *ui;

};

#endif // GAMEOVERWINDOW_H
