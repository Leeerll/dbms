/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(1001, 600);
        login->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/6.jpg);"));
        centralwidget = new QWidget(login);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(630, 130, 221, 41));
        lineEdit->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(630, 210, 221, 41));
        lineEdit_2->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(490, 130, 121, 41));
        label->setStyleSheet(QStringLiteral("font: 75 16pt \"Berlin Sans FB Demi\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(490, 210, 131, 41));
        label_2->setStyleSheet(QStringLiteral("font: 75 16pt \"Berlin Sans FB Demi\";"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(680, 300, 121, 51));
        pushButton->setStyleSheet(QStringLiteral("font: 75 16pt \"Berlin Sans FB Demi\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(90, 10, 131, 51));
        label_3->setStyleSheet(QStringLiteral("font: 75 26pt \"Berlin Sans FB Demi\";"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 0, 61, 71));
        label_4->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/mouse.png);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 90, 421, 381));
        label_5->setStyleSheet(QStringLiteral("border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/Login.png);"));
        login->setCentralWidget(centralwidget);
        menubar = new QMenuBar(login);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1001, 26));
        login->setMenuBar(menubar);
        statusbar = new QStatusBar(login);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        login->setStatusBar(statusbar);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QApplication::translate("login", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("login", "username", Q_NULLPTR));
        label_2->setText(QApplication::translate("login", "password", Q_NULLPTR));
        pushButton->setText(QApplication::translate("login", "Login", Q_NULLPTR));
        label_3->setText(QApplication::translate("login", "Login", Q_NULLPTR));
        label_4->setText(QString());
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
