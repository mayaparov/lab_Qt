#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    set_Edit();
    set_file_m();

    connect(editor->document(), &QTextDocument::contentsChange,this,&MainWindow::name_);
    numbersym= editor->document()->lineCount();
}

MainWindow::~MainWindow()
{
}

void MainWindow::create_new(){
    name = "Без имени";
    editor->clear();
}
void MainWindow::open_file(const QString &path){
    QString fileName = path;

        if (fileName.isNull()){
            fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/D:",tr("Text files (*.txt)"));
           name=QFileInfo(fileName).fileName();
           symsize =QFileInfo(fileName).size();
           kilosize =(QFileInfo(fileName).size())/1024 +1;
           setWindowTitle(name);
           numberstroke = QTextStream(&file).readAll().split('\n').count();
        }
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::Text))
                editor->setPlainText(file.readAll());

        }

}
void MainWindow::set_Edit(){

        font.setFamily("Arial");
        font.setFixedPitch(true);
        font.setPointSize(10);

        editor = new Editor(this);
        setCentralWidget(editor);
        editor->setWindowTitle(QObject::tr("Без имени"));
        editor->setFont(font);
        editor->setGeometry(0,100,640,480);
        editor->show();

        highlight = new Highlighter(editor->document(),key_syntax);
        if (file.open(QFile::ReadOnly | QFile::Text))
              editor->setPlainText(file.readAll());
        editor->setPlainText(file.readAll());

}
void MainWindow::set_file_m()
{
    pop = new QToolButton();
    pop->setText(tr("t/t,r"));
    QIcon find_icon(":/photo/find.jpg");
    pop->setIcon(find_icon);
    fileMenu= menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(tr("&Новый"), this, SLOT(create_new()), QKeySequence(tr("Ctrl+N","File|New")));
    fileMenu->addAction(tr("&Открыть"), this, SLOT(open_file()),QKeySequence(tr("Ctrl+O","File|Open")));
    fileMenu->addAction(tr("&Сохранить"), this, SLOT(save()), QKeySequence(tr("Ctrl+S","File|Save")));
    fileMenu->addAction(tr("&Сохранить как"), this, SLOT(save_as()),QKeySequence(tr("Ctrl+K","File|Save_As")));
    fileMenu->addAction(tr("&Выход"), qApp, SLOT(quit()), QKeySequence(tr("Ctrl+Q","File|Exit")));
    Edit = menuBar()->addMenu(tr("&Правка"));
    Edit->addAction(tr("&Отменить"),this,SLOT(undo_()));
    Edit->addAction(tr("&Повторить"),this,SLOT(redo_()));
    Edit->addAction(tr("&Копировать"),this,SLOT(copy_()));
    Edit->addAction(tr("&Вырезать"),this,SLOT(cut_()));
    Edit->addAction(tr("&Вставить"),this,SLOT(paste_()));
    Edit->addAction(tr("&Найти"),this,SLOT(find_()));
    Edit->addAction(tr("&Найти и заменить"),this,SLOT(find_and_replace_()));
    Edit->addAction(tr("&Выделить все"),this,SLOT(select_all()));
    format =menuBar()->addMenu(tr("&Формат"));
    available=format->addAction(tr("&Перенос по словам"),this,SLOT(shift_()));
    format->addAction(tr("&Выбор шрифта"),this,SLOT(font_()));
    view= menuBar()->addMenu(tr("&Вид"));
    view->addAction(tr("Выбор цвета фона"),this,SLOT(choose_font_()));
    view->addAction(tr("Выбор цвета текущей строки"),this,SLOT(choose_line_()));
    view->addAction(tr("Нумерация строк"),this,SLOT(line_numbering_()));
    view->addAction(tr("Панель инструментов"),this,SLOT(tollbar_()));
    view->addAction(tr("Строка состояния"),this,SLOT(status_bar_()));
    view->addAction(tr("Подстветка синтаксиса"),this,SLOT(syntax_highlighting_()));
    helpMenu=menuBar()->addMenu(tr("&Справка"));
    helpMenu->addAction(tr("Информация о приложении"),this,SLOT(about_me()));
    available->setEnabled(available_);

    choose_syntax= new QMenu(tr("&Выбор синтаксиса"),this);
    choose_style=new QMenu(tr("&Выбор стиля подсветки"),this);
    view->addMenu(choose_syntax);
    view->addMenu(choose_style);
    choose_style->addAction(tr("Изменить"),this,SLOT(change_view()));
    choose_style->addAction(tr("Загрузить"),this,SLOT(downolad_view()));
    choose_style->addAction(tr("Default"),this,SLOT(default_view()));
    All_style=new QMenu(tr("Доступные стили"),this);
    choose_style->addMenu(All_style);
    syn1=choose_syntax->addAction(tr("Си++ 14"),this,SLOT(cplus_14()));
    syn2=choose_syntax->addAction(tr("Си++ 17"),this,SLOT(cplus_17()));
    syn3=choose_syntax->addAction(tr("Си++ 20"),this,SLOT(cplus_20()));
    syn4=choose_syntax->addAction(tr("Си 11"),this,SLOT(c_11()));
    syn5=choose_syntax->addAction(tr("Си 18"),this,SLOT(c_18()));
    syn1->setEnabled(false);
    bar=new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, bar);
    bar->setContextMenuPolicy(Qt::PreventContextMenu);
    bar->setGeometry(0,20,400,20);

    QIcon new_icon(":/photo/new.jpg");
    QIcon open_icon(":/photo/open.jpg");
    QIcon save_icon(":/photo/save.jpg");
    QIcon undo_icon(":/photo/undo.jpg");
    QIcon redo_icon(":/photo/redo.jpg");
    QIcon cut_icon(":/photo/cut.jpg");
    QIcon paste_icon(":/photo/paste.jpg");
    QIcon copy_icon(":/photo/copy.jpg");

    bar->addAction(new_icon, tr("&Новый"),this,SLOT(create_new()));
    bar->addAction(open_icon,tr("&Открыть"),this,SLOT(open_file()));
    bar->addAction(save_icon,tr("&Сохранить"),this,SLOT(save()));
    bar->addAction(undo_icon,tr("&Отменить"),this,SLOT( undo_()));
    bar->addAction(redo_icon,tr("&Повторить"),this,SLOT( redo_()));
    bar->addAction(copy_icon,tr("&Копировать"),this,SLOT(copy_()));
    bar->addAction(cut_icon,tr("&Вырезать"),this,SLOT(cut_()));
    bar->addAction(paste_icon,tr("&Вставить"),this,SLOT(paste_()));
    bar->addWidget(pop);


    pop->setPopupMode(QToolButton::InstantPopup);
    hike= new QMenu(pop);
    pop->setMenu(hike);
    hike->addAction(find_icon,tr("&Найти"),this,SLOT(find_()));
    hike->addAction(find_icon,tr("&Найти и заменить"),this,SLOT(find_and_replace_()));

    mipi = new QLabel(this);
    misi = new QLabel(this);
    miti = new QLabel(this);
    numchar=new QLabel(this);
    numword=new QLabel(this);
    numsym=new QLabel(this);
    mipi->setText("Позиция курсора (столбец:строка) " + QString::number( editor->textCursor().positionInBlock()) + ":" + QString::number(editor->textCursor().blockNumber() + 1));

    misi->setText(" Размер в килобайтах: " + QString::number(kilosize));
    numchar->setText("Количество символов " + QString::number(symsize));
    numword->setText("Количество слов  " + QString::number(numberword));
    numsym->setText("Количество строк " + QString::number(numbersym));

    miti->setText("   Текущее время: "+QDateTime::currentDateTime().toString("hh:mm"));
    connect(editor,SIGNAL(cursorPositionChanged()),this,SLOT(update_1()));

    statusBar()->addWidget(mipi);
    statusBar()->addWidget(miti);
    statusBar()->addWidget(numsym);
    statusBar()->addWidget(numword);
    statusBar()->addWidget(numchar);
    statusBar()->addWidget(misi);
}
void MainWindow::save(){
    QString fileName = name;
    if (fileName != "") {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                stream << editor->toPlainText();
                stream.flush();
                file.close();
            }
        }
}
void MainWindow::save_as(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"),
                               "/D:",tr("Text files (*.txt );;All C++ files (*.cpp );;All C++ files (*.h)" ));

        QFile file_save(fileName);
        file_save.open(QIODevice::WriteOnly);
                QTextStream stream(&file_save);
                stream << editor->toPlainText();
                stream.flush();
                file_save.close();

        name = file_save.fileName();

}

