#include "tree.h"

tree::tree()
{

}

tree::tree(QString tableName,QString databaseName){
    this->tableName=tableName;
    this->databaseName=databaseName;
    readHead();
    readData();
}

bool tree::readHead(){
    //读取字段文件
    QFile f("D:\\dbms-master\\FILE\\database\\"+databasename+"\\table\\"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        return false;
    }
    //记录字段属性
    while(!f.atEnd()){
        QByteArray line = f.readLine();
        QString str(line);
        QStringList list = str.split(" ");
        field row;
        row.set_name(list.value(0));
        row.set_dataType(list.value(1));
        row.set_PK(list.value(2));//主键
        row.set_unique(list.value(3));//唯一性
        row.set_notNull(list.value(4));//非空
        row.set_defaultValue(list.at(5));//默认值
        head.append(row);
    }
    f.close();
}

bool tree::readData(){
    //读取数据文件
    QFile f("D:\\dbms-master\\FILE\\database\\"+databasename+"\\data\\"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        return false;
    }
    while(!f.atEnd()){
        QVector<QString> row;
        QByteArray line = f.readLine();
        QString str(line);
        QStringList list = str.split(",");
        for(int i=0;i<list.size();i++){
            if(list.at(i)!="\n")
            row.append(list.at(i));
        }
        data.append(row);
    }
    f.close();}

QVector<field> tree::getHead(){
    return head;
}

QVector<QVector<QString>> tree::getData(){
    return data;
}

void tree::setData(QVector<QVector<QString> > newData){
    this->data=newData;
}
void tree::setHead(QVector<field > newHead){
    this->head=newHead;
}

bool tree::UpdateAllData(){
    //打开数据文件
    QFile f("D:\\dbms-master\\FILE\\database\\"+databasename+"\\data\\"+tableName+".txt");
   if(!f.open(QIODevice::WriteOnly|QIODevice::Text)){
       throw QString("table"+tableName+"The data file could not be opened");
       return false;
   }
   QTextStream out(&f);
   QString oneRow;
   for(int i=0;i<data.size();i++){
       for(int j=0;j<data.at(i).size();j++){
           oneRow.append(data.at(i).at(j));
           oneRow.append(",");
       }
       out<<oneRow<<endl;
       oneRow.clear();
   }
}
bool tree::InsertData(QMap<QString,QString> row){
    QFile f("D:\\dbms-master\\FILE\\database\\"+databasename+"\\data\\"+tableName+".txt");
   if(!f.open(QIODevice::ReadWrite | QIODevice::Append)){
       throw QString("table"+tableName+"The data file could not be opened");
       return false;
   }
   QString oneRow;
   QTextStream out(&f);
   for(int i=0;i<head.size();i++){
       if(row.contains(head[i].get_name())){
           oneRow.append(row.find(head[i].get_name()).value());
       }
       oneRow.append(",");
   }
   out<<oneRow<<endl;
   f.close();
}

QVector<int> tree::FindAllData(QString column, QString judge, QString condtion){
    QVector<int> all;
    int order = getFieldIndex(column);
    if(order==-1){
        throw QString("Unknown field"+column);
    }
    qDebug()<<condtion;
    int order2 = getFieldIndex(condtion);
    qDebug()<<"order2:"<<order2;
    for(int j=0;j<data.size();j++){
        if(order2!=-1)
            condtion = data.value(j).value(order2);
//            qDebug()<<"111:"<<condtion;
        }
        if(judge==">="){
            if(data.at(j).at(order)>=condtion){
                all.append(j);
            }
        }
        else if(judge=="<="){
            if(data.at(j).at(order)<=condtion){
                all.append(j);
            }
        }
        else if(judge=="!="){
            if(data.at(j).at(order)!=condtion){
                all.append(j);
            }
        }
        else if(judge==">"){
            if(data.at(j).at(order)>condtion){
                all.append(j);
            }
        }
        else if(judge=="<"){
            if(data.at(j).at(order)<condtion){
                all.append(j);
            }
        }
        else if(judge=="="){
            if(data.at(j).at(order)==condtion){
                all.append(j);
            }
        }
    }
    return all;
}

bool tree::DeleteAllData(){
    //打开数据文件
    QFile f("D:\\dbms-master\\FILE\\database\\"+databasename+"\\data\\"+tableName+".txt");
   if(!f.open(QIODevice::WriteOnly|QIODevice::Text)){
       throw QString("table"+tableName+"The data file could not be opened");
       return false;
   }
   f.close();
   return true;
}
bool tree::UpdateOneData(int id, QString column, QString value){
    int order = getFieldIndex(column);
    if(order==-1){
        throw QString("Unknown field"+column);
        return false;
    }
    data[id][order]=value;
    return true;
}
tree tree::SelectData(QStringList columnList,QStringList groupList,QStringList orderList){
    tree t;
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
            if(getFieldIndex(columnList.at(i))==-1){
                throw QString("存在未知字段"+columnList.at(i));
            }
            row.set_name(columnList.at(i));
            row.set_dataType(getFieldType(columnList.at(i)));
            t.head.append(row);
        }
    }
    return t;
}
int tree::getFieldIndex(QString name){
    for(int i=0;i<head.size();i++){
        if(head[i].get_name()==name){
            return i;
        }
    }
    return -1;
}
QString tree::getFieldType(QString name){
    for(int i=0;i<head.size();i++){
        if(head[i].get_name()==name){
            return head[i].get_dataType();
        }
    }
    return "";
}
//得到两个表的笛卡尔积
tree tree::Cartesian(tree t){
    tree newT;
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
QString tree::getTableName(){
    return tableName;
}
QVector<int> tree::getWhere(QStringList judgeList){
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
                tem = FindAllData(column,judge,value);
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
