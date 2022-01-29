#ifndef Editor_H
#define Editor_H

#include <QPlainTextEdit>
#include <QObject>
#include "highlight.h"
QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

class Editor : public QPlainTextEdit
{
Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    bool a=true;
    QColor lineColor = QColor(Qt::blue).lighter(160);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    QMenu *menu;
    void contextMenuEvent(QContextMenuEvent *event );

    QAction *menu1;
    QAction *menu2;
    QAction *menu3;
    QAction *menu4;
    QAction *menu5;
    QAction *menu6;
    QAction *menu7;
    QAction *menu8;
    QAction *menu9;
    QAction *menu10;
    bool available= true;
    void change_();
    void resizeEvent(QResizeEvent *event = nullptr);
public slots:
    void paste_word();
    void paste_current_line();
    void redo_1();
    void undo_1();
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void delete_();

private:
    QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(Editor *editor) : QWidget(editor) {
        Editor = editor;
    }
    Highlighter *highlight;

    QSize sizeHint() const override {
        return QSize(Editor->lineNumberAreaWidth(), 0);
    }

public:
    void paintEvent(QPaintEvent *event) override {
        Editor->lineNumberAreaPaintEvent(event);
    }

private:
    Editor *Editor;

};


#endif
