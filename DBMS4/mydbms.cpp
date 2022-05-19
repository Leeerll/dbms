#include "mydbms.h"
#include "mainwindow.h"


void myDBMS::openDataBase(QString dataBaseName) {

    QString pathName = "D:\\dbms-master\\FILE\\" + dataBaseName;
    if (QDir(pathName).exists() == false)printf("The database does not exist");
    else {
        prePath = pathName + "\\";
         emit sendmessage("Database opened successfully");
        open = true;
    }
}

void myDBMS::closeDataBase(QString dataBaseName) {//和析构函数相同
    if (!open) {
        emit sendmessage("Please open the database first");
        return;
    }
    QString pathName = "D:\\dbms-master\\FILE\\database" + dataBaseName;
    if (QDir(pathName).exists() == false)printf("The database does not exist");
    else {
        for (int i = 0; i < tab.size(); i++) {
            if (tab[i]->fp != NULL)
                fclose(tab[i]->fp);
            delete tab[i];
        }
        tab.resize(0);
        cmd = "";
        prePath = "";
        emit sendmessage("Database closed successfully");
        open = false;
    }


}

void myDBMS::myCreateDataBase(QString dataBaseName) {//建立数据库
    QString pathName = "D:\\dbms-master\\FILE\\database\\" + dataBaseName;

    QFile file("D:\\dbms-master\\FILE\\database\\"+dataBaseName+".txt");//同步创建数据库预留表
    bool ok = file.open(QIODevice::ReadWrite);

    qDebug()<<pathName;
    if (QDir(pathName).exists() == false) {
        if (QDir().mkdir(pathName))//返回0表示创建成功,-1表示失败
            emit sendmessage("Created successfully");
        else
            emit sendmessage("Creation failed");
        return;
    }
    emit sendmessage("The database already exists");
}

void myDBMS::myDropDataBase(QString dataBaseName) {//删除数据库
    QString pathName = "D:\\dbms-master\\FILE\\database\\" + dataBaseName;
    if (QDir(pathName).exists() == true) {

        if (DelDir(pathName,dataBaseName) == true)
        {
            emit sendmessage("Database deleted successfully");
        }
        else
           emit sendmessage("Failed to delete database");
        //return;
    }
    else
    {
        emit sendmessage("The database does not exist");
    }

}

//删除文件夹
bool myDBMS::DelDir(const QString &path,QString dataBaseName)
{
    if (path.isEmpty()){
        return false;
    }
    QDir dir(path);
    if(!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
    foreach(QFileInfo file, fileList){ //遍历文件信息
        if (file.isFile()){ // 是文件，删除
            file.dir().remove(file.fileName());
        }else{ // 递归删除
            DelDir(file.absoluteFilePath(),dataBaseName);
        }
    }
    QFile filedatabase;
    filedatabase.setFileName("D:\\dbms-master\\FILE\\database\\" + dataBaseName+".txt");
    if(filedatabase.exists())
    {
        filedatabase.remove();
    }
    return dir.rmpath(dir.absolutePath()); // 删除文件夹
}
