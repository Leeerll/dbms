#ifndef LOGIN_H
#define LOGIN_H
#include<QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE
class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void mysystemDataBase();
    void mysystemuser();
    void readtxt();
private slots:
    void on_pushButton_clicked();
    void my_show_slot();
private:
    Ui::login *ui;
    QTcpServer *ser;
    QTcpSocket *cli;
    QMap<QString,QString> pathtxt;


};
#endif // LOGIN_H
