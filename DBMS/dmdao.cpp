#include <dmdao.h>

bool dmDao::insertDao(QString tableName,QString databasename,QStringList columnList, QStringList paramList){
    try{
        QVector<field> map;
        QMap<QString,QString> row;
        //读取表文件获取表字段
        Table t(tableName,databasename);
        map =  t.getHead();
        if(!map.isEmpty()){
            if(!columnList.isEmpty()){
                //遍历比较字段与列参数表
                bool find =false;
                for(int j=0;j<columnList.size();j++){
                    find=false;
                    for(int i=0;i<map.size();i++){
                        if(map[i].get_name()==columnList.at(j)){
                            row.insert(columnList.at(j),paramList.at(j));
                            find=true;
                        }
                    }
                    //判断是否出现未知字段
                    if(!find){
                        throw QString("An unknown field occurred");
                    }
                }
                return (t.InsertData(row));
            }
            //缺省：全参数
            else if(map.size()==paramList.size()){
                for(int i=0;i<map.size();i++){
                   row.insert(map[i].get_name(),paramList.at(i));
                }
                return (t.InsertData(row));
            }
            else{
                throw QString("Parameter mismatch");
            }
        }
        else{
            throw QString("The table field is empty");
        }
   }catch(QString exception){
       throw QString(exception);
   }
     return false;
}

bool dmDao::deleteDao(QString tableName,QString databasename,QStringList judgeList){
    try{
        Table t(tableName,databasename);
        //没有约束条件时，全部删除
        if(judgeList.isEmpty()){
            t.DeleteAllData();
        }
        else{
             QVector<int> where = t.getWhere(judgeList);
            QVector<QVector<QString>> newData;
            for(int i=0;i<t.getData().size();i++){
                if(!where.contains(i)){
                    newData.append(t.getData()[i]);
                }
            }
            t.setData(newData);
            t.UpdateAllData();
        }
        return true;
   }catch(QString exception){
       throw QString(exception);
   }
}
bool dmDao::updateDao(QString tableName,QString databasename, QString column1,QString value1,QStringList judgeList){
     try{
        Table t(tableName,databasename);
         //没有约束条件时，全部修改
         if(judgeList.isEmpty()){
             for(int i=0;i<t.getData().size();i++){
                 t.UpdateOneData(i,column1,value1);
             }
             t.UpdateAllData();
             return true;
         }
         else{
             QVector<int> where = t.getWhere(judgeList);
             for(int i=0;i<t.getData().size();i++){
                 if(where.contains(i)){
                     t.UpdateOneData(i,column1,value1);
                 }
             }
             t.UpdateAllData();
             return true;
         }
    }catch(QString exception){
        throw QString(exception);
    }
     return false;
}
Table dmDao::selectDao(QString databasename,QStringList tableList, QStringList columnList, QStringList judgeList,QStringList groupList,QStringList orderList,bool desc){
    try{
        Table all;//总表
        //暂不考虑子查询
        for(int i=0;i<tableList.size();i++){
            //qDebug()<<tableList[i];
            Table temp(tableList[i],databasename);
            //qDebug()<<"tempsize"<<temp.getData()[0].size();
            all = all.Cartesian(temp);
            //qDebug()<<"size"<<all.getData()[0].size();
        }
        if(!judgeList.isEmpty()){
             QVector<int> where = all.getWhere(judgeList);
            //qDebug()<<"where"<<where.size();
            //只保留符合where条件的数据
            QVector<QVector<QString>> newData;
            for(int i=0;i<all.getData().size();i++){
                if(where.contains(i)){
                    newData.append(all.getData()[i]);
                    //qDebug()<<i;
                }
            }
            all.setData(newData);
        }
        return all.SelectData(columnList,groupList,orderList,desc);
    }catch(QString exception){
        throw QString(exception);
    }
    //return all.SelectData(columnList,groupList,orderList,desc);
}
