#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <qdebug.h>
#include<QFileDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <table.h>
#include <field.h>
#include <dmdao.h>
#include <qtextcodec.h>
#include <QTextCodec>
#include <QPushButton>
#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <tree.h>
#include "user.h"
#include <QTextStream>
#include <login.h>
#include <mydbms.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool prase();
    void init();
    bool dataParse(QString sql);//解析
    bool Select(QString database,QString sql);
    bool Insert(QString database,QString sql);
    bool Delete(QString database,QString sql);
    bool Update(QString database,QString sql);
    void Exec();//执行

    QString insert_field();//插入字段
    QString drop_field();//删除字段
    void read_tableField(QString tableName);//预读表内字段
    void update_field_file(QString tableName);//更新表内字段

    QString insert_user();//插入用户
    QString drop_user();//删除用户
    void read_userField();
    void update_user_file();//更新用户表内字段
    bool push_user(QString);
    void getUser(QString name);//获取当前用户
    QString namefile;//当前点击表名称
    QString namedatabase;//当前数据库名称
    bool checkPower(QString tableName);//检查表级权限

    bool constraint(QString tablename);//完整性约束判断

    bool dbtest(QString s);

    bool createTable(QString str);
    bool dropTable(QString str);
    bool table_prase(QString str);

    bool createIndex(QString str);

    QString filename;
    QString str;
    QString tmp;
    QString b;
    QString tableName;	    //表名
    QString indexName;

    QQueue<QString> queuewyj;
    QStringList a2;
protected:
    void closeEvent(QCloseEvent *event);

private slots:

    void on_open_triggered();

    void on_addtable_triggered();

    void on_findtable_triggered();

    void on_backbutton_clicked();

    void on_pushButton_clicked();

    void on_clearbutton_clicked();

    void on_readtable(QString,QString);

    void on_readdb_triggered();

    void on_treeWidget_itemSelectionChanged();

    void png();

    void on_trefresh_clicked();

    void on_twrong_clicked();

    void on_tcorrect_clicked();

    void on_tadd_clicked();

    void on_tdelete_clicked();
    void on_textEdit_destroyed();


    void message(QString s);


private:
    Ui::MainWindow *ui;
    QString fileName;
    QString dataname;

    QStringList sqlList;
    //QString sql;
    QQueue<QString> queue;
    QVector<QString> judge;
    QMap<QString,QVector<QString>> map;
    dmDao dao;

    user nowUser;//此时正在操作DBMS的用户
    user thisUser;//要操作的用户
    field thisField;//要操作的字段

    QVector<field> allFields;//将字段文件预读入此
    QVector<user> allUsers;//将用户文件预读于此

    QStringList squece;
    myDBMS *db;
};
#endif // MAINWINDOW_H
