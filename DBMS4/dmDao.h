//负责数据修改包括增删改查与查询
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
    bool insertTo(QString tableName,QString databasename,QStringList columnList,QStringList paramList);
    bool deleteTo(QString tableName,QString databasename,QStringList judgeList);
    bool updateTo(QString tableName,QString databasename,QString column,QString value,QStringList judgeList);
    Table selectTo(QString databasename,QStringList tableList, QStringList columnList, QStringList judgeList,QStringList groupList,QStringList orderList,bool desc);
};
#endif // DMDAO_H
