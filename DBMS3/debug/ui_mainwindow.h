/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1065, 688);
        MainWindow->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/6.jpg);"));
        open = new QAction(MainWindow);
        open->setObjectName(QStringLiteral("open"));
        save = new QAction(MainWindow);
        save->setObjectName(QStringLiteral("save"));
        back = new QAction(MainWindow);
        back->setObjectName(QStringLiteral("back"));
        db = new QAction(MainWindow);
        db->setObjectName(QStringLiteral("db"));
        table = new QAction(MainWindow);
        table->setObjectName(QStringLiteral("table"));
        trigger = new QAction(MainWindow);
        trigger->setObjectName(QStringLiteral("trigger"));
        login = new QAction(MainWindow);
        login->setObjectName(QStringLiteral("login"));
        adddb = new QAction(MainWindow);
        adddb->setObjectName(QStringLiteral("adddb"));
        deletedb = new QAction(MainWindow);
        deletedb->setObjectName(QStringLiteral("deletedb"));
        addtable = new QAction(MainWindow);
        addtable->setObjectName(QStringLiteral("addtable"));
        deletetable = new QAction(MainWindow);
        deletetable->setObjectName(QStringLiteral("deletetable"));
        addfield = new QAction(MainWindow);
        addfield->setObjectName(QStringLiteral("addfield"));
        modifyfield = new QAction(MainWindow);
        modifyfield->setObjectName(QStringLiteral("modifyfield"));
        deletefield = new QAction(MainWindow);
        deletefield->setObjectName(QStringLiteral("deletefield"));
        adddate = new QAction(MainWindow);
        adddate->setObjectName(QStringLiteral("adddate"));
        finddb = new QAction(MainWindow);
        finddb->setObjectName(QStringLiteral("finddb"));
        findtable = new QAction(MainWindow);
        findtable->setObjectName(QStringLiteral("findtable"));
        findfield = new QAction(MainWindow);
        findfield->setObjectName(QStringLiteral("findfield"));
        logout = new QAction(MainWindow);
        logout->setObjectName(QStringLiteral("logout"));
        readtable = new QAction(MainWindow);
        readtable->setObjectName(QStringLiteral("readtable"));
        deletedate = new QAction(MainWindow);
        deletedate->setObjectName(QStringLiteral("deletedate"));
        updatedate = new QAction(MainWindow);
        updatedate->setObjectName(QStringLiteral("updatedate"));
        readdb = new QAction(MainWindow);
        readdb->setObjectName(QStringLiteral("readdb"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        treeWidget = new QTreeWidget(centralwidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 20, 221, 611));
        treeWidget->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(260, 20, 611, 231));
        textEdit->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(360, 570, 20, 20));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(890, 100, 111, 61));
        pushButton->setStyleSheet(QStringLiteral("font: 87 16pt \"Bodoni MT Black\";background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        clearbutton = new QPushButton(centralwidget);
        clearbutton->setObjectName(QStringLiteral("clearbutton"));
        clearbutton->setGeometry(QRect(890, 20, 111, 61));
        clearbutton->setStyleSheet(QStringLiteral("font: 87 16pt \"Bodoni MT Black\";background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        backbutton = new QPushButton(centralwidget);
        backbutton->setObjectName(QStringLiteral("backbutton"));
        backbutton->setGeometry(QRect(890, 190, 111, 61));
        backbutton->setStyleSheet(QStringLiteral("font: 87 16pt \"Bodoni MT Black\";background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        tadd = new QPushButton(centralwidget);
        tadd->setObjectName(QStringLiteral("tadd"));
        tadd->setGeometry(QRect(291, 371, 20, 20));
        tadd->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        tdelete = new QPushButton(centralwidget);
        tdelete->setObjectName(QStringLiteral("tdelete"));
        tdelete->setGeometry(QRect(330, 370, 20, 20));
        tdelete->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        tcorrect = new QPushButton(centralwidget);
        tcorrect->setObjectName(QStringLiteral("tcorrect"));
        tcorrect->setGeometry(QRect(380, 370, 20, 20));
        tcorrect->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        twrong = new QPushButton(centralwidget);
        twrong->setObjectName(QStringLiteral("twrong"));
        twrong->setGeometry(QRect(430, 370, 20, 20));
        twrong->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        trefresh = new QPushButton(centralwidget);
        trefresh->setObjectName(QStringLiteral("trefresh"));
        trefresh->setGeometry(QRect(470, 370, 20, 20));
        trefresh->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        showWidget = new QTableWidget(centralwidget);
        showWidget->setObjectName(QStringLiteral("showWidget"));
        showWidget->setGeometry(QRect(260, 280, 611, 361));
        showWidget->setStyleSheet(QStringLiteral("background-image: url(:/build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug/DBMS/res/back (2).png);"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1065, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        menu_6 = new QMenu(menubar);
        menu_6->setObjectName(QStringLiteral("menu_6"));
        menu_7 = new QMenu(menubar);
        menu_7->setObjectName(QStringLiteral("menu_7"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        save->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        back->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", Q_NULLPTR));
        db->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        table->setText(QApplication::translate("MainWindow", "\350\241\250", Q_NULLPTR));
        trigger->setText(QApplication::translate("MainWindow", "\350\247\246\345\217\221\345\231\250", Q_NULLPTR));
        login->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", Q_NULLPTR));
        adddb->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        deletedb->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        addtable->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\350\241\250", Q_NULLPTR));
        deletetable->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\241\250", Q_NULLPTR));
        addfield->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\255\227\346\256\265", Q_NULLPTR));
        modifyfield->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\345\255\227\346\256\265", Q_NULLPTR));
        deletefield->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\255\227\346\256\265", Q_NULLPTR));
        adddate->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\350\256\260\345\275\225", Q_NULLPTR));
        finddb->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        findtable->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\350\241\250", Q_NULLPTR));
        findfield->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\350\257\255\345\217\245", Q_NULLPTR));
        logout->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        readtable->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\350\241\250", Q_NULLPTR));
        deletedate->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\256\260\345\275\225", Q_NULLPTR));
        updatedate->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\350\256\260\345\275\225", Q_NULLPTR));
        readdb->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "DB List", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">please input sql here...</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Execute", Q_NULLPTR));
        clearbutton->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        backbutton->setText(QApplication::translate("MainWindow", "Revoke", Q_NULLPTR));
        tadd->setText(QString());
        tdelete->setText(QString());
        tcorrect->setText(QString());
        twrong->setText(QString());
        trefresh->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\350\241\250", Q_NULLPTR));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\255\227\346\256\265", Q_NULLPTR));
        menu_5->setTitle(QApplication::translate("MainWindow", "\350\256\260\345\275\225", Q_NULLPTR));
        menu_6->setTitle(QApplication::translate("MainWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        menu_7->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
