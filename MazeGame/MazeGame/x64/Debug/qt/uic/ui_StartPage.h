/********************************************************************************
** Form generated from reading UI file 'StartPage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTPAGE_H
#define UI_STARTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QPushButton *btnEnterGame;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(913, 650);
        label = new QLabel(Form);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 10, 911, 631));
        label->setStyleSheet(QString::fromUtf8("background-image: url(\"C:/Users/Lenovo/Desktop/true.jpg\");\n"
"background-position: center;\n"
"background-repeat: no-repeat;\n"
""));
        btnEnterGame = new QPushButton(Form);
        btnEnterGame->setObjectName("btnEnterGame");
        btnEnterGame->setGeometry(QRect(360, 370, 171, 71));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        btnEnterGame->setText(QCoreApplication::translate("Form", "\350\277\233\345\205\245\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTPAGE_H
