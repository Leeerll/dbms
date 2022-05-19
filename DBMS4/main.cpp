#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    login w;


    w.setWindowTitle("DBMS");//为窗口添加图标与文本
    QIcon icon_tdatabase;
    icon_tdatabase.addFile("D:\\dbms-master\\FILE\\res\\mouse.png");
    w.setWindowIcon(icon_tdatabase);


    w.setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap("D:\\dbms-master\\FILE\\res\\mouse.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w.setPalette(palette);
    w.show();
    return a.exec();
}
