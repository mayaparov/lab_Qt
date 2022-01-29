#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/photo/icon.jpg"));
    w.setGeometry(300,300,1180,640);
    w.show();
    return a.exec();
}
