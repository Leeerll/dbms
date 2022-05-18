#ifndef TABLE_H
#define TABLE_H
#include<QMap>
#include<QQueue>
#include<QVector>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<algorithm>
#include<field.h>
#include<set>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
class Table{
public:
    Table();
    Table(QString tableName,QString databasename);
    bool readHead();
    bool readData();
    QVector<field> getHead();
    QVector<QVector<QString>> getData();
    void setData(QVector<QVector<QString>> newData);
    void setHead(QVector<field> newHead);
    bool UpdateAllData();
    bool UpdateOneData(int id,QString column,QString value);
    QVector<int> FindAllData(QString column,QString judge,QString condtion);
    bool DeleteAllData();
    bool InsertData(QMap<QString,QString> row);
    Table SelectData(QStringList columnList,QStringList groupList,QStringList orderList,bool desc);//查询

    QVector<int> getWhere(QStringList judgeList);
//    Table orderBy(QStringList orderList,bool desc);
//    Table groupBy(QStringList groupList);
    Table Cartesian(Table t);

    QString getTableName();
    QString getFieldType(QString name);
    int getFieldIndex(QString name);

    Table sort(QString column,bool desc);
    Table orderBy(QStringList orderList,bool desc);

    bool  ExistinTable(QVector<QString> row);
    Table  groupBy(QStringList groupList);

    bool constraint();
    void backups();
    //bool cmp(const QVector<QVector<QString>> &v1,const QVector<QVector<QString>>);
protected:
public:
    QString tableName;
    QString databasename;
    QString textcache;
    QVector<QVector<QString>> data;
    QVector<field> head;
};

#endif // TABLE_H
