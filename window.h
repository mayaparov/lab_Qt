#ifndef WINDOW_H
#define WINDOW_H

#include <QPixmap>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include<QTableWidgetItem>
class about: public QDialog{
Q_OBJECT
public:
    about(QWidget* p = 0);

private:
    QLabel *about_me;
    QLabel *about_Qt;
    QLabel *about_qt_s;
    QLabel *about_qt;
    QLabel *about_time;
    QLabel *label;
    QPixmap pic;
};

#endif
