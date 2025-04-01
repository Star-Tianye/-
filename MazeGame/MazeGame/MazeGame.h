#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MazeGame.h"

class MazeGame : public QMainWindow
{
    Q_OBJECT

public:
    MazeGame(QWidget *parent = nullptr);
    ~MazeGame();

private:
    Ui::MazeGameClass ui;
};
