#include "login.h"
#include "mydbms.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include<QFile>
#include <QTextStream>

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);//密文输入
    mysystemDataBase();
    mysystemuser();

    //creat a server object
    ser = new QTcpServer(this);

    //set server object to listen client
    //set server's ip  to be the same as host
    //set server's port to be 8888
    ser->listen(QHostAddress::AnyIPv4,8888);

    connect(ser,&QTcpServer::newConnection,

            [=]()
           {
              //get cliet's sockfd
              cli = ser->nextPendingConnection();

              //get client's ip and port

              QString cli_ip = cli->peerAddress().toString();
              quint16 cli_port = cli->peerPort();
              QString temp = QString("[%1:%2 connect success]").arg(cli_ip).arg(cli_port);


              qDebug() << temp;
            }
            );

}

login::~login()
{
    delete ui;
}

//D:\\test
void login::mysystemDataBase() {//建立数据库
    QString pathName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\user\\data\\user.txt" ;
    if (QDir(pathName).exists() == false) {
        if (QDir().mkdir(pathName))//返回0表示创建成功,-1表示失败
            qDebug()<<"success";
        else
            qDebug()<<"error";
        return;
    }
    qDebug()<<"have that";
}

bool isFileExist()
{
    QString fullFileName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\user\\data\\user.txt";
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

void login::mysystemuser(){
    if(!isFileExist()){
        QFile file("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\user\\data\\user.txt");
            if(! file.open(QIODevice::Append|QIODevice::Text))  //append追加，不会覆盖之前的文件
            {
                QMessageBox::critical(this,"错误","无法打开文件。信息未保存！","确认");
                return;
            }

            QTextStream out(&file);//写入
            QString mes = "sys sys TRUE TRUE TRUE";
            QStringList a = mes.split(" ");
//            for (int j=0;j<a.count();j++) {
//                out<<a[j];
//                out<<",";
//                if((j+1)%5 == 0)
//                    out << '\n';
//            }
            out<<mes;
            file.close();
    }
    else
        qDebug()<<"have that filetxt";

}

void login::readtxt()
{
    QFile f("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\user\\data\\user.txt");
        if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"not found filetxt";
            return;
        }
        while(!f.atEnd()){
            QVector<QString> row;
            QByteArray line = f.readLine();
            QString str(line);
            //str = str.simplified();
            //str.remove(" ");
            QStringList list = str.split(" ");
            pathtxt.insert(list[0],list[1]);
//            for(int i=0;i<list.size();i++){
//                if(list[i]!="\n")
//                row.append(list.at(i));
//            }
        }
        f.close();
}

void login::on_pushButton_clicked()
{
    //获得用户和密码
    QString name=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QString p;
    readtxt();
    if (pathtxt.contains(name) ){
        qDebug()<<"have user";
        p = pathtxt[name];
        qDebug()<<pathtxt.find(name).value();
        qDebug()<<"password  "+pathtxt[name];
        if(password == p)
        {

            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            //在这里直接跳转
            pathtxt.clear();

            this->hide();
            MainWindow *dia=new MainWindow(this);
            dia->getUser(name);
            dia->setWindowTitle("DBMS");//为窗口添加图标与文本
            QIcon icon_tdatabase;
            icon_tdatabase.addFile("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\res\\mouse.png");
            dia->setWindowIcon(icon_tdatabase);

            dia->setAutoFillBackground(true);
            QPalette palette;
            QPixmap pixmap("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\res\\mouse.png");
            palette.setBrush(QPalette::Window, QBrush(pixmap));
            dia->setPalette(palette);

            dia->show();
            connect(dia,SIGNAL(mysignal()),this,SLOT(my_show_slot())); //收到第二个窗口关闭信号显示第一窗口
        }
        else {
            QMessageBox::warning(this,"警告!","用户名或密码错误",QMessageBox::Yes);
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    }
    else{
        QMessageBox::warning(this,"警告!","用户名或密码错误",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    }

}

void login::my_show_slot()
{
    this->show();
}
