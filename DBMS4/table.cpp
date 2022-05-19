#include <table.h>
#include<iostream>
using namespace std;
Table::Table(){

}

Table::Table(QString tableName,QString databasename){
    this->tableName=tableName;
    this->databasename=databasename;
    QFile f("D:/dbms-master/FILE/"+databasename+"/table/"+tableName+".txt");
    if(!f.exists())
    {
         throw QString("table "+tableName+" is not exist!");
    }
    else if(!readHead()||!readData()){
       throw QString("table "+tableName+":There is no or exception");
    }
}
bool Table::readHead(){
    //读取字段文件
    QFile f("D:/dbms-master/FILE/"+databasename+"/table/"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        throw QString("table "+tableName+":The field file cannot be opened");
        return false;
    }
    //记录字段属性
    while(!f.atEnd()){
        QByteArray line = f.readLine();
        QString str(line);
        str = str.simplified();
        QStringList list = str.split(" ");
        field row;

        row.set_name(list.value(0));
        row.set_dataType(list.value(1));
        row.set_PK(list.value(2));//主键
        row.set_unique(list.value(3));//唯一性
        row.set_notNull(list.value(4));//非空
       // row.set_defaultValue(list.value(5));//默认值
        head.append(row);
    }
    f.close();
    return true;
}
void Table::setData(QVector<QVector<QString> > newData){
    this->data=newData;
}
void Table::setHead(QVector<field > newHead){
    this->head=newHead;
}
bool Table::readData(){
    //读取数据文件
    QFile f("D:\\dbms-master\\FILE\\"+databasename+"\\data\\"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        throw QString("table"+tableName+"The data file could not be opened");
        return false;
    }
    while(!f.atEnd()){
        QVector<QString> row;
        QByteArray line = f.readLine();
        QString str(line);
//        str = str.simplified();
        QStringList list = str.split(",");
        for(int i=0;i<list.size();i++){
            if(list.value(i)!="\n")
                row.append(list.value(i));
        }
        data.append(row);
    }
    f.close();
    return true;
}
QVector<field> Table::getHead(){
    return head;
}
QVector<QVector<QString>> Table::getData(){
    return data;
}
bool Table::UpdateAllData(){
    //打开数据文件
    backups();
    QFile f("D:\\dbms-master\\FILE\\"+databasename+"\\data\\"+tableName+".txt");
   if(!f.open(QIODevice::WriteOnly|QIODevice::Text)){
       throw QString("table"+tableName+"The data file could not be opened");
       return false;
   }
   QTextStream out(&f);
   QString oneRow;
   for(int i=0;i<data.size();i++){
       for(int j=0;j<data.value(i).size();j++){
           oneRow.append(data.value(i).value(j));
           oneRow.append(",");
       }
       out<<oneRow<<endl;
       oneRow.clear();
   }
   f.close();
   constraint();
   return true;
}
bool Table::InsertData(QMap<QString,QString> row){
   QFile f("D:\\dbms-master\\FILE\\"+databasename+"\\data\\"+tableName+".txt");
   if(!f.open(QIODevice::ReadWrite | QIODevice::Append)){
       throw QString("table"+tableName+"The data file could not be opened");
       return false;
   }

   backups();

   QString oneRow;
   QTextStream out(&f);
   for(int i=0;i<head.size();i++){
       if(row.contains(head[i].get_name())){
           oneRow.append(row.find(head[i].get_name()).value());
       }
       else if(head[i].get_defaultValue()!="FALSE"){
           oneRow.append(head[i].get_defaultValue());
       }
       oneRow.append(",");
   }
   out<<oneRow<<endl;
   f.close();

   constraint();

   return true;
}
QVector<int> Table::FindAllData(QString column, QString judge, QString condtion){
    QVector<int> all;
    int order = getFieldIndex(column);
    if(order==-1){
        throw QString("Unknown field"+column);
    }
    //qDebug()<<condtion;
    int order2 = getFieldIndex(condtion);
   // qDebug()<<"order2:"<<order2;

    for(int j=0;j<data.size();j++){
        if(order2!=-1){
            condtion = data[j].value(order2);
            //qDebug()<<"111:"<<condtion;
            //qDebug()<<"222"<<data[j][order2];
        }
        if(judge==">="){
            if(data.value(j).value(order)>=condtion){
                all.append(j);
            }
        }
        else if(judge=="<="){
            if(data.value(j).value(order)<=condtion){
                all.append(j);
            }
        }
        else if(judge=="!="){
            if(data.value(j).value(order)!=condtion){
                all.append(j);
            }
        }
        else if(judge==">"){
            if(data.value(j).value(order)>condtion){
                all.append(j);
            }
        }
        else if(judge=="<"){
            if(data.value(j).value(order)<condtion){
                all.append(j);
            }
        }
        else if(judge=="="){
            if(data.value(j).value(order)==condtion){
                all.append(j);
            }
        }
    }
    return all;
}

