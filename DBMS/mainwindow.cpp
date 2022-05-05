#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    db = new myDBMS();
    ui->setupUi(this);
    connect(db,SIGNAL(sendmessage(QString)),this,SLOT(message(QString)));
    connect(db,SIGNAL(sendmessage(QString)),this,SLOT(message(QString)));
    png();
    this->read_userField();//读入用户
    this->ui->tadd->setDisabled(true);
    this->ui->tcorrect->setDisabled(true);
    this->ui->tdelete->setDisabled(true);
    this->ui->twrong->setDisabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
     ui->textEdit->setText("");
}

//关闭时询问是否退出
void MainWindow::closeEvent(QCloseEvent *event){
    //窗口关闭时询问是否退出
       QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确定要退出本系统吗？",
                          QMessageBox::Yes|QMessageBox::No);
        if (result==QMessageBox::Yes)
            event->accept();
        else
            event->ignore();
}

//加载图片素材
void MainWindow::png()
{
    QIcon icon_tadd;
    icon_tadd.addFile(tr("DBMS/res/add.png"));
    ui->tadd->setIcon(icon_tadd);

    QIcon icon_tdelete;
    icon_tdelete.addFile(tr("DBMS/res/delete.png"));
    ui->tdelete->setIcon(icon_tdelete);

    QIcon icon_tcorrect;
    icon_tcorrect.addFile(tr("DBMS/res/correct.png"));
    ui->tcorrect->setIcon(icon_tcorrect);

    QIcon icon_twrong;
    icon_twrong.addFile(tr("DBMS/res/wrong.png"));
    ui->twrong->setIcon(icon_twrong);

    QIcon icon_trefresh;
    icon_trefresh.addFile(tr("DBMS/res/refresh.png"));
    ui->trefresh->setIcon(icon_trefresh);
}

bool MainWindow::prase(){




    int i = 0;
    QVector<user>::iterator iter; //迭代器,找到对应的用户
    for(iter=allUsers.begin();iter!=allUsers.end();iter++){
        if(iter->get_Name() == this->nowUser.get_Name()){
            break;
        }
        i++;
    }

    if(allUsers[i].get_CONNECT() == "FALSE" && allUsers[i].get_DBA() == "FALSE" && allUsers[i].get_DBA() == "FALSE"){
        this->ui->textEdit->append("YOU HAVE NONE POWER!");
        this->ui->pushButton->setDisabled(true);
        return false;
    }
    QString sqls=ui->textEdit->toPlainText();
    QStringList sqlList = sqls.split(";");
    for(int i = 0;i<sqlList.size();i++){
        QString sql = sqlList[i];
        sql = sql.simplified();
        sql = sql.toLower();
        QStringList list = sql.split(" ");
        if(list.size()<3){
            return false;
        }
        if(list[0]=="insert"||list[i]=="delete"||list[0]=="update"||list[0]=="select"){
            if(!dataname.isEmpty()) return dataParse(sql);
            ui->textEdit->setText("请先打开数据库");
            return false;
        }

        else if(list[0]=="create"||list[0]=="drop")
        {

           if(list[1]=="database"){
                if(allUsers[i].get_DBA() == "FALSE"){
                    this->ui->textEdit->append("YOU HAVE NO POWER!");
                    return false;
                }
                return dbtest(sql);

            }
            else if(list[1]=="user"){
                 if(!dataname.isEmpty()){
                     if(allUsers[i].get_DBA() == "FALSE"){
                         this->ui->textEdit->append("YOU HAVE NO POWER!");
                         return false;
                     }
                     return push_user(sql);
                 }
                 ui->textEdit->setText("请先打开数据库");
                 return false;

            }
            else if(list[1]=="table"||list[1]=="index"){
                if(!dataname.isEmpty()){
                    if(allUsers[i].get_CONNECT() == "FALSE"){
                        this->ui->textEdit->append("YOU HAVE NO POWER!");
                        return false;
                    }
                    return table_prase(sql);
                }
                ui->textEdit->setText("请先打开数据库");
                return false;
            }

        }

        else if(list[0] == "alter" || list[0] == "revoke" || list[0] == "grand"){
            return push_user(sql);
        }

        else if(list[0] == "open")
        {

            return dbtest(sql);
        }
        else{
            ui->textEdit->append("不符合语法规范！");
        }

    }
    return false;
}

//判断语法是否错误
bool MainWindow::dataParse(QString sql){
        //QString::trimmed() 移除字符串两端空白符
        //QString::simplified() 移除字符串两端空白符，使用单个空格字符代替字符串中出现的空白字符
        //remove(QRegExp("\\s)) 移除所有空白字符

        sql = sql.simplified();
        if(sql.isEmpty())
        {
            return false;
        }
        //全部转换为小写
        sql = sql.toLower();
        sqlList = sql.split(" ",QString::SkipEmptyParts);
        QString tem = sqlList[0];
        try{
            if(tem=="insert"){
                if(!Insert(dataname,sql)){
                    ui->textEdit->append("出现语法错误");
                }
                else{
                    ui->textEdit->append("插入成功");
                }
            }
            else if(tem=="delete"){
                if(!Delete(dataname,sql)){
                    ui->textEdit->append("出现语法错误");
                }
                else{
                    ui->textEdit->append("删除成功");
                }
            }
            else if(tem=="update"){
                if(!Update(dataname,sql)){
                    ui->textEdit->append("出现语法错误");
                }
                else{
                    ui->textEdit->append("更新成功");
                }
            }
            else if(tem=="select"){
                if(!Select(dataname,sql)){
                    ui->textEdit->append("出现语法错误");
                }
                else{
                    ui->textEdit->append("查询成功");
                }
            }
            else
            {
                ui->textEdit->append("语句错误");
            }
        }catch(QString exception){
            ui->textEdit->append(exception);
        }
    return true;
}

//插入
bool MainWindow::Insert(QString database,QString sql){
    try{
           QRegularExpression re("^insert\\sinto\\s([A-Za-z_]+)\\s?\\(((?:[A-Za-z_]+,)*[A-Za-z_]+)\\)\\svalues\\s?\\(((?:.*,)*.*)\\)");
           QRegularExpressionMatch match=re.match(sql);
           QString tableName;
           QString column;
           QString param;
           QStringList columnList;
           QStringList paramList;
           database=dataname;

           //有表参数
           if(match.hasMatch())
           {
               tableName = match.captured(1);

               if(!checkPower(tableName)){
                   throw QString("YOU HAVE NO POWER!");
               }
               column = match.captured(2);
               param = match.captured(3);
               //qDebug()<<param;
               columnList = column.split(",");
               paramList = param.split(",");
//               if(columnList.length()==paramList.length()){
                   return dao.insertDao(tableName,dataname,columnList,paramList);
//           }
           }
           //无表参数
           else{
               QRegularExpression reg("^insert\\sinto\\s([A-Za-z_]+)\\svalues\\s?\\(((?:.*,)*.*)\\)");
               match=reg.match(sql);
               if(match.hasMatch())
               {
                   tableName = match.captured(1);
                   if(!checkPower(tableName)){
                       throw QString("YOU HAVE NO POWER!");
                   }
                   param = match.captured(2);
                   paramList = param.split(",");
                   return dao.insertDao(tableName,dataname,columnList,paramList);

               }
               else{
                   throw QString("Does not conform to the grammar standard");
               }
           }


      }catch(QString exception){
          throw QString(exception);
      }
       return false;
}

//删除
bool MainWindow::Delete(QString database,QString sql){
    try{
           QString tableName;
           QStringList judgeList;
           QString judge;

           database=dataname;

           if(!sql.contains("where")){
               QRegularExpression re("^delete\\sfrom\\s(\\w+)");
               QRegularExpressionMatch match=re.match(sql);
               if(match.hasMatch())
               {
                   tableName = match.captured(1);
                   if(!checkPower(tableName)){
                       throw QString("YOU HAVE NO POWER!");
                   }
                   return dao.deleteDao(tableName,dataname,judgeList);
               }
               else{
                   throw QString("Does not conform to the grammar standard");
               }
           }
           else{
               QRegularExpression re("^delete\\sfrom\\s(\\w+)\\swhere\\s((?:[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+\\s(?:and|or)\\s)*[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+)");
               QRegularExpressionMatch match=re.match(sql);
               if(match.hasMatch())
               {
                   tableName = match.captured(1);
                   if(!checkPower(tableName)){
                       throw QString("YOU HAVE NO POWER!");
                   }
                   judge=match.captured(2);
                   judgeList = judge.split(" or ");
                   return dao.deleteDao(tableName,dataname,judgeList);
               }
               else{
                   throw QString("Does not conform to the grammar standard");
               }
           }
           }catch(QString exception){
               throw QString(exception);
           }

       return false;
}

