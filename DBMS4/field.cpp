#include "field.h"

field::field()
{

}
/*记录表的内容*/
void field::set_tableName(QString tableName){
    this->tableName = tableName;
}

void field::set_name(QString name){
    this->name = name;
}

void field::set_dataType(QString dataType){
    this->dataType = dataType;
}

void field::set_PK(QString PK){
    this->PK = PK;
}
void field::set_unique(QString unique){
    this->unique = unique;
}

void field::set_notNull(QString notNull){
    this->notNull = notNull;
}

void field::set_defaultValue(QString defaultValue){
    this->defaultValue = defaultValue;
}

void field::set_checkUP(QString checkUP){
    this->checkUP = checkUP;
}

void field::set_checkDown(QString checkDown){
    this->checkDown = checkDown;
}

void field::set_FK_tableName(QString FK_tableName){
    this->FK_tableName = FK_tableName;
}

void field::set_deleteLimit(QString deleteLimit){
    this->deleteLimit = deleteLimit;
}

/***********************************************************************/


QString field::get_tableName(){
    return this->tableName;
}

QString field::get_name(){
    return this->name;
}

QString field::get_dataType(){
    return this->dataType;
}

QString field::get_PK(){
    return this->PK;
}
QString field::get_unique(){
    return this->unique;
}

QString field::get_notNull(){
    return this->notNull;
}

QString field::get_defaultValue(){
    return this->defaultValue;
}

QString field::get_checkUP(){
    return this->checkUP;
}

QString field::get_checkDown(){
    return this->checkDown;
}

QString field::get_FK_tableName(){
    return this->FK_tableName;
}

QString field::get_deleteLimit(){
    return this->deleteLimit;
}

/*字段属性*/

void field::refresh_field(){
    name = "FALSE";//名称
    dataType = "FALSE";//数据类型

    PK = "FALSE";//主键------表级
    unique = "FALSE";//唯一
    notNull = "FALSE";//非空
    defaultValue = "FALSE";//默认值

    checkUP = "FALSE";//check上限
    checkDown = "FALSE";//check下限

    FK_tableName = "FALSE";//外键引用表名---表级
    deleteLimit = "RESTRICT";//删除约束
}