void MainWindow::undo_(){
    editor->undo_1();
}
void MainWindow::redo_(){
    editor->redo_1();
}
void MainWindow::copy_(){
    editor->copy();
}
void MainWindow::cut_(){
    editor->cut();
}
void MainWindow::paste_(){
    editor->paste();
}
void MainWindow::find_(){

    d1 = new QInputDialog(this,Qt::Dialog);
    bool  find1;
    QString text = QInputDialog::getText(this, tr("Введите текст"),tr("Найти:"), QLineEdit::Normal,
                                   QDir::home().dirName(), &find1);

    editor->find(text,QTextDocument::FindCaseSensitively);
}
void MainWindow::find_and_replace_(){
    d1 = new QInputDialog(this,Qt::Dialog);
    bool  find1;
    QString text = QInputDialog::getText(this, tr("Введите текст"),tr("Найти:"), QLineEdit::Normal,
                                       QDir::home().dirName(), &find1);

    if(editor->find(text,QTextDocument::FindCaseSensitively)){
        d2 = new QInputDialog(this,Qt::Dialog);
        bool  r1;
        QString text1 = QInputDialog::getText(this, tr("На что нужно заменить"),tr("Заменить:"), QLineEdit::Normal,
                                       QDir::home().dirName(), &r1);
        editor->textCursor().deleteChar();
        editor->textCursor().insertText(text1);
    }
}
void MainWindow::select_all(){
    editor->selectAll();
}
void MainWindow::font_(){
    bool fonk;
    QFont fnt = QFontDialog::getFont(&fonk);
    if(fonk)
        editor->setFont(fnt);
}
void MainWindow::shift_(){
  if (available_)
    editor->setWordWrapMode(QTextOption::WrapAnywhere);
  else
    editor->setWordWrapMode(QTextOption::WordWrap);

  available_= !available_;
}

