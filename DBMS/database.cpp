#include"database.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>

#include <direct.h>
#include <io.h>

#include <fstream>

using namespace std;

//database::database()
//{

//}
struct Tables {
    string name;
    string pathName;
    vector<string>colName;//列名称
    vector<string>type;
    vector<int>size;
    FILE* fp;
};

class myDBMS {
    vector<Tables*>tab;
    bool open;
public:
    string cmd;
    string prePath;//数据库的文件路径

    myDBMS() {
        cmd = "";
        prePath = "";
        open = false;
        //建库删库
        cout << "Please enter the command statement according to the following rules (commands are not case sensitive)" << endl;
        cout << "New database: create database" << endl;
        cout << "Drop database: drop database database name" << endl;
        cout << "Open database: database name" << endl;
        cout << "Close database: close database database name" << endl;
        cout << "Exit program: exit" << endl;
    }
    ~myDBMS() {
        for (int i = 0; i < tab.size(); i++) {
            if (tab[i]->fp != NULL)
                fclose(tab[i]->fp);
            delete tab[i];
        }
        tab.resize(0);
        cmd = "";
        prePath = "";
    }

    void transfer();//转为小写
    void openDataBase(string);//打开数据库
    void closeDataBase();//关闭数据库
    void myCreateDataBase(string); //建立数据库
    void myDropDataBase(string); //删除数据库


    int posIsNos(string);//辅助函数
};

void myDBMS::transfer() {
    for (int i = 0; i < cmd.size(); i++)
        cmd[i] = tolower(cmd[i]);
}

void myDBMS::openDataBase(string dataBaseName) {
    if (open) {
        cout << "Please close the currently open database first" << endl;
        return;
    }
    string pathName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\" + dataBaseName;
    if (0 != access(pathName.c_str(), 0))printf("The database does not exist");
    else {
        prePath = pathName + "\\";
        cout << "Database opened successfully" << endl;
        open = true;
    }
}

void myDBMS::closeDataBase() {//和析构函数相同
    for (int i = 0; i < tab.size(); i++) {
        if (tab[i]->fp != NULL)
            fclose(tab[i]->fp);
        delete tab[i];
    }
    tab.resize(0);
    cmd = "";
    prePath = "";
    open = false;
}

//D:\\test
void myDBMS::myCreateDataBase(string dataBaseName) {//建立数据库
    string pathName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS" + dataBaseName;
    if (0 != access(pathName.c_str(), 0)) {
        if (0 == mkdir(pathName.c_str()))//返回0表示创建成功,-1表示失败
            cout << "Created successfully" << endl;
        else
            cout << "Creation failed" << endl;
        return;
    }
    cout << "The database already exists" << endl;
}

void myDBMS::myDropDataBase(string dataBaseName) {//删除数据库
    string pathName = "D:\\test\\" + dataBaseName;
    if (0 == access(pathName.c_str(), 0)) {
        pathName = "rd " + pathName;
        if (0 == system(pathName.c_str()))
            cout << "Delete database" << dataBaseName << "success" << endl;
        else
            cout << "Delete database" << dataBaseName << "fail" << endl;
        return;
    }
    cout << "database" << dataBaseName << "not exist" << endl;
}

int main(void) {
    myDBMS db;
    while (cin >> db.cmd) {
        db.transfer();
        //cout << "db.cmd = " << db.cmd << endl;
        if (db.cmd == "exit")break;
        if (db.cmd == "create") {
            string name;
            cin >> db.cmd >> name;
            db.transfer();
            //cout << "db.cmd:" << db.cmd << " name:" << name << endl;
            if (db.cmd == "database")
                db.myCreateDataBase(name);
            else cout << "Error in command statement!" << endl;
        }
        else if (db.cmd == "drop") {
            string name;
            cin >> db.cmd >> name;
            db.transfer();
            if (db.cmd == "database")
                db.myDropDataBase(name);
            else cout << "Error in command statement!" << endl;
        }
        else if (db.cmd == "open") {
            string name;
            cin >> db.cmd >> name;
            db.openDataBase(name);
        }
        else if (db.cmd == "close") {
            string name;
            cin >> db.cmd >> name;
            db.transfer();
            if (db.cmd == "database")
                db.closeDataBase();
            else cout << "Error in command statement!" << endl;
        }
        else {
            string tmp;
            getline(cin, tmp);
            cout << "Input command error, please check!" << endl;
        }
    }
    return 0;
}
