/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *open;
    QAction *save;
    QAction *back;
    QAction *db;
    QAction *table;
    QAction *trigger;
    QAction *login;
    QAction *adddb;
    QAction *deletedb;
    QAction *addtable;
    QAction *deletetable;
    QAction *addfield;
    QAction *modifyfield;
    QAction *deletefield;
    QAction *adddate;
    QAction *finddb;
    QAction *findtable;
    QAction *findfield;
    QAction *logout;
    QAction *readtable;
    QAction *deletedate;
    QAction *updatedate;
    QAction *readdb;
    QWidget *centralwidget;
    QTreeWidget *treeWidget;
    QTextEdit *textEdit;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QPushButton *clearbutton;
    QPushButton *backbutton;
    QPushButton *tadd;
    QPushButton *tdelete;
    QPushButton *tcorrect;
    QPushButton *twrong;
    QPushButton *trefresh;
    QTableWidget *showWidget;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;
    QMenu *menu_7;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1481, 698);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/background.png);"));
        open = new QAction(MainWindow);
        open->setObjectName(QString::fromUtf8("open"));
        save = new QAction(MainWindow);
        save->setObjectName(QString::fromUtf8("save"));
        back = new QAction(MainWindow);
        back->setObjectName(QString::fromUtf8("back"));
        db = new QAction(MainWindow);
        db->setObjectName(QString::fromUtf8("db"));
        table = new QAction(MainWindow);
        table->setObjectName(QString::fromUtf8("table"));
        trigger = new QAction(MainWindow);
        trigger->setObjectName(QString::fromUtf8("trigger"));
        login = new QAction(MainWindow);
        login->setObjectName(QString::fromUtf8("login"));
        adddb = new QAction(MainWindow);
        adddb->setObjectName(QString::fromUtf8("adddb"));
        deletedb = new QAction(MainWindow);
        deletedb->setObjectName(QString::fromUtf8("deletedb"));
        addtable = new QAction(MainWindow);
        addtable->setObjectName(QString::fromUtf8("addtable"));
        deletetable = new QAction(MainWindow);
        deletetable->setObjectName(QString::fromUtf8("deletetable"));
        addfield = new QAction(MainWindow);
        addfield->setObjectName(QString::fromUtf8("addfield"));
        modifyfield = new QAction(MainWindow);
        modifyfield->setObjectName(QString::fromUtf8("modifyfield"));
        deletefield = new QAction(MainWindow);
        deletefield->setObjectName(QString::fromUtf8("deletefield"));
        adddate = new QAction(MainWindow);
        adddate->setObjectName(QString::fromUtf8("adddate"));
        finddb = new QAction(MainWindow);
        finddb->setObjectName(QString::fromUtf8("finddb"));
        findtable = new QAction(MainWindow);
        findtable->setObjectName(QString::fromUtf8("findtable"));
        findfield = new QAction(MainWindow);
        findfield->setObjectName(QString::fromUtf8("findfield"));
        logout = new QAction(MainWindow);
        logout->setObjectName(QString::fromUtf8("logout"));
        readtable = new QAction(MainWindow);
        readtable->setObjectName(QString::fromUtf8("readtable"));
        deletedate = new QAction(MainWindow);
        deletedate->setObjectName(QString::fromUtf8("deletedate"));
        updatedate = new QAction(MainWindow);
        updatedate->setObjectName(QString::fromUtf8("updatedate"));
        readdb = new QAction(MainWindow);
        readdb->setObjectName(QString::fromUtf8("readdb"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        treeWidget = new QTreeWidget(centralwidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(10, 20, 221, 611));
        treeWidget->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);\n"
"background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(280, 20, 611, 231));
        textEdit->setStyleSheet(QString::fromUtf8("font: 75 15pt \"Times New Roman\";\n"
"background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(280, 310, 621, 311));
        tableWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(910, 110, 93, 51));
        pushButton->setStyleSheet(QString::fromUtf8("font: 87 11pt \"Bodoni MT Black\";"));
        clearbutton = new QPushButton(centralwidget);
        clearbutton->setObjectName(QString::fromUtf8("clearbutton"));
        clearbutton->setGeometry(QRect(910, 20, 93, 51));
        clearbutton->setStyleSheet(QString::fromUtf8("font: 87 11pt \"Bodoni MT Black\";"));
        backbutton = new QPushButton(centralwidget);
        backbutton->setObjectName(QString::fromUtf8("backbutton"));
        backbutton->setGeometry(QRect(910, 190, 93, 51));
        backbutton->setStyleSheet(QString::fromUtf8("font: 87 11pt \"Bodoni MT Black\";\n"
"background-color: rgb(255, 255, 255);"));
        tadd = new QPushButton(centralwidget);
        tadd->setObjectName(QString::fromUtf8("tadd"));
        tadd->setGeometry(QRect(671, 270, 30, 30));
        tadd->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/add.png);"));
        tdelete = new QPushButton(centralwidget);
        tdelete->setObjectName(QString::fromUtf8("tdelete"));
        tdelete->setGeometry(QRect(721, 270, 30, 30));
        tdelete->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/delete.png);\n"