void MainWindow::choose_font_(){
    col_4 = QColorDialog::getColor();
    if (col_4.isValid() ) {
    QPalette palette = editor->palette();
            palette.setBrush(QPalette::Base, QBrush(col_4));
            editor->setPalette(palette);
    }
}
void MainWindow::choose_line_(){
    QColor color = QColorDialog::getColor();
    if (color.isValid())
        editor->lineColor=color.lighter(160);
    editor->highlightCurrentLine();

}
void MainWindow::line_numbering_(){
    if(ln){
        editor->a=false;
        ln= false;
    }
    else{
        editor->a=true;
        ln= true;
    }


}
void MainWindow::tollbar_(){
    if(tb){
        bar->setHidden(true);
        tb= false;
    }
    else{
        bar->setHidden(false);
        tb= true;
   }
}
void MainWindow::syntax_highlighting_(){

    if(sh){
        highlight->clear();
        sh= false;
    }
    else{
        highlight = new Highlighter(editor->document(),key_syntax);
        sh= true;
   }
}
void MainWindow::about_me(){
   w1.setMinimumWidth(200);
   w1.show();
}
void MainWindow::update_1(){
    numberword= editor->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count();
    numbersym= editor->document()->lineCount();
    mipi->setText("Позиция курсора (столбец строка) " +QString::number( editor->textCursor().positionInBlock()) + ":" + QString::number(editor->textCursor().blockNumber() + 1));
    misi->setText(" Размер в килобайтах: " + QString::number(kilosize));
    numchar->setText("Количество символов " + QString::number(symsize));
    numword->setText("Количество слов  " + QString::number(numberword));
    numsym->setText("Количество строк " + QString::number(numbersym));

}
void MainWindow::status_bar_(){
   if(sb) {
       this->statusBar()->setHidden(true);
       sb=false;
   }
   else{
       this->statusBar()->setHidden(false);
       sb=true;
   }
}

