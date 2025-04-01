/********************************************************************************
** Form generated from reading UI file 'MazeGame.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZEGAME_H
#define UI_MAZEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MazeGameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MazeGameClass)
    {
        if (MazeGameClass->objectName().isEmpty())
            MazeGameClass->setObjectName("MazeGameClass");
        MazeGameClass->resize(600, 400);
        menuBar = new QMenuBar(MazeGameClass);
        menuBar->setObjectName("menuBar");
        MazeGameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MazeGameClass);
        mainToolBar->setObjectName("mainToolBar");
        MazeGameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MazeGameClass);
        centralWidget->setObjectName("centralWidget");
        MazeGameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MazeGameClass);
        statusBar->setObjectName("statusBar");
        MazeGameClass->setStatusBar(statusBar);

        retranslateUi(MazeGameClass);

        QMetaObject::connectSlotsByName(MazeGameClass);
    } // setupUi

    void retranslateUi(QMainWindow *MazeGameClass)
    {
        MazeGameClass->setWindowTitle(QCoreApplication::translate("MazeGameClass", "MazeGame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MazeGameClass: public Ui_MazeGameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEGAME_H