bool Table::DeleteAllData(){
    //打开数据文件
    QFile f("D:\\dbms-master\\FILE\\"+databasename+"\\data\\"+tableName+".txt");
   if(!f.open(QIODevice::WriteOnly|QIODevice::Text)){
       throw QString("table"+tableName+"The data file could not be opened");
       return false;
   }
   f.close();
   return true;
}
bool Table::UpdateOneData(int id, QString column, QString value){
    int order = getFieldIndex(column);
    if(order==-1){
        throw QString("Unknown field"+column);
        return false;
    }
    data[id][order]=value;
    return true;
}
int Table::getFieldIndex(QString name){
    for(int i=0;i<head.size();i++){
        if(head[i].get_name()==name){
            return i;
        }
    }
    return -1;
}
QString Table::getFieldType(QString name){
    for(int i=0;i<head.size();i++){
        if(head[i].get_name()==name){
            return head[i].get_dataType();
        }
    }
    throw QString("Unknown field"+name);
    return "";
}
//得到两个表的笛卡尔积
Table Table::Cartesian(Table t){
    Table newT;
    QString sameFieldName;
    int id=-1;
    //添加字段
    if(newT.tableName.isEmpty()){
        newT.tableName=t.getTableName();
    }
    for(int i=0;i<t.getHead().size();i++){
        id = getFieldIndex(t.getHead()[i].get_name());
        //具有相同字段时加前缀 table.field
        if(id!=-1){
            sameFieldName = head[id].get_name();
            QString newName;
            newName.append(t.getTableName());
            newName.append(".");
            newName.append(sameFieldName);
            t.head[i].set_name(newName);
            newName.clear();
            newName.append(tableName);
            newName.append(".");
            newName.append(sameFieldName);
            head[id].set_name(newName);
        }
        //newT.head.append(t.getHead()[i]);
    }
    //添加字段
    for(int i=0;i<getHead().size();i++){
      newT.head.append(getHead()[i]);
    }
    for(int i=0;i<t.getHead().size();i++){
        newT.head.append(t.getHead()[i]);
    }
    //添加数据
    if(getData().size()==0){
        for(int j=0;j<t.getData().size();j++){
            QVector<QString> row;
            row.append(t.getData()[j]);
            newT.data.append(row);
        }
    }
    else if(t.getData().size()==0){
        for(int j=0;j<getData().size();j++){
            QVector<QString> row;
            row.append(getData()[j]);
            newT.data.append(row);
        }
    }
    else{
        for(int i=0;i<getData().size();i++){
            for(int j=0;j<t.getData().size();j++){
                QVector<QString> row;
                row.append(getData()[i]);
                row.append(t.getData()[j]);
                newT.data.append(row);
            }
        }
    }
    return newT;
}
QString Table::getTableName(){
    return tableName;
}
QVector<int> Table::getWhere(QStringList judgeList){
    QString temp;
    QRegularExpression re("([A-Za-z_\\.]+)\\s?(>|<|>=|<=|!=|=)\\s?([\\w\\.]+)");
    QRegularExpressionMatch match;
    QString column;
    QString judge;
    QString value;
    QVector<int> OR;
    // or判断
    for(int i=0;i<judgeList.size();i++){
        temp=judgeList[i];
        qDebug()<<"temp"<<temp;
        QVector<int> AND;
        // and 判断
        if(temp.contains(" and ")){
            QStringList AndList = temp.split(" and ");
            for(int i=0;i<AndList.size();i++){
                QVector<int> tem;
                match = re.match(AndList[i]);
                if(match.hasMatch())
                {
                    column = match.captured(1);
                    judge=match.captured(2);
                    value = match.captured(3);
                    //判断字段是否存在
                    if(getFieldIndex(column)==-1){
                        throw QString("出现未知字段");
                    }
                    tem = FindAllData(column,judge,value);
                    if(i==0){
                      AND=tem;
                    }
                    else{
                        //交集
                        QVector<int> temAND;
                        std::sort(tem.begin(),tem.end());
                        std::sort(AND.begin(),AND.end());
                        std::set_intersection(AND.begin(),AND.end(),tem.begin(),tem.end(),std::back_inserter(temAND));
                        AND = temAND;
                    }
                }
                else {
                    AND.clear();
                }
            }
            //并集
            QVector<int> ORAND;
            std::sort(OR.begin(),OR.end());
            std::sort(AND.begin(),AND.end());
            std::set_union(AND.begin(),AND.end(),OR.begin(),OR.end(),std::back_inserter(ORAND));
            OR = ORAND;
        }
        else{
            QVector<int> tem;
            match = re.match(temp);
            if(match.hasMatch())
            {
                column = match.captured(1);
                judge=match.captured(2);
                value = match.captured(3);
                qDebug()<<"column"<<column;
                tem = FindAllData(column,judge,value);
            }
            else{
                throw QString("匹配失败");
            }
            //做并集
            QVector<int> temOR;
            std::sort(OR.begin(),OR.end());
            std::sort(tem.begin(),tem.end());
            std::set_union(tem.begin(),tem.end(),OR.begin(),OR.end(),std::back_inserter(temOR));
            OR = temOR;
        }
    }
    return OR;
}