//更新
bool MainWindow::Update(QString database,QString sql){
    try{
          QString tableName;
          QStringList judgeList;
          QString column;
          QString value;
          QString judge;

          database=dataname;

          if(!sql.contains("where")){
              QRegularExpression re("^update\\s(\\w+)\\sset\\s(\\w+)\\s?=\\s?(\\w+)");
              QRegularExpressionMatch match=re.match(sql);
              if(match.hasMatch())
              {
                  tableName = match.captured(1);
                  if(!checkPower(tableName)){
                      throw QString("YOU HAVE NO POWER!");
                  }
                  column = match.captured(2);
                  value = match.captured(3);
                  return dao.updateDao(tableName,dataname,column,value,judgeList);
              }
              else{
                  throw QString("Does not conform to the grammar standard");
              }
          }
          else{
              QRegularExpression re("^update\\s(\\w+)\\sset\\s(\\w+)\\s?=\\s?(\\w+)\\swhere\\s((?:[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+\\s(?:and|or)\\s)*[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+)");
              QRegularExpressionMatch match=re.match(sql);
              if(match.hasMatch())
              {
                  tableName = match.captured(1);
                  if(!checkPower(tableName)){
                      throw QString("YOU HAVE NO POWER!");
                  }
                  column = match.captured(2);
                  value = match.captured(3);
                  judge=match.captured(4);
                  judgeList = judge.split(" or ");
                  return dao.updateDao(tableName,dataname,column,value,judgeList);
              }
              else{
                  throw QString("Does not conform to the grammar standard");
              }
          }
          }catch(QString exception){
              throw QString(exception);
          }

      return false;
}

//查询
bool MainWindow::Select(QString database,QString sql){
    try{
            Table t;
            QString table;
            QString column;
            QString judge;
            QString group;
            QString order;

            database=dataname;

            //QString having;
            bool desc=true;
            QStringList columnList;//SELECT ...
            QStringList tableList;//FROM ...
            QStringList judgeList;//WHERE
            QStringList groupList;//GROUP BY (...,)...
            QStringList orderList;//ORDER BY (...,)... (ASC)
            QRegularExpression re("^select\\s((?:[\\w\\.]+,)*[\\w\\.]+|\\*)\\sfrom\\s((?:\\w+,)*\\w+)"
                                  "(?:\\swhere\\s((?:[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+"
                                  "\\s(?:and|or)\\s)*[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+))?"
                                  "(?:\\sgroup\\sby\\s((?:[\\w\\.]+,)*[\\w\\.]+))?(?:\\sorder\\sby\\s((?:[\\w\\.]+,)*[\\w\\.]+)\\s?(?:asc|desc)?)?$");
            QRegularExpressionMatch match=re.match(sql);
            if(match.hasMatch()){
                if(sql.contains("where")){
                    QRegularExpression re("\\swhere\\s((?:[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+\\s(?:and|or)\\s)*[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+)");
                    QRegularExpressionMatch match=re.match(sql);
                    if(match.hasMatch())
                    {
                        judge = match.captured(1);
                        judgeList = judge.split(" or ");
                    }
                }
               if(sql.contains("group by")){
                   QRegularExpression re("\\sgroup\\sby\\s((?:[\\w\\.]+,)*[\\w\\.]+)");
                   QRegularExpressionMatch match=re.match(sql);
                   if(match.hasMatch())
                   {
                       group = match.captured(1);
                       groupList = group.split(",");
                   }
               }
               if(sql.contains("order by")){
                   QRegularExpression re("\\sorder\\sby\\s((?:[\\w\\.]+,)*[\\w\\.]+)\\s?(?:asc|desc)?");
                   QRegularExpressionMatch match=re.match(sql);
                   if(match.hasMatch())
                   {
                       if(match.captured(0).contains("asc")){
                           desc=false;
                       }
                       order = match.captured(1);
                       orderList = order.split(",");
                   }
               }
                QRegularExpression re("^select\\s((?:[\\w\\.]+,)*[\\w\\.]+|\\*)\\sfrom\\s((?:\\w+,)*\\w+)");
                QRegularExpressionMatch match=re.match(sql);
                if(match.hasMatch())
                {
                    column = match.captured(1);
                    table = match.captured(2);
                    tableList = table.split(",");
                    columnList = column.split(",");
                    t = dao.selectDao(dataname,tableList,columnList,judgeList,groupList,orderList,desc);
                     qDebug()<<"asc:";
                    //将表输出
                     ui->showWidget->clear();//清空已存在的表
                     ui->showWidget->setColumnCount(t.getHead().size());//根据表结构设置列数
                     ui->showWidget->setRowCount(t.getData().size());//根据数据设置行数

                          for(int i=0;i<t.getData().size();i++)//创建视图
                          {
                              for(int j=0;j<t.getHead().size();j++)
                              {
                                  ui->showWidget->setHorizontalHeaderItem(j,new QTableWidgetItem(t.getHead()[j].get_name()));//设置表头

                                  if(t.getData()[i][j]==NULL)//判断表中的数据是否存在，若不存在补充null
                                  {
                                      ui->showWidget->setItem(i,j,new QTableWidgetItem(""));//读取内容
                                  }
                                  else//将表中读出的数据输入到表中相应位置
                                  {
                                      ui->showWidget->setItem(i,j,new QTableWidgetItem(t.getData()[i][j]));//读取内容

                                  }
                              }
                          }
//                    QString row;
//                    for(int i=0;i<t.getHead().size();i++){
//                        row.append(t.getHead()[i].get_name());
//                        row.append(",");
//                    }
//                    ui->textEdit->append(row);
//                    row.clear();
//                    qDebug()<<t.getData().size();
//                    for(int i=0;i<t.getData().size();i++){
//                        for(int j=0;j<t.getData()[i].size();j++){
//                            row.append(t.getData()[i][j]);
//                            row.append(",");
//                        }
//                       ui->textEdit->append(row);
//                       row.clear();
//                    }
                    return true;
                }
                else{
                    throw QString("Does not conform to the grammar standard");
                }
            }
            else{
                throw QString("Does not conform to the grammar standard");
            }
            }catch(QString exception){
                throw QString(exception);
            }
        return false;
}

//打开xx
void MainWindow::on_open_triggered()
{
     QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\data",tr("txt (*.txt)"));//打开文件
}

//创建表
void MainWindow::on_addtable_triggered()
{
    QFile file("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table"+tableName+".txt");
    bool ok = file.open(QIODevice::ReadWrite);
}

//获取表
void MainWindow::on_findtable_triggered()
{
    QDir dir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\table");//将目标文件夹下所有文件获取并输出
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" <<"*.txt";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    QString listname = files.join("\n");
    ui->textEdit->setText(listname);
    ui->treeWidget->clear();
    ui->treeWidget->windowFilePath();
    ui->treeWidget->setWindowIconText(listname);

}

//撤销
void MainWindow::on_backbutton_clicked()
{
    QFile f("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\cache\\cache.txt");//从缓存文件中获取之前的语句内容并还原
    f.open(QIODevice::ReadOnly);
    QTextStream t(&f);
    QString text = t.readAll();
    ui->textEdit->setPlainText(text);
    f.close();
}

