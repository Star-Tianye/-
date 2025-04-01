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
    void onShowNextPath(); // �����ۺ���
    void resizeEvent(QResizeEvent* event);
private:
    void setupUI();
    void setupConnections();
    void drawMaze(); // ���ڻ����Թ�ͼ��

    QGraphicsView* mazeView;
    QGraphicsScene* mazeScene;
    QPushButton* generateButton;
    QPushButton* startButton;
    QPushButton* exitButton;
    QSpinBox* rowSpinBox;
    QSpinBox* colSpinBox;
    QComboBox* algorithmComboBox;

    Maze* maze;  // ��� Maze ����ָ��
    QTextEdit* pathInfoText;  // ������������ʾ·����Ϣ

    void drawPath(); // ���� drawPath ����
    void showPathInfo();
    int currentPathIndex;  // ��ǰ��ʾ��·������

    QPushButton* nextPathButton;  // ��Ӱ�ťָ�룬���ơ���ʾ��һ��·������ť����ʾ
};

#endif // GAMEPAGE_H
