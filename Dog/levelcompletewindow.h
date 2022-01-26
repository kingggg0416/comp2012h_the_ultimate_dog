/*
when player reaches the flagpole, it will pop up the game finish window. 
there are 2 buttons which are "play again" and "quit the game".
*/

#ifndef LEVELCOMPLETEWINDOW_H
#define LEVELCOMPLETEWINDOW_H

#include <QDialog>

namespace Ui {
class LevelCompleteWindow;
}

class LevelCompleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LevelCompleteWindow(QWidget *parent = nullptr);
    ~LevelCompleteWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LevelCompleteWindow *ui;
};

#endif // LEVELCOMPLETEWINDOW_H