//执行
void MainWindow::on_pushButton_clicked()
{
    QFile f("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\cache\\cache.txt");//将当前输入框内容缓存备份
    f.open(QFile::WriteOnly|QFile::Truncate);
    f.close();
    QString text = ui->textEdit->toPlainText();
    f.open(QFile::WriteOnly|QFile::Truncate);
    QTextStream out(&f);
    out<<text<<endl;
    f.close();
    prase();
//    if(!prase()){
//        ui->textEdit->append("不符合语法规范！");
//    }
//    dbtest();
//    if(!dataname.isEmpty())
//    {
//        push_user();//检验SQL语句
//    }
//    else
//    {
//        ui->textEdit->clear();
//        ui->textEdit->setText("请先打开数据库！");
//    }
}

//清除
void MainWindow::on_clearbutton_clicked()
{

    QFile f("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\cache\\cache.txt");//将当前输入框内容缓存备份
    f.open(QFile::WriteOnly|QFile::Truncate);
    f.close();
    QString text = ui->textEdit->toPlainText();
    f.open(QFile::WriteOnly|QFile::Truncate);
    QTextStream out(&f);
    out<<text<<endl;
    f.close();

    ui->textEdit->clear();//清空文本
}

//打开表
void MainWindow::on_readtable(QString filename,QString databasename)
{
    tree t(filename,databasename);

    ui->tableWidget->clear();//清空已存在的表
    ui->tableWidget->setColumnCount(t.getHead().size());//根据表结构设置列数
    ui->tableWidget->setRowCount(t.getData().size());//根据数据设置行数

//    ui->tableWidget->horizontalHeader()->setVisible(false);// 隐藏表头
//    ui->tableWidget->verticalHeader()->setVisible(false);

         for(int i=0;i<t.getData().size();i++)//创建视图
         {
             for(int j=0;j<t.getHead().size();j++)
             {
                 ui->tableWidget->setHorizontalHeaderItem(j,new QTableWidgetItem(t.getHead()[j].get_name()));//设置表头

                 if(t.getData()[i][j]==NULL)//判断表中的数据是否存在，若不存在补充null
                 {
                     ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));//读取内容
                 }
                 else//将表中读出的数据输入到表中相应位置
                 {
                     ui->tableWidget->setItem(i,j,new QTableWidgetItem(t.getData()[i][j]));//读取内容

                 }
             }
         }
}

//打开数据库
void MainWindow::on_readdb_triggered()
{
    ui->treeWidget->clear();//清空树

    ui->treeWidget->setColumnCount(1);//设置树冠
    QStringList header;
    header<<QString("DB List");//不能使用中文
    ui->treeWidget->setHeaderLabels(header);

    QDir dirdbs("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\database");//获取数据库
    QStringList dbsfiles;
    dbsfiles << "*.jpg" << "*.png" <<"*.txt";
    QStringList dbs = dirdbs.entryList(dbsfiles, QDir::Files|QDir::Readable, QDir::Name);
    QStringList toplevel;//一级节点 数据库
    for(int i=0;i<dbs.size();i++)
    {;
        QStringList dbsname = dbs[i].split(".txt");
        toplevel<<dbsname;
        QTreeWidgetItem *top = new QTreeWidgetItem(ui->treeWidget,toplevel);
        toplevel.clear();

        QDir dir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dbsname[0]+"\\table");//获取对应数据库的表
        QStringList nameFilters;
        nameFilters << "*.jpg" << "*.png" <<"*.txt";
        QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
        QStringList seclevel;//二级节点 表
        for(int j=0;j<files.size();j++)
        {
            QStringList tablename = files[j].split(".txt");//增加对应数据库前缀
            QString cache;
            cache.append(dbsname[0]);
            cache.append(".");
            cache.append(tablename[0]);
            seclevel<<cache;//读入文件*1
            QTreeWidgetItem *childitem = new QTreeWidgetItem(top,seclevel);
            top->addChild(childitem);
            seclevel.clear();//清空队列
            QFile file("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\table\\"+cache+".txt");
            bool ok = file.open(QIODevice::ReadWrite);//
            file.close();
        }
    }
}

//点击二级节点后的响应事件
void MainWindow::on_treeWidget_itemSelectionChanged()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    QDir dir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\table");//获取表
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" <<"*.txt";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    QStringList seclevel;//二级节点 表

    if(!dataname.isEmpty())
    {
        if(item->text(0).contains("."))
        {

            QStringList name = item->text(0).split(".");//将二级节点名拆分成数据库名和表名
            tree t(name[1],name[0]);//名字1是表名，名字2是数据库名
            qDebug()<<name[1];
            if(!checkPower(name[1])){
                this->ui->tadd->setDisabled(true);
                this->ui->tcorrect->setDisabled(true);
                this->ui->tdelete->setDisabled(true);
                this->ui->twrong->setDisabled(true);

            }
            else{
                this->ui->tadd->setDisabled(false);
                this->ui->tcorrect->setDisabled(false);
                this->ui->tdelete->setDisabled(false);
                this->ui->twrong->setDisabled(false);
            }
            if(t.getHead().size()!=NULL)//检测表是否为空
            {
                if(t.getData().size()!=NULL)
                {
                    for(int j=0;j<files.size();j++)
                    {
                        QStringList tablename = files[j].split(".txt");
                        seclevel<<tablename;//读入文件数量
                        if(item->text(0)==seclevel[0])//检测表是否存在
                        {
                            namefile=name[1];
                            namedatabase=name[0];
                            on_readtable(name[1],name[0]);
                        }
                        seclevel.clear();//清空队列
                    }
                }
                else
                {
                    for(int j=0;j<files.size();j++)
                    {
                        QStringList tablename = files[j].split(".txt");
                        seclevel<<tablename;//读入文件数量
                        if(item->text(0)==seclevel[0])//检测表是否存在
                        {
                            namefile=name[1];
                            namedatabase=name[0];
                            on_readtable(name[1],name[0]);
                        }
                        seclevel.clear();//清空队列
                    }
                    ui->tableWidget->setRowCount(1);
                }

            }
            else//如果是空表，输出
            {
                ui->tableWidget->clear();
                ui->tableWidget->setColumnCount(1);
                ui->tableWidget->setRowCount(1);
                ui->tableWidget->setItem(0,0,new QTableWidgetItem("null_table"));
            }
        }
    }
    else
    {
        ui->textEdit->setText("请先打开数据库");
    }


}

//预读字段表内字段
void MainWindow::read_tableField(QString tableName){
    QString fileName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table\\" + tableName;
    QFile table(fileName);
    if(!table.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        this->ui->textEdit->setText("CAN'T OPEN THE FILE!");//lky
        return;

    }
    else{
        while(!table.atEnd()){//筛选属性
            QByteArray line = table.readLine();
            QString str(line);
            str = str.simplified();
            QStringList strList = str.split(" ");


            field a_field;
            a_field.set_tableName(this->thisField.get_tableName());
            a_field.set_name(strList[0]);
            a_field.set_dataType(strList[1]);
            a_field.set_PK(strList[2]);
            a_field.set_unique(strList[3]);
            a_field.set_notNull(strList[4]);
            a_field.set_defaultValue(strList[5]);
            a_field.set_checkUP(strList[6]);
            a_field.set_checkDown(strList[7]);
            a_field.set_FK_tableName(strList[8]);
            a_field.set_deleteLimit(strList[9]);


            this->allFields.append(a_field);


        }

        table.close();
        return;
    }
}

//用于清除字段文件中的内容并写入allFields
void MainWindow::update_field_file(QString tableName){
    int i = 0;
    QString fileName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table\\" + tableName;
    QFile table(fileName);
    table.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&table);
    stream.seek(table.size());
    stream << "";
    table.close();


    table.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream stream1(&table);
    stream1.seek(table.size());
    QVector<field>::iterator iter; //迭代器
    for(iter=allFields.begin();iter!=allFields.end();iter++){
        QString aline = iter->get_name() + " "
                        + iter->get_dataType() + " "
                        + iter->get_PK() + " "
                        + iter->get_unique() + " "
                        + iter->get_notNull() + " "
                        + iter->get_defaultValue() + " "
                        + iter->get_checkUP() + " "
                        + iter->get_checkDown() + " "
                        + iter->get_FK_tableName() + " "
                        + iter->get_deleteLimit();
        qDebug()<<aline;

        stream1 << aline;
        i++;
        if(i != allFields.count()){
            stream1 << endl;
        }
    }
    table.close();


}

