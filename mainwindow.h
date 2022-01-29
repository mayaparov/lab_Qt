#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "editor.h"
#include "highlight.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QToolBar>
#include <QToolButton>
#include <QIcon>
#include "window.h"
#include <QPixmap>
#include<QStatusBar>
#include<QString>
#include<QDate>
#include<QTime>
#include <QCheckBox>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void about_me();
    void save();
    void save_as();
    void create_new();
    void open_file(const QString &path = QString());
    void update_1();
    void undo_();
    void redo_();
    void copy_();
    void cut_();
    void paste_();
    void find_();
    void find_and_replace_();
    void select_all();
    void font_();
    void shift_();
    void choose_font_();
    void choose_line_();
    void line_numbering_();
    void tollbar_();
    void syntax_highlighting_();
    void status_bar_();
    void name_();
    void change_view();
    void downolad_view(const QString &path = QString());
    void default_view();
    void cplus_14();
    void cplus_17();
    void cplus_20();
    void c_11();
    void c_18();

private:
    QString path = QString("");
    void set_Edit();
    void set_file_m();
    QFont font;
    QTextCharFormat fmt;
    Editor *editor;
    Highlighter *highlight;
    QMenu * fileMenu;
    QMenu *helpMenu;
    QMenu *format;
    QMenu *Edit;
    QMenu *view;
    QMenu *hike;
    QMenu *choose_syntax;
    QMenu *choose_style;
    QMenu *All_style;
    QInputDialog *d1;
    QInputDialog *d2;
    about  w1;
    QToolBar *bar;
    QToolButton * p;

    bool z=1;
    int kilosize =0;
    int symsize =0;
    int numberstroke =0;
    int numberword=0;
    int numbersym= 0;
    QStatusBar *bar1;

    QLabel *mipi;
    QLabel *mini;
    QLabel *misi;
    QLabel *miniSTR;
    QLabel *miti;
    QLabel *numchar;
    QLabel *numword;
    QLabel *numsym;

    QAction *available;
    QAction *syn1;
    QAction *syn2;
    QAction *syn3;
    QAction *syn4;
    QAction *syn5;
    QToolButton *pop;
    QFile file;
    bool available_=true;
    QString name= "";
    QColor col_4=Qt::white;
    int key_syntax =1;
    QLabel* labe1;
    bool ln = true ;
    bool tb = true ;
    bool sh = true ;
    bool sb = true ;
};
#endif
