#pragma once
#ifndef GAMEPAGE_H
#define GAMEPAGE_H
#include <Maze.h>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <qboxlayout.h>
class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget* parent = nullptr);
    ~GamePage();
private slots:
    void onGenerateMaze();
    void onStartGame();
    void onExitGame();
    void onShowNextPath(); // 新增槽函数
    void resizeEvent(QResizeEvent* event);
private:
    void setupUI();
    void setupConnections();
    void drawMaze(); // 用于绘制迷宫图形

    QGraphicsView* mazeView;
    QGraphicsScene* mazeScene;
    QPushButton* generateButton;
    QPushButton* startButton;
    QPushButton* exitButton;
    QSpinBox* rowSpinBox;
    QSpinBox* colSpinBox;
    QComboBox* algorithmComboBox;

    Maze* maze;  // 添加 Maze 对象指针
    QTextEdit* pathInfoText;  // 新增：用于显示路径信息

    void drawPath(); // 声明 drawPath 方法
    void showPathInfo();
    int currentPathIndex;  // 当前显示的路径索引

    QPushButton* nextPathButton;  // 添加按钮指针，控制“显示下一条路径”按钮的显示
};

#endif // GAMEPAGE_H
