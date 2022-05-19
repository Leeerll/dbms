#ifndef DMDAO_H
#define DMDAO_H
#include<QStringList>
#include<QVector>
#include<QQueue>
#include<QMap>
#include<table.h>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<set>
#include<algorithm>
class dmDao{
public:
    bool insertDao(QString tableName,QString databasename,QStringList columnList,QStringList paramList);
    bool deleteDao(QString tableName,QString databasename,QStringList judgeList);
    bool updateDao(QString tableName,QString databasename,QString column,QString value,QStringList judgeList);
    Table selectDao(QString databasename,QStringList tableList, QStringList columnList, QStringList judgeList,QStringList groupList,QStringList orderList,bool desc);
};
#endif // DMDAO_H
