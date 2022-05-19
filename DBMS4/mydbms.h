#ifndef MYDBMS_H
#define MYDBMS_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <QString>
#include <sstream>
#include <iomanip>
#pragma execution_character_set("utf-8")
#include <direct.h>
#include <io.h>
#include <QDir>
#include <fstream>
#include <QObject>
#include <QMainWindow>
using namespace std;


struct Tables {
    string name;
    string pathName;
    vector<string>colName;//列名称
    vector<string>type;
    vector<int>size;
    FILE* fp;
};

class myDBMS: public QMainWindow{
    Q_OBJECT
    vector<Tables*>tab;
    bool open;
public:
    QString cmd;
    QString prePath;//数据库的文件路径


    myDBMS() {

        cmd = "";
        prePath = "";
        open = false;
//        //建库删库
//        cout << "Please enter the command statement according to the following rules (commands are not case sensitive)" << endl;
//        cout << "create new database: create database databasename" << endl;
//        cout << "delete old database: drop database databasename" << endl;
//        cout << "open database: open database databasename" << endl;
//        cout << "close: close database databasename" << endl;
//        cout << "exit program  : exit" << endl;
    }
    ~myDBMS() {
        for (int i = 0; i < tab.size(); i++) {
            if (tab[i]->fp != NULL)
                fclose(tab[i]->fp);
            delete tab[i];
        }
        tab.resize(0);
        cmd = "";
        prePath = "";
    }
    void run();
    void transfer();//转为小写
    void openDataBase(QString);//打开数据库
    void closeDataBase(QString);//关闭数据库
    void myCreateDataBase(QString); //建立数据库
    void myDropDataBase(QString); //删除数据库
    bool DelDir(const QString &path,QString dataBaseName);//删除文件夹
signals:
    void sendmessage(QString);


    int posIsNos(QString);//辅助函数
};

#endif // MYDBMS_H