//对字段文件执行插入行操作 ALTER TABLE student ADD cno VARCHAR(20)
QString MainWindow::insert_field(){

    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
    for(iter=allFields.begin();iter!=allFields.end();iter++){
       if(iter->get_name() == this->thisField.get_name()){

           this->ui->textEdit->setText("THE ATTRIBUTE NAME IS ALREADY IN USE");
           return "THE ATTRIBUTE NAME IS ALREADY IN USE";
       }
    }

    this->allFields.append(this->thisField);
    this->update_field_file(this->thisField.get_tableName());
    this->ui->textEdit->append("INSERT SUCCESSFULLY!");
    return "INSERT SUCCESSFULLY!";
}

//对字段文件执行删除行操作ALTER TABLE student DROP COLUMN cno
QString MainWindow::drop_field(){

    int i = 0;
    QVector<field>::iterator iter; //迭代器,检查有无该属性
    for(iter=allFields.begin();iter!=allFields.end();iter++){
       if(iter->get_name() == this->thisField.get_name()){
           this->allFields.remove(i);
           this->update_field_file(this->thisField.get_tableName());
           this->ui->textEdit->append("DROP SUCCESSFULLY!");
           return "DROP SUCCESSFULLY!";
       }
       i++;
    }

    this->ui->textEdit->append("CAN'T FIND IT!");
    return "DROP FAILED!";
}

/****************************************************************************/

//预读用户信息
void MainWindow::read_userField(){
    QString fileName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\user\\data\\user.txt";
    QFile table(fileName);

    if(!table.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        this->ui->textEdit->append("CAN'T OPEN THE FILE!");
        return;//lky

    }
    else{

        while(!table.atEnd()){//筛选属性
            QByteArray line = table.readLine();
            qDebug() <<line;
            QString str(line);
            str = str.simplified();
            QStringList strList = str.split(" ");

            user a_user;
            a_user.set_Name(strList[0]);
            a_user.set_Password(strList[1]);
            a_user.set_DBA(strList[2]);
            a_user.set_RESOURCE(strList[3]);
            a_user.set_CONNECT(strList[4]);

            this->allUsers.append(a_user);
        }
        table.close();
        return;
    }
}