Table Table::SelectData(QStringList columnList,QStringList groupList,QStringList orderList,bool desc){
    Table t;
    //全参
    if(columnList[0]=="*"){
        for(int i=0;i<getHead().size();i++){
            field row;
            row.set_name(getHead()[i].get_name());
            row.set_dataType(getHead()[i].get_dataType());
            t.head.append(row);
        }
    }
    //部分参
    else{
        for(int i=0;i<columnList.size();i++){
            field row;
            //存在未知字段
            if(getFieldIndex(columnList.value(i))==-1){
                throw QString("There is an unknown field"+columnList.value(i));
            }
            row.set_name(columnList.value(i));
            row.set_dataType(getFieldType(columnList.value(i)));
            t.head.append(row);
        }
    }
    for(int i=0;i<getData().size();i++){
        QVector<QString> row;
        for(int j=0;j<getHead().size();j++){
            if(t.getFieldIndex(getHead()[j].get_name())!=-1){
                row.append(getData()[i][j]);
            }
        }
        t.data.append(row);
    }
    if(!groupList.isEmpty()){
        t=t.groupBy(groupList);
    }
    if(!orderList.isEmpty()){
        t=t.orderBy(orderList,desc);
    }
    return t;
}

Table Table::orderBy(QStringList orderList, bool desc){
    Table t;
    try
    {
        t.head=this->head;
        t.data=this->data;
        for(int i=orderList.size()-1;i>=0;i--){
            t=t.sort(orderList[i],desc);
        }
    }catch(QString exception){
        throw QString(exception);
    }
    return t;
}