void MainWindow::name_(){
    QString name1 = "*" + name;
    setWindowTitle(name1);
}
void MainWindow::change_view(){
    QColor color_1=QColorDialog::getColor();
    bool fun1;
    int s_1 = QInputDialog::getInt(this, tr("higlight_keyword"),
                        tr("higliht"), 100, 0, 200, 15, &fun1);
    QBrush b_1;
    b_1=color_1.lighter(s_1);

    highlight->setKeywordColor(b_1);


    QColor color_2=QColorDialog::getColor();
    bool fun2;
    int s_2 = QInputDialog::getInt(this, tr("higlight_Class"),
                            tr("higliht"), 100, 0, 200, 15, &fun2);
    QBrush b_2;
    b_2=color_2.lighter(s_2);
    highlight->setClassColor(b_2);


    QColor color_3=QColorDialog::getColor();
    bool fun3;
    int s_3 = QInputDialog::getInt(this, tr("higlight_Quotation"),
                            tr("higliht"), 100, 0, 200, 15, &fun3);
    QBrush b_3;
    b_3=color_3.lighter(s_3);

    highlight->setQuotationColor(b_3);


    QColor color_4=QColorDialog::getColor();
    bool fun4;
    int s_4 = QInputDialog::getInt(this, tr("higlight_MultiLine"),
                                   tr("higliht"), 100, 0, 200, 15, &fun4);
    QBrush b_4;
    b_4=color_4.lighter(s_4);
    highlight->setFunctionColor(b_4);

    QColor color_5=QColorDialog::getColor();
    bool fun5;
    int s_5 = QInputDialog::getInt(this, tr("higlight_MultiLine"),
                            tr("higliht"), 100, 0, 200, 15, &fun5);
    QBrush b_5;
    b_5=color_5.lighter(s_5);
    highlight->setMultiLineColor(b_5);
    bool  fun6;

    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("style name: Без имени"), QLineEdit::Normal,
                                       QDir::home().dirName(), &fun6);

}
void MainWindow::downolad_view(const QString &path){


      QBrush b_1;
      QBrush b_2;
      QBrush b_3;
      QBrush b_4;
      QBrush b_5;



      highlight->setKeywordColor(b_1);
      highlight->setClassColor(b_2);
      highlight->setQuotationColor(b_3);
      highlight->setFunctionColor(b_4);
      highlight->setMultiLineColor(b_5);
}
void MainWindow::default_view(){
    QBrush syn1=  Qt::magenta;
    QBrush syn2 = Qt::darkMagenta;
    QBrush syn3 = Qt::darkGreen;
    QBrush syn4 = Qt::blue;
    QBrush syn5 = Qt::red;
    highlight->setKeywordColor(syn1);
    highlight->setClassColor(syn2);
    highlight->setQuotationColor(syn3);
    highlight->setFunctionColor(syn4);
    highlight->setMultiLineColor(syn5);
}

void MainWindow::cplus_14(){
    key_syntax=1;
    highlight = new Highlighter(editor->document(),key_syntax);
    syn1->setEnabled(false);
    syn2->setEnabled(true);
    syn3->setEnabled(true);
    syn4->setEnabled(true);
    syn5->setEnabled(true);
}
void MainWindow::cplus_17(){
    key_syntax=2;
    highlight = new Highlighter(editor->document(),key_syntax);
    syn1->setEnabled(true);
    syn2->setEnabled(false);
    syn3->setEnabled(true);
    syn4->setEnabled(true);
    syn5->setEnabled(true);
}
void MainWindow::cplus_20(){
    key_syntax=3;
    highlight = new Highlighter(editor->document(),key_syntax);
    syn1->setEnabled(true);
    syn2->setEnabled(true);
    syn3->setEnabled(false);
    syn4->setEnabled(true);
    syn5->setEnabled(true);
}
void MainWindow::c_11(){
    key_syntax=4;
    highlight = new Highlighter(editor->document(),key_syntax);
    syn1->setEnabled(true);
    syn2->setEnabled(true);
    syn3->setEnabled(true);
    syn4->setEnabled(false);
    syn5->setEnabled(true);
}
void MainWindow::c_18(){
    key_syntax=5;
    highlight = new Highlighter(editor->document(),key_syntax);
    syn1->setEnabled(true);
    syn2->setEnabled(true);
    syn3->setEnabled(true);
    syn4->setEnabled(true);
    syn5->setEnabled(false);
}
