/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
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
        login->resize(1023, 578);
        login->setStyleSheet(QString::fromUtf8("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back.jpg);"));
        centralwidget = new QWidget(login);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(620, 140, 221, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(620, 210, 221, 41));
        lineEdit_2->setStyleSheet(QString::fromUtf8("border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(560, 140, 51, 41));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(570, 230, 31, 16));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(670, 300, 121, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 120, 421, 381));
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/Login.png);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 10, 61, 71));
        label_4->setStyleSheet(QString::fromUtf8("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/mouse.png);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(110, 40, 91, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Berlin Sans FB Demi\";"));
        login->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(login);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        login->setStatusBar(statusbar);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("login", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("login", "\347\231\273\345\275\225", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QCoreApplication::translate("login", "LOGIN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