//更新用户
void MainWindow::update_user_file(){
    int i =0;
    QString userName = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\user\\data\\user.txt";
    QFile file(userName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.seek(file.size());
    stream << "";
    file.close();


    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream stream1(&file);
    stream1.seek(file.size());
    QVector<user>::iterator iter; //迭代器
    for(iter=allUsers.begin();iter!=allUsers.end();iter++){
        QString aline = iter->get_Name() + " "
                        + iter->get_Password() + " "
                        + iter->get_DBA() + " "
                        + iter->get_RESOURCE() + " "
                        + iter->get_CONNECT();
        qDebug()<<aline;

        stream1 << aline;
        i++;
        if(i != allUsers.count()){
            stream1 << endl;
        }
    }
    file.close();


}

//添加新用户 CREATE USER xxx IDENTIFIED BY xxxx
QString MainWindow::insert_user(){
    QVector<user>::iterator iter; //迭代器,检查是否插入同名属性

    for(iter=allUsers.begin();iter!=allUsers.end();iter++){
       if(iter->get_Name() == this->thisUser.get_Name()){

           this->ui->textEdit->append("THE USER IS ALREADY IN USE");
           return "THE USER ALREADY IN USE";
       }
    }
    this->allUsers.append(this->thisUser);
    this->update_user_file();
    this->ui->textEdit->append("CREATE USER SUCCESSFULLY!");
    return "CREATE USER SUCCESSFULLY!";
}

//删除用户
QString MainWindow::drop_user(){
    int i = 0;
    QVector<user>::iterator iter; //迭代器,检查有无该属性
    for(iter=allUsers.begin();iter!=allUsers.end();iter++){
       if(iter->get_Name() == this->thisUser.get_Name()){
           this->allUsers.remove(i);
           this->update_user_file();
           this->ui->textEdit->append("DROP USER SUCCESSFULLY!");
           return "DROP USER SUCCESSFULLY!";
       }
       i++;
    }

    this->ui->textEdit->setText("CAN'T FIND IT!");
    return "DROP USER FAILED!";

}

//SQL语句执行
bool MainWindow::push_user(QString sql){


    this->thisField.refresh_field();//刷新对象
    this->thisUser.refresh_user();//刷新用户
    this->allFields.clear();//刷新字段容器
    this->allUsers.clear();//刷新用户容器

     //按空格切割sql语句

    sql = sql.simplified();

    QString firstSql = sql.toLower();//保存初始sql用于正则表达式处理

    sql = sql.replace(QRegExp("\\,"), " ");
    sql = sql.toLower();
    this->sqlList = sql.split(" ");
    qDebug() << sqlList.size();

    this->read_userField();//读入用户

    //确认该语句指向字段修改
    if(sqlList[0].toLower() == "alter" && sqlList[1].toLower() == "table"){

        this->thisField.set_tableName(sqlList[2] + ".txt");//确认关系名
        if(!checkPower(sqlList[2])){
            throw QString("YOU HAVE NO POWER!");
        }
        this->read_tableField(this->thisField.get_tableName());//读入容器

    }

    //CREATE USER 111 IDENTIFIED BY 111;创建用户
    else if(sqlList[0].toLower() == "create" && sqlList[1].toLower() == "user"
            && sqlList[3].toLower() == "identified" && sqlList[4].toLower() == "by" && sqlList.length() == 6){
        //this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[2]);
        this->thisUser.set_Password(sqlList[5]);
        insert_user();
        return true;
    }

    //DROP USER 111;删除用户
    else if(sqlList[0].toLower() == "drop" && sqlList[1].toLower() == "user" && sqlList.length() == 3){
        //this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[2]);
        drop_user();
        return true;
    }

    //GRAND CONNECT, RESOURCE, DBA TO yby;授权
    else if(sqlList[0] == "grand" && sqlList.length() >= 4){
        QRegularExpression rx1("^(grand)\\s(connect|dba|resource)\\s(to)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match1 = rx1.match(firstSql);
        QRegularExpression rx2("^(grand)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s(to)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match2 = rx2.match(firstSql);
        QRegularExpression rx3("^(grand)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s*\\,\\s*(connect|dba|resource)\\s(to)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match3 = rx3.match(firstSql);
        QRegularExpression rx8("^grand all on [A-Za-z0-9]+ to [A-Za-z0-9]+$");
        QRegularExpressionMatch match8 = rx8.match(firstSql);
        //if(match1.hasMatch()){

        //this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        int i = 0;
        QVector<user>::iterator iter; //迭代器,找到对应的用户
        for(iter=allUsers.begin();iter!=allUsers.end();iter++){
            if(iter->get_Name() == this->thisUser.get_Name()){
                break;
            }
            i++;
            if(i == this->allUsers.count()){
                this->ui->textEdit->append("CAN'T FIND USER!");
                return false;
            }
        }

        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        if(match1.hasMatch()){
                if(sqlList[1] == "dba"){
                    allUsers[i].set_DBA("TRUE");
                    update_user_file();
                    this->ui->textEdit->append("GRAND succeeded!");
                    return true;
                }
                else if(sqlList[1] == "connect"){
                    allUsers[i].set_CONNECT("TRUE");
                    update_user_file();
                    this->ui->textEdit->append("GRAND succeeded!");
                    return true;
                }
                else if(sqlList[1] == "resource"){
                    allUsers[i].set_RESOURCE("TRUE");
                    update_user_file();
                    this->ui->textEdit->append("GRAND succeeded!");
                    return true;
                }
                else{
                    this->ui->textEdit->append("WRONG SQL STATEMENT!");
                    return false;
                }
            }
        else if(match2.hasMatch()){
            if(sqlList[1] != "dba" && sqlList[2] != "connect"){
                allUsers[i].set_CONNECT("TRUE");
                allUsers[i].set_RESOURCE("TRUE");
                update_user_file();
                this->ui->textEdit->append("GRAND succeeded!");
                return true;
            }
            else if(sqlList[1] != "connect" && sqlList[2] != "connect"){
                allUsers[i].set_DBA("TRUE");
                allUsers[i].set_RESOURCE("TRUE");
                update_user_file();
                this->ui->textEdit->append("GRAND succeeded!");
                return true;
            }
            else if(sqlList[1] != "resource" && sqlList[2] != "resource"){
                allUsers[i].set_DBA("TRUE");
                allUsers[i].set_CONNECT("TRUE");
                update_user_file();
                this->ui->textEdit->append("GRAND succeeded!");
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }
        }
        else if(match3.hasMatch()){
            allUsers[i].set_CONNECT("TRUE");
            allUsers[i].set_RESOURCE("TRUE");
            allUsers[i].set_DBA("TRUE");
            update_user_file();
            this->ui->textEdit->append("GRAND succeeded!");
            return true;
        }

        //具体到表的权限GRAND;
        else if(match8.hasMatch()){
            QString filename = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission\\" +sqlList[3]+".txt";
            QFile usertable(filename);
            QStringList strList1;

            if(!usertable.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                this->ui->textEdit->append("CAN'T OPEN THE FILE!");
                return false;

            }
            else{
                while(!usertable.atEnd()){
                    QByteArray line = usertable.readLine();
                    QString str(line);
                    if(str == this->thisUser.get_Name()){
                        this->ui->textEdit->append("GRAND succeeded!");
                        return true;
                    }
                }
            }
            usertable.close();

            if(!usertable.open(QIODevice::ReadWrite | QIODevice::Append))
            {
                this->ui->textEdit->append("CAN'T OPEN THE FILE!");
                return false;

            }
            else{

                QTextStream stream1(&usertable);
                stream1.seek(usertable.size());
                stream1 << endl << this->thisUser.get_Name();
                }

                usertable.close();
                this->ui->textEdit->append("GRAND succeeded!");
                return true;
        }



        else{

            this->ui->textEdit->append("WRONG SQL STATEMENT!");
            return false;
        }

    }

    //REVOKE CONNECT, RESOURCE, DBA FROM xxx;删权
    else if(sqlList[0] == "revoke" && sqlList.length() >= 4){
        QRegularExpression rx1("^(revoke)\\s(connect|dba|resource)\\s(from)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match1 = rx1.match(firstSql);
        QRegularExpression rx2("^(revoke)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s(from)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match2 = rx2.match(firstSql);
        QRegularExpression rx3("^(revoke)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s*\\,\\s*(connect|dba|resource)\\s(from)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match3 = rx3.match(firstSql);
        QRegularExpression rx8("^revoke all on [A-Za-z0-9]+ from [A-Za-z0-9]+$");
        QRegularExpressionMatch match8 = rx8.match(firstSql);


        //this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        int i = 0;
        QVector<user>::iterator iter; //迭代器,找到对应的用户
        for(iter=allUsers.begin();iter!=allUsers.end();iter++){
            if(iter->get_Name() == this->thisUser.get_Name()){
                break;
            }
            i++;
            if(i == this->allUsers.count()){
                this->ui->textEdit->append("CAN'T FIND IT!");
                return false;
            }
        }

        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        if(match1.hasMatch()){
                if(sqlList[1] == "dba"){
                    allUsers[i].set_DBA("FALSE");
                    update_user_file();
                    this->ui->textEdit->append("REVOKE succeeded!");
                    return true;
                }
                else if(sqlList[1] == "connect"){
                    allUsers[i].set_CONNECT("FALSE");
                    update_user_file();
                    this->ui->textEdit->append("REVOKE succeeded!");
                    return true;
                }
                else if(sqlList[1] == "resource"){
                    allUsers[i].set_RESOURCE("FALSE");
                    update_user_file();
                    this->ui->textEdit->append("REVOKE succeeded!");
                    return true;
                }
                else{
                    this->ui->textEdit->append("WRONG SQL STATEMENT!");
                    return false;
                }
            }
        else if(match2.hasMatch()){
            if(sqlList[1] != "dba" && sqlList[2] != "connect"){
                allUsers[i].set_CONNECT("FALSE");
                allUsers[i].set_RESOURCE("FALSE");
                update_user_file();
                this->ui->textEdit->append("REVOKE succeeded!");
                return true;
            }
            else if(sqlList[1] != "connect" && sqlList[2] != "connect"){
                allUsers[i].set_DBA("FALSE");
                allUsers[i].set_RESOURCE("FALSE");
                update_user_file();
                this->ui->textEdit->append("REVOKE succeeded!");
                return true;
            }
            else if(sqlList[1] != "resource" && sqlList[2] != "resource"){
                allUsers[i].set_DBA("FALSE");
                allUsers[i].set_CONNECT("FALSE");
                update_user_file();
                this->ui->textEdit->append("REVOKE succeeded!");
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }
        }
        else if(match3.hasMatch()){
            allUsers[i].set_CONNECT("FALSE");
            allUsers[i].set_RESOURCE("FALSE");
            allUsers[i].set_DBA("FALSE");
            update_user_file();
            this->ui->textEdit->append("REVOKE succeeded!");
            return true;
        }

        //删除具体权限REVOKE ALL ON STUDENT FROM xxx;
        else if(match8.hasMatch()){
            QString filename = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission\\" +sqlList[3]+".txt";
            QFile usertable1(filename);
            QStringList strList1;

            if(!usertable1.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                this->ui->textEdit->append("CAN'T OPEN THE FILE!");
                return false;

            }
            else{
                while(!usertable1.atEnd()){

                    QByteArray line = usertable1.readLine();
                    QString str(line);
                    if(str != this->thisUser.get_Name()){
                        strList1 << str;

                    }

                }
            }
            usertable1.close();

            /********************************/

            usertable1.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream stream(&usertable1);
            stream.seek(usertable1.size());
            stream << "";
            usertable1.close();


            usertable1.open(QIODevice::WriteOnly|QIODevice::Append);
            QTextStream stream1(&usertable1);
            stream1.seek(usertable1.size());

            for(int i = 0;i<strList1.length();){
                QString aline = strList1[i];
                aline = aline.simplified();
                qDebug()<<aline;
                stream1 << aline;
                i++;
                if(i != strList1.length()){
                    stream1 << endl;
                }
            }
            usertable1.close();
            this->ui->textEdit->append("REVOKE succeeded!");
            return true;
        }

        else{
            this->ui->textEdit->append("WRONG SQL STATEMENT!");
            return false;
        }

    }
    else{
        this->ui->textEdit->append("WRONG SQL STATEMENT!");
       return false;
   }

/**************************************************************************************************/
    //确认该语句指向添加属性, 若为 add column 则长度必然大于等于七个单词
    //ALTER TABLE student ADD COLUMN cno VARCHAR(20) UNIQUE NOTNULL DEFAULT XXX;
    if(sqlList[3].toLower() == "add" && sqlList[4].toLower() == "column" && sqlList.length() >=7 ){

        this->thisField.set_tableName(sqlList[2] + ".txt");//确认表名

        //正则表达式判断数据类型书写正确性
        QRegularExpression rx4("(varchar|int)\\([0-9]*\\)");
        QRegularExpressionMatch match4 = rx4.match(firstSql);
        QRegularExpression rx5("(varchar|int)");
        QRegularExpressionMatch match5 = rx5.match(firstSql);

        if(!match4.hasMatch() && !match5.hasMatch()){
            this->ui->textEdit->append("WRONG SQL STATEMENT!");
            return false;
        }
        this->thisField.set_name(sqlList[5]);//确认属性名
        this->thisField.set_dataType(sqlList[6]);//确认属性数据类型
        //(varchar\([0-9]*\)|int\([0-9]*\))

        if(sqlList.length() == 7){
            insert_field();//插入
            return true;
        }

        else if(sqlList.length() == 8){
             qDebug() << "////////////////";
            if(sqlList[7].toLower() == "notnull"){//非空设置
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[7].toLower() == "unique"){//唯一设置

                this->thisField.set_unique("TRUE");
                insert_field();//插入
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }
        }

        else if(sqlList.length() == 9){
            if(sqlList[7].toLower() == "default"){//默认值设置
                this->thisField.set_defaultValue(sqlList[8]);
                insert_field();//插入
                return true;
            }
            else if(sqlList[7].toLower() == "unique" && sqlList[8].toLower() == "notnull"){
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[8].toLower() == "unique" && sqlList[7].toLower() == "notnull"){
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }
        }

        else if(sqlList.length() == 10){//既有非空又有默认值
            if(sqlList[7].toLower() == "default" && sqlList[9].toLower() == "notnull"){//默认值和非空设置
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[7].toLower() == "default" && sqlList[9].toLower() == "unique"){//默认值和唯一设置
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_unique("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[7].toLower() == "notnull" && sqlList[8].toLower() == "default"){//默认值和非空设置
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[7].toLower() == "unique" && sqlList[8].toLower() == "default"){//默认值和唯一设置
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_unique("TRUE");
                insert_field();//插入
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }
        }

        else if(sqlList.length() == 11){//三项全占
            if(sqlList[7].toLower() == "default" && sqlList[9].toLower() == "notnull" && sqlList[10].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[7].toLower() == "default" && sqlList[10].toLower() == "notnull" && sqlList[9].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[8].toLower() == "default" && sqlList[7].toLower() == "notnull" && sqlList[10].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[8].toLower() == "default" && sqlList[10].toLower() == "notnull" && sqlList[7].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[9].toLower() == "default" && sqlList[7].toLower() == "notnull" && sqlList[8].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[10]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else if(sqlList[9].toLower() == "default" && sqlList[8].toLower() == "notnull" && sqlList[7].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[10]);

                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }

        }
        else{
            this->ui->textEdit->append("WRONG SQL STATEMENT!");
            return false;
        }


    }


/**************************************************************************************************/
    //确认语句指向删除字段
    //ALTER TABLE student DROP COLUMN cno RESTRICT|CASCADE;
    else if(sqlList[3].toLower() == "drop" && sqlList[4].toLower() == "column" && sqlList.length() >=6){

        this->thisField.set_name(sqlList[5]);//确认属性名
        this->thisField.set_tableName(sqlList[2] + ".txt");//确认表名

        //若为 drop column 则长度必然大于等于六个单词，等于六为默认删除
        if(sqlList.length()<7){
            this->thisField.set_deleteLimit("RESTRICT");
            drop_field();//删除字段
            return true;
        }

        else if(sqlList.length() == 7){//确认删除类型

            if(sqlList[6].toLower() == "restrict" || sqlList[6].toLower() == "cascade"){
                this->thisField.set_deleteLimit(sqlList[6].toUpper());
                drop_field();//删除字段
                return true;
            }

            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }

        }

        else{
            this->ui->textEdit->append("WRONG SQL STATEMENT!");
            return  false;
        }

    }


/**************************************************************************************************/
    //修改字段的属性
    //ALTER TABLE student MODIFY COLUMN cno UNIQUE|DEFAULT XXX|NOTNULL|DATATYPE
    //ALTER TABLE student MODIFY COLUMN cno DEFAULT XXX
    //ALTER TABLE student MODIFY COLUMN sno INT(10) UNIQUE
    else if(sqlList[3].toLower() == "modify" && sqlList[4].toLower() == "column" && sqlList.length() >=7){
        this->thisField.set_name(sqlList[5]);//确认属性名
        this->thisField.set_tableName(sqlList[2] + ".txt");//确认表名
        //正则表达式判断数据类型书写正确性
        QRegularExpression rx6("(varchar|int)\\([0-9]*\\)");
        QRegularExpressionMatch match6 = rx6.match(firstSql);
        QRegularExpression rx7("(varchar|int)");
        QRegularExpressionMatch match7 = rx7.match(firstSql);

//        if(!match6.hasMatch() && !match7.hasMatch()){
//            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
//            return;
//        }

        int i = 0;
        QVector<field>::iterator iter; //迭代器,找到对应的字段
        for(iter=allFields.begin();iter!=allFields.end();iter++){
           if(iter->get_name() == this->thisField.get_name()){

               break;
           }
           i++;
           if(i == this->allFields.count()){
               this->ui->textEdit->append("CAN'T FIND IT!");
               return false;
           }
        }

        //单项修改
        if(sqlList.length() == 7){//修改数据类型

            if(match6.hasMatch() || match7.hasMatch()){
                allFields[i].set_dataType(sqlList[6].toUpper());

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if(sqlList[6].toLower() == "unique"){//修改唯一性
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if(sqlList[6].toLower() == "notnull"){//修改非空
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }

        }

        else if(sqlList.length() == 8){
            if(sqlList[6].toLower() == "notnull" && sqlList[7].toLower() == "unique"){//非空且唯一
                allFields[i].set_notNull("TRUE");
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if(sqlList[7].toLower() == "notnull" && sqlList[6].toLower() == "unique"){//非空且唯一
                allFields[i].set_notNull("TRUE");
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if((match6.hasMatch() || match7.hasMatch())
                    && sqlList[6].toLower() == "unique"){//数据类型和唯一
                allFields[i].set_dataType(sqlList[7].toUpper());
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if((match6.hasMatch() || match7.hasMatch())
                    && sqlList[7].toLower() == "unique"){//数据类型和唯一
                allFields[i].set_dataType(sqlList[6].toUpper());
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if(sqlList[7].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch())){//数据类型和非空
                allFields[i].set_notNull("TRUE");
                allFields[i].set_dataType(sqlList[6].toUpper());

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if(sqlList[6].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch())){//数据类型和非空
                allFields[i].set_notNull("TRUE");
                allFields[i].set_dataType(sqlList[7].toUpper());

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else if(sqlList[6].toLower() == "default"){//修改默认值
                allFields[i].set_defaultValue(sqlList[7]);
                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }
            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }
        }

        else if(sqlList.length() == 9){
            if(sqlList[6].toLower() == "default"){//默认值设置,且非空或唯一或数据类型
                allFields[i].set_defaultValue(sqlList[7]);

                if(sqlList[8].toLower() == "notnull"){//非空
                    allFields[i].set_notNull("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
                }

                else if(sqlList[8].toLower() == "unique"){//唯一
                    allFields[i].set_unique("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
                }

                else if(match6.hasMatch() || match7.hasMatch()){//数据类型
                    allFields[i].set_dataType(sqlList[8].toUpper());
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
                }
                else{
                    this->ui->textEdit->append("WRONG SQL STATEMENT!");
                    return false;
                }

            }

            else if(sqlList[7].toLower() == "default"){//默认值设置,且非空或唯一或数据类型
                allFields[i].set_defaultValue(sqlList[8]);

                if(sqlList[6].toLower() == "notnull"){//非空
                    allFields[i].set_notNull("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
                }

                else if(sqlList[6].toLower() == "unique"){//唯一
                    allFields[i].set_unique("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
                }

                else if(match6.hasMatch() || match7.hasMatch()){//数据类型
                    allFields[i].set_dataType(sqlList[6].toUpper());
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
                }
                else{
                    this->ui->textEdit->append("WRONG SQL STATEMENT!");
                    return false;
                }
            }

            else if(sqlList[6].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[8].toLower() == "unique"){//非空、数据类型、唯一
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[7].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }

            else if(sqlList[6].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[7].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[8].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }

            else if(sqlList[7].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[8].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[6].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }

            else if(sqlList[8].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[7].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[6].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }

            else if(sqlList[7].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[6].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[8].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }

            else if(sqlList[8].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[6].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[7].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit->append("Modification succeeded!");
                return true;
            }

            else{
                this->ui->textEdit->append("WRONG SQL STATEMENT!");
                return false;
            }
        }
        else{
            this->ui->textEdit->append("WRONG SQL STATEMENT!");
            return false;
        }
    }


/**************************************************************************************************/
    //添加CHECK约束
    //ALTER TABLE student ADD CHECK (sno>10)
    //ALTER TABLE student ADD CHECK (sno>10 AND sex<5)
    else if(sqlList[3].toLower() == "add" && sqlList[4].toLower() == "check" && sqlList.length() >= 6){

        sqlList[5] = sqlList[5].remove(QChar('('), Qt::CaseInsensitive);//括号清除
        sqlList[5] = sqlList[5].remove(QChar(')'), Qt::CaseInsensitive);//括号清除
        //sqlList[5] = sqlList[5].replace(QRegExp("\\)"), " ");

        if(sqlList[5].contains(">",Qt::CaseSensitive) == true) {
            int i = 0;
            QStringList a_check = sqlList[5].split(">");
            QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
            for(iter=allFields.begin();iter!=allFields.end();iter++){
               if(iter->get_name() == a_check[0]){
                    allFields[i].set_checkDown(a_check[1]);
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
               }
               i++;
            }

            if(sqlList.length() == 8){
                if(sqlList[7].contains(">",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkDown(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit->append("Modification succeeded!");
                            return true;
                       }
                       j++;
                    }

                }
                else if(sqlList[7].contains("<",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkUP(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit->append("Modification succeeded!");
                            return true;
                       }
                       j++;
                    }
                }
                else{
                    this->ui->textEdit->append("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
                    return false;
                }
            }
            this->ui->textEdit->append("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
            return false;
        }
        else if(sqlList[5].contains("<",Qt::CaseSensitive) == true){
            int i = 0;
            QStringList a_check = sqlList[5].split("<");
            QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
            for(iter=allFields.begin();iter!=allFields.end();iter++){
               if(iter->get_name() == a_check[0]){
                    allFields[i].set_checkUP(a_check[1]);
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit->append("Modification succeeded!");
                    return true;
               }
               i++;
            }
            if(sqlList.length() == 8){
                if(sqlList[7].contains(">",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkDown(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit->append("Modification succeeded!");
                            return true;
                       }
                       j++;
                    }

                }
                else if(sqlList[7].contains("<",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkUP(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit->append("Modification succeeded!");
                            return true;
                       }
                       j++;
                    }
                }
                else{
                    this->ui->textEdit->append("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
                    return false;
                }

            this->ui->textEdit->append("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
            return false;
            }
        }
        else{
            this->ui->textEdit->append("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
            return false;
        }

    }


/**************************************************************************************************/

    else{
        this->ui->textEdit->append("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
        return false;
    }

}

//刷新表
void MainWindow::on_trefresh_clicked()
{
    if(!namefile.isEmpty()&&!namedatabase.isEmpty())
    {
         on_readtable(namefile,namedatabase);
         on_readdb_triggered();
    }
}

//取消表操作
void MainWindow::on_twrong_clicked()
{
    if(!namefile.isEmpty()&&!namedatabase.isEmpty());
}

//添加新的行
void MainWindow::on_tadd_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

//删除选中行
void MainWindow::on_tdelete_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

//提交表操作
void MainWindow::on_tcorrect_clicked()
{
    QFile cache("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+namedatabase+"\\data\\"+namefile+".txt");//从缓存文件中获取之前的语句内容并还原
    cache.open(QIODevice::ReadOnly);
    QTextStream tcache(&cache);
    QString textcache = tcache.readAll();
    cache.close();

    QFile ff("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+namedatabase+"\\data\\"+namefile+".txt");
    ff.open(QFile::WriteOnly|QFile::Truncate);
    ff.close();

    QString work;
    QFile f("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+namedatabase+"\\data\\"+namefile+".txt");
    f.open(QIODevice::ReadWrite | QIODevice::Append);
    qDebug()<<"work1";
    QTextStream out(&f);
    qDebug()<<"work2";
    int x=ui->tableWidget->columnCount();
    int y=ui->tableWidget->rowCount();
    for(int i=0;i<y;i++)
    {
        for(int j=0;j<x;j++)
        {
            qDebug()<<"work4"<<i;
            if(ui->tableWidget->item(i,j)->text().isEmpty())
            {
                 ui->textEdit->append("表中不允许存在空值!");
                 return;
            }
            work=ui->tableWidget->item(i,j)->text();
            work.append(",");

            out<<work;
        }
        out<<"\n";
    }
    f.close();
    if(constraint(namefile))
    {
        QFile fcache("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+namedatabase+"\\data\\"+namefile+".txt");//清空
        fcache.open(QFile::WriteOnly|QFile::Truncate);
        fcache.close();
        QFile ffcache("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+namedatabase+"\\data\\"+namefile+".txt");//还原
        ffcache.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream out(&ffcache);
        qDebug()<<textcache;
        out<<textcache;
        ffcache.close();
    }
    else
    {
        ui->textEdit->append("UPDATE!");
    }


}

//完整性约束判断
bool MainWindow::constraint(QString tablename){

    qDebug()<<"123";

    Table t(tablename,dataname);

    bool target=false;//是否终止
    bool PK=false;//主键
    bool UNIQUE=false;
    bool NOTNULL=false;
    QStringList unique;//唯一性

    ui->textEdit->clear();
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
                ui->textEdit->append("表"+tablename+"主键不唯一！");
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
            ui->textEdit->append(t.getHead()[i].get_name()+"的唯一性未被满足！");
            UNIQUE=false;
        }
        if(NOTNULL)
        {
            ui->textEdit->append(t.getHead()[i].get_name()+"不满足非空性约束！");
            NOTNULL=false;
        }
        unique.clear();
    }

    if(target)//是否结束操作
    {      
        return true;
        throw QString("当前操作已终止！");
    }
    else
    {
        return false;
    }
}

//判断数据库操作语句是否正确
bool MainWindow::dbtest(QString sql)
{
    qDebug()<< "****dbtest*****";
//    db->cmd = ui->textEdit->toPlainText();
//    sql=db->cmd;
        sql = sql.toLower();
        qDebug()<<sql;
        squece = sql.split(" ");
        if (squece[0] == "exit"){
            ui->textEdit->clear();
        }
        //cout << "db.cmd = " << db.cmd << endl;

        if (squece[0] == "create") {
            QString name;
            name = squece[2];
            qDebug()<<name;

            //cout << "db.cmd:" << db.cmd << " name:" << name << endl;
            if (squece[1] == "database")
            {
                db->myCreateDataBase(name);

            }

            else {
                ui->textEdit->setText("WRONG SQUENCE");
                return false;
            }
        }
        else if (squece[0] == "drop") {
            QString name;
            name = squece[2];
            if (squece[1] == "database")
            {
                db->myDropDataBase(name);
            }

            else {
                ui->textEdit->setText("drop WRONG SQUENCE");
                return false;
            }
        }
        else if (squece[0] == "open") {
            qDebug()<< "**************";
            QString name;
            name = squece[2];
            dataname = name;

            bool find=false;
            QDir dir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\database");//获取表
            QStringList nameFilters;
            nameFilters << "*.jpg" << "*.png" <<"*.txt";
            QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

            for(int i=0;i<files.size();i++)
            {
                files[i].remove(".txt");
                if(dataname==files[i])
                {
                    find=true;
                }
            }

            if(find)
            {
                if(squece[1] == "database")
                {
                    db->openDataBase(name);

                }
                else {
                    ui->textEdit->setText("open WRONG SQUENCE");
                    return false;
                }
            }
            else
            {
                ui->textEdit->setText("未找到数据库");
                return false;
            }

        }
//        else if (squece[0] == "close") {
//            QString name;
//            name = squece[2];

//            if (squece[1] == "database")
//            {
//                db->closeDataBase(name);
//                dataname.clear();
//            }
//            else {
//                ui->textEdit->setText("close WRONG SQUENCE");
//                return false;
//            }
//        }
        return true;
}

void MainWindow::message(QString s){
    ui->textEdit->setText(s);
}

//create table student(sno varchar2(9) PK,sname varchar2(12) notnull,age int unique);
bool MainWindow::table_prase(QString str){
    if(str.startsWith("create table")){
        if(createTable(str)){
            return true;
        }
    }
    else if(str.startsWith("drop table")){
        if(dropTable(str)){
            return true;
        }
    }
    else if(str.startsWith("create index")){
        if(createIndex(str)){
            return true;
        }
    }
    return false;
}

bool MainWindow::createTable(QString str){
    // ^create\\stable\\s\\w+\\s?\\(\\s?((?:[\\w\\s]+,)*[\\w\\s]+)\\s?\\)$
    //(\\w+)\\s(int(\\(?:[0-9]+\\))?|varchar(\\(?:[0-9]+\\))?)((?:pk|notnull|unique|default\\s[0-9]+\\s)*(?:pk|notnull|unique|default))
    QRegularExpression re("^create\\stable\\s(\\w+)\\s?\\(\\s?((?:[\\w\\s\\(\\)]+,)*[\\w\\s\\(\\)]+)\\s?\\)");
    QRegularExpressionMatch match = re.match(str);



    if(match.hasMatch()){
        QRegularExpression re1("(\\w+)\\s(int(\\(?:[0-9]+\\))?|varchar(\\(?:[0-9]+\\))?)((?:pk|notnull|unique|default\\s[0-9]+\\s)*(?:pk|notnull|unique|default))");
        QRegularExpressionMatch match1 = re1.match(match.captured(2));
        tableName=match.captured(1);
        match.captured(2);

        qDebug()<<match.captured(2);
    }
    else{
        ui->textEdit->append("语法错误！");
        return false;
    }
//    tmp=str.section("(",0,0);//分出create table+表名
//    b=str.section("(",1,50);
//    b.chop(1);
//    qDebug()<<b;
//    QStringList a=tmp.split(" ");


    str=ui->textEdit->toPlainText();
    QRegExp exp("\\(\\s?((?:.*,).*)\\s?\\)");
    if(str.indexOf(exp)>=0)
    {
        QStringList list =exp.cap(1).split(",");
        QRegExp first("[a-z]+");//匹配 第一个单词
        QRegExp second("\\s+[^\\s]+");//匹配 第二个单词 (int\\(?[0-9]+\\)?|varchar\\([0-9]+\\))
        QRegExp iv("\\bint\\b");
        QRegExp va("\\bvarchar\\b");
        QRegExp PK("\\bPK\\b");//匹配“PK”
        QRegExp notn("\\bnotnull\\b");//匹配“notnull”
        QRegExp uniq("\\bunique\\b");//匹配“unique”
        QRegExp de("\\bdefault\\b");//匹配“default”

        fileName=tableName+".txt";
        QDir dir;
        if(!dir.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table")){
            dir.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table");
        }
        dir="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table";
        QString path=dir.filePath(fileName);
        QFile file;
        file.setFileName(path);
        if(file.exists()){
            ui->textEdit->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
            ui->textEdit->append("表已存在！");//把str追加到textBrowser中；
            return false;
        }
        file.open(QIODevice::ReadWrite|QIODevice::Text);
        QTextStream out(&file);

        for (int i=0;i<list.size();i++) {
            if(list.at(i).indexOf(first)>=0){

            out<<first.cap();
            qDebug()<<first.cap();
            }
            if(list.at(i).indexOf(second)>=0){
                if(list.at(i).indexOf(PK)>=0){
                    qDebug()<<PK.cap();

                if(PK.cap()=="PK"){
                    out<<second.cap()+" TRUE FALSE FALSE FALSE FALSE FALSE FALSE RESTRICT\n";
                    fileName=tableName+"_index.txt";
                    QDir dir3;
                    if(!dir3.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index")){
                        dir3.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index");
                    }
                    dir3="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index";
                    QString path3=dir3.filePath(fileName);
                    QFile file3;
                    file3.setFileName(path3);
                    file3.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append);
                    QTextStream out3(&file3);
                    out3<<"index_"+first.cap()+"\n";
                    file3.close();
                }
                }else{


                }
                if(list.at(i).indexOf(notn)>=0){
                    qDebug()<<notn.cap();
                if(notn.cap()=="notnull"){
                    out<<second.cap()+" FALSE FALSE TRUE FALSE FALSE FALSE FALSE RESTRICT\n";
                }

                }else{

                }
                if(list.at(i).indexOf(uniq)>=0){
                    qDebug()<<uniq.cap();
                if(uniq.cap()=="unique"){
                    out<<second.cap()+" FALSE TRUE FLASE FALSE FALSE FALSE FALSE RESTRICT\n";
                }
                }else{

                }
                if(list.at(i).indexOf(de)>=0){
                    qDebug()<<de.cap();
                if(de.cap()=="default"){
                    out<<second.cap()+" FALSE FALSE FLASE TRUE FALSE FALSE FALSE RESTRICT\n";
                }
                }else{

                }
            }
        }
         file.close();
        }
    QDir dir1;
    if(!dir1.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\data")){
        dir1.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\data");
    }
    dir1="DBMS/"+dataname+"/data";
    fileName=tableName+".txt";
    QString path1=dir1.filePath(fileName);
    QFile file1;
    file1.setFileName(path1);
    file1.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream out1(&file1);
    file1.close();
    QDir dir4;
    if(!dir4.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission")){
        dir4.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission");
    }
    dir4="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission";
    fileName=tableName+".txt";
    QString path4=dir4.filePath(fileName);
    QFile file4;
    file4.setFileName(path4);
    file4.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream out4(&file4);
    out4<<"sys";
    file4.close();
    ui->textEdit->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
    ui->textEdit->append("表已创建");//把str追加到textBrowser中；

}

//drop table student;
bool MainWindow::dropTable(QString str){
    qDebug()<<"str="<<str;
    QStringList list=str.split(" ");
    if(list.size()<3){
        ui->textEdit->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
        ui->textEdit->append("语法错误！");//把str追加到textBrowser中；
        return false;
    }
    tableName=list.at(2);
    fileName=tableName+".txt";
    QDir dir;
    if(!dir.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table")){
        dir.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table");
    }
    dir="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\table";
    QString path=dir.filePath(fileName);

    qDebug()<<"文件名="<<fileName;
    QFile file;
    file.setFileName(path);

    if(file.exists())
    {
        file.remove();
    }
    QDir dir1;
    if(!dir1.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\data")){
        dir1.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\data");
    }
    dir1="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\data";
    QString path1=dir1.filePath(fileName);

    qDebug()<<"文件名="<<fileName;
    QFile file1;
    file1.setFileName(path1);

    if(file1.exists())
    {
        file1.remove();
    }
    QDir dir4;
    if(!dir4.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission")){
        dir4.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission");
    }
    dir4="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission";
    QString path4=dir4.filePath(fileName);

    qDebug()<<"文件名="<<fileName;
    QFile file4;
    file4.setFileName(path4);

    if(file4.exists())
    {
        file4.remove();
    }
    QDir dir3;
    if(!dir3.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index")){
        dir3.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index");
    }
    dir3="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index";
    fileName=tableName+"_index.txt";
    QString path3=dir3.filePath(fileName);

    qDebug()<<"文件名="<<fileName;
    QFile file3;
    file3.setFileName(path3);

    if(file3.exists())
    {
        file3.remove();
    }

    ui->textEdit->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
    ui->textEdit->append("表已删除");//把str追加到textBrowser中；
}

//create index index_sno on student(sno);
bool MainWindow::createIndex(QString str){
    QStringList list=str.split(" ");
    indexName=list.at(2);
    fileName=tableName+"_index.txt";
    QDir dir3;
    if(!dir3.exists("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index")){
        dir3.mkdir("D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index");
    }
    dir3="D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\index";
    QString path3=dir3.filePath(fileName);

    qDebug()<<"文件名="<<fileName;
    QFile file3;
    file3.setFileName(path3);
    file3.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append);
    QTextStream out3(&file3);
    out3<<indexName;
    file3.close();
    ui->textEdit->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
    ui->textEdit->append("索引已创建");//把str追加到textBrowser中；
    return true;
}

void MainWindow::getUser(QString name){
    nowUser.set_Name(name);

}
bool MainWindow::checkPower(QString tableName){
    QString filename = "D:\\dbms-master\\build-DBMS-Desktop_Qt_5_9_9_MSVC2015_32bit-Debug\\DBMS\\"+dataname+"\\permission\\" +tableName+".txt";
    QFile usertable(filename);
    QStringList strList1;

    if(!usertable.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        this->ui->textEdit->append("CAN'T OPEN THE FILE!");
        return false;

    }
    else{
        while(!usertable.atEnd()){
            QByteArray line = usertable.readLine();
            QString str(line);
            qDebug() << str<<this->nowUser.get_Name();
            if(str == this->nowUser.get_Name()){

                usertable.close();
                return true;
            }
        }
    }
    usertable.close();
    return false;
}
