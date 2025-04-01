#pragma once
#ifndef STARTPAGE_H
#define STARTPAGE_H
#include "GamePage.h"
#include <QWidget>
#include <QPushButton>

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget* parent = nullptr);
    ~StartPage();

private slots:
    void onStartButtonClicked();

private:
    void setupUI();
    void setupConnections();

    QPushButton* startButton;
};

#endif // STARTPAGE_H
