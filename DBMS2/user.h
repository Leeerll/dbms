#ifndef USER_H
#define USER_H
#include <QMainWindow>



class user
{
public:
    user();

    void set_Name(QString);
    void set_Password(QString);
    void set_DBA(QString);
    void set_RESOURCE(QString);
    void set_CONNECT(QString);

    QString get_Name();
    QString get_Password();
    QString get_DBA();
    QString get_RESOURCE();
    QString get_CONNECT();

    void refresh_user();//刷新此用户

private:
    QString name;
    QString password;
    QString DBA = "FALSE";
    QString RESOURCE = "FALSE";
    QString CONNECT = "FALSE";

};

#endif // USER_H
