//存储登录账户信息
#include "user.h"

user::user()
{

}
void user::set_Name(QString name){
    this->name = name;
}

void user::set_Password(QString password){
    this->password = password;
}

void user::set_DBA(QString _switch){
    this->DBA = _switch;
}

void user::set_RESOURCE(QString _switch){
    this->RESOURCE = _switch;
}

void user::set_CONNECT(QString _switch){
    this->CONNECT = _switch;
}

/******************************************/

QString user::get_Name(){
    return this->name;
}

QString user::get_Password(){
    return this->password;
}

QString user::get_DBA(){
    return this->DBA;
}

QString user::get_RESOURCE(){
    return this->RESOURCE;
}

QString user::get_CONNECT(){
    return this->CONNECT;
}


void user::refresh_user(){
    this->DBA = "FALSE";
    this->RESOURCE = "FALSE";
    this->CONNECT = "FALSE";
}






