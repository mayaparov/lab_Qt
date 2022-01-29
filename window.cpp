#include "window.h"
#include <QDate>

about::about(QWidget* p)
{
    setWindowTitle(tr("Разработчик программы и версия Qt"));
    setGeometry(100,100,640,580);
    about_me= new QLabel(tr("Япаров Матвей"),this);
    about_qt_s= new QLabel(QString("Версия сборки: ") + QString(qVersion()),this);
    about_qt= new QLabel(QString("Версия QT: ") + QString(qVersion()),this);

    QDate data = QDate::currentDate();

    about_time= new QLabel((data.toString()),this);
    about_me->move(50,10);
    about_qt_s->move(50,20);
    about_qt->move(50,30);
    about_time->move(50,50);
    QPixmap pic(":/photo/me.jpg" );
    label= new QLabel(this);
    label->setPixmap(pic);
    label->move(50,70);
}