Table Table::sort(QString column, bool desc){
    Table t;
    int order = getFieldIndex(column);
    if(order==-1){
        throw QString("未知的字段"+column);
    }
    t.head=this->head;
    t.data=this->data;
    for(int i=0;i<t.data.size()-1;i++){
        for(int j=0;j<t.data.size()-1-i;j++){
            if(desc){
                if(t.data[j][order] < t.data[j+1][order]){
                    qDebug()<<"old t.data[j]"<<j<<t.data[j][order];
                    qDebug()<<"old t.data[j+1]"<<t.data[j+1][order];
                    t.data[j].swap(t.data[j+1]);
                    //std::swap(t)
                    qDebug()<<"new t.data[j]"<<j<<t.data[j][order];
                    qDebug()<<"new t.data[j+1]"<<t.data[j+1][order];
                }
            }
            else{
                if(t.data[i][order] > t.data[i+1][order]){
                    t.data[i].swap(t.data[i+1]);
                }
            }
        }
    }
    return t;
}

Table Table::groupBy(QStringList groupList){
    Table t;
    if(groupList.size()!=head.size()){
                throw QString("group 与 column 不匹配");
    }
    t.head=this->head;
    //t.data=this->data;
    for(int i=0;i<this->data.size();i++){
        if(!t.ExistinTable(this->data[i])){
            t.data.append(this->data[i]);
        }
    }
    return t;
}

bool Table::ExistinTable(QVector<QString> row){
    bool same = true;
    for(int i=0;i<this->data.size();i++){
        same=true;
        for(int j=0;j<this->head.size();j++){
            if(this->data[i][j]!=row[j]){
                same=false;
                break;
            }
        }
        if(same){
            return true;
        }
    }
    return false;
}

bool Table::constraint()
{
    qDebug()<<"123";

    Table t(tableName,databasename);

    QString throwmessage;

    bool target=false;//是否终止
    bool PK=false;//主键
    bool UNIQUE=false;
    bool NOTNULL=false;
    QStringList unique;//唯一性

    for(int i=0;i<t.getHead().size();i++)
    {

        if(t.getHead()[i].get_PK()=="TRUE")//主键
        {
            if(!PK)
            {
                PK=true;
            }
            else
            {
                throwmessage.append("table:"+tableName+"--The primary key is not unique!");
                target=true;
            }
        }
        if(t.getHead()[i].get_unique()=="TRUE")//唯一性
        {
            for(int j=0;j<t.getData().size();j++)//获取列数据
            {
                unique<<t.getData()[j][i];
            }
            for(int j=0;j<t.getData().size();j++)
            {
                for(int k=0;k<t.getData().size();k++)
                {
                    if(k!=j)
                    {
                        if(t.getData()[j][i]==unique[k])
                        {
                            UNIQUE=true;
                            target=true;
                        }
                    }
                }
            }
        }
        if(t.getHead()[i].get_notNull()=="TRUE")//非空
        {
            for(int j=0;j<t.getData().size();j++)//获取列数据
            {
                if(t.getData()[j][i].isEmpty())
                {
                    NOTNULL=true;
                    target=true;
                }
            }
        }

        if(UNIQUE)
        {
            throwmessage.append(t.getHead()[i].get_name()+"--The uniqueness of is not satisfied!\n");
            UNIQUE=false;
        }
        if(NOTNULL)
        {
            throwmessage.append(t.getHead()[i].get_name()+"--Non null constraints are not satisfied!\n");
            NOTNULL=false;
        }
        unique.clear();
    }

    if(target)//是否结束操作
    {
        QFile fcache("D:\\dbms-master\\FILE\\"+databasename+"\\data\\"+tableName+".txt");//清空
        fcache.open(QFile::WriteOnly|QFile::Truncate);
        fcache.close();
        QFile ffcache("D:\\dbms-master\\FILE\\"+databasename+"\\data\\"+tableName+".txt");//还原
        ffcache.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream out(&ffcache);
        qDebug()<<textcache;
        out<<textcache;
        ffcache.close();
        throw QString(throwmessage);
    }
    return false;
}

void Table::backups()
{
    QFile cache("D:\\dbms-master\\FILE\\"+databasename+"\\data\\"+tableName+".txt");//从缓存文件中获取之前的语句内容并还原
    cache.open(QIODevice::ReadOnly);
    QTextStream tcache(&cache);
    textcache = tcache.readAll();
    cache.close();
}