"color: rgb(255, 255, 255);"));
        tcorrect = new QPushButton(centralwidget);
        tcorrect->setObjectName(QString::fromUtf8("tcorrect"));
        tcorrect->setGeometry(QRect(771, 270, 30, 30));
        tcorrect->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/correct.png);\n"
"color: rgb(255, 255, 255);"));
        twrong = new QPushButton(centralwidget);
        twrong->setObjectName(QString::fromUtf8("twrong"));
        twrong->setGeometry(QRect(821, 270, 30, 30));
        twrong->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/wrong.png);\n"
"color: rgb(255, 255, 255);"));
        trefresh = new QPushButton(centralwidget);
        trefresh->setObjectName(QString::fromUtf8("trefresh"));
        trefresh->setGeometry(QRect(870, 270, 31, 30));
        trefresh->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/refresh.png);"));
        showWidget = new QTableWidget(centralwidget);
        showWidget->setObjectName(QString::fromUtf8("showWidget"));
        showWidget->setGeometry(QRect(1025, 21, 431, 611));
        showWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        MainWindow->setCentralWidget(centralwidget);
        tableWidget->raise();
        pushButton->raise();
        clearbutton->raise();
        backbutton->raise();
        tadd->raise();
        tdelete->raise();
        tcorrect->raise();
        twrong->raise();
        trefresh->raise();
        showWidget->raise();
        treeWidget->raise();
        textEdit->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1481, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        menu_6 = new QMenu(menubar);
        menu_6->setObjectName(QString::fromUtf8("menu_6"));
        menu_7 = new QMenu(menubar);
        menu_7->setObjectName(QString::fromUtf8("menu_7"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menubar->addAction(menu_6->menuAction());
        menubar->addAction(menu_7->menuAction());
        menu->addAction(open);
        menu->addAction(save);
        menu->addAction(back);
        menu->addAction(login);
        menu->addAction(logout);
        menu_2->addAction(adddb);
        menu_2->addAction(deletedb);
        menu_3->addAction(addtable);
        menu_3->addAction(deletetable);
        menu_4->addAction(addfield);
        menu_4->addAction(modifyfield);
        menu_4->addAction(deletefield);
        menu_5->addAction(adddate);
        menu_5->addAction(deletedate);
        menu_5->addAction(updatedate);
        menu_6->addAction(finddb);
        menu_6->addAction(findtable);
        menu_6->addAction(findfield);
        menu_6->addAction(readtable);
        menu_6->addAction(readdb);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        back->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
        db->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\272\223", nullptr));
        table->setText(QCoreApplication::translate("MainWindow", "\350\241\250", nullptr));
        trigger->setText(QCoreApplication::translate("MainWindow", "\350\247\246\345\217\221\345\231\250", nullptr));
        login->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        adddb->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\225\260\346\215\256\345\272\223", nullptr));
        deletedb->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\225\260\346\215\256\345\272\223", nullptr));
        addtable->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\350\241\250", nullptr));
        deletetable->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\241\250", nullptr));
        addfield->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\255\227\346\256\265", nullptr));
        modifyfield->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\345\255\227\346\256\265", nullptr));
        deletefield->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\255\227\346\256\265", nullptr));
        adddate->setText(QCoreApplication::translate("MainWindow", "\345\242\236\345\212\240\350\256\260\345\275\225", nullptr));
        finddb->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276\346\225\260\346\215\256\345\272\223", nullptr));
        findtable->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276\350\241\250", nullptr));
        findfield->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276\350\257\255\345\217\245", nullptr));
        logout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        readtable->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\350\241\250", nullptr));
        deletedate->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\256\260\345\275\225", nullptr));
        updatedate->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\350\256\260\345\275\225", nullptr));
        readdb->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\346\225\260\346\215\256\345\272\223", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "DB List", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Times New Roman'; font-size:15pt; font-weight:72; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:10pt; font-weight:400;\">please input sql here...</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Execute", nullptr));
        clearbutton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        backbutton->setText(QCoreApplication::translate("MainWindow", "Revoke", nullptr));
        tadd->setText(QString());
        tdelete->setText(QString());
        tcorrect->setText(QString());
        twrong->setText(QString());
        trefresh->setText(QString());
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\272\223", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\350\241\250", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\345\255\227\346\256\265", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\350\256\260\345\275\225", nullptr));
        menu_6->setTitle(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        menu_7->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
