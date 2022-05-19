/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(1019, 541);
        login->setStyleSheet(QString::fromUtf8("background-image: url(:/FILE/res/6.jpg);"));
        centralwidget = new QWidget(login);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(670, 130, 251, 51));
        lineEdit->setStyleSheet(QString::fromUtf8("border-image: url(:/FILE/res/back (2).png);"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(670, 220, 251, 51));
        lineEdit_2->setStyleSheet(QString::fromUtf8("border-image: url(:/FILE/res/back (2).png);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(520, 130, 131, 41));
        label->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Berlin Sans FB Demi\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(530, 230, 121, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Berlin Sans FB Demi\";"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(720, 300, 111, 61));
        pushButton->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Berlin Sans FB Demi\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 120, 421, 381));
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/FILE/res/Login.png);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 20, 61, 71));
        label_4->setStyleSheet(QString::fromUtf8("background-image: url(:/FILE/res/mouse.png);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(130, 40, 151, 41));
        label_5->setStyleSheet(QString::fromUtf8("font: 75 26pt \"Berlin Sans FB Demi\";"));
        login->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(login);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        login->setStatusBar(statusbar);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QApplication::translate("login", "MainWindow", nullptr));
        label->setText(QApplication::translate("login", "username", nullptr));
        label_2->setText(QApplication::translate("login", "password", nullptr));
        pushButton->setText(QApplication::translate("login", "Login", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QApplication::translate("login", "LOGIN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
