#include <QtWidgets>

#include "editor.h"

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    lineNumberArea->setGeometry(40,40,640,480);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    setGeometry(10,40,540,480);


    connect(this,&Editor::copyAvailable,this,&Editor::change_);

}


int Editor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());

    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}


void Editor::updateLineNumberAreaWidth(int )
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void Editor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}




void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}




void Editor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    if(a){
        QPainter painter(lineNumberArea);
        painter.fillRect(event->rect(), Qt::lightGray);
        QTextBlock block = firstVisibleBlock();
        int blockNumber = block.blockNumber();
        int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        int bottom = top + (int) blockBoundingRect(block).height();


        while (block.isValid() && top <= event->rect().bottom()) {
            if (block.isVisible() && bottom >= event->rect().top()) {
                QString number = QString::number(blockNumber + 1);
                painter.setPen(Qt::black);
                painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                                 Qt::AlignRight, number);
            }

            block = block.next();
            top = bottom;
            bottom = top + (int) blockBoundingRect(block).height();
            ++blockNumber;
        }
    }
}



void Editor::delete_(){
    QTextCursor c = textCursor();
    c.removeSelectedText();
}
void Editor::redo_1(){
    redo();

}
void Editor::undo_1(){
    undo();

}
void Editor::paste_word(){
    QTextCursor c = textCursor();
    c.select(QTextCursor::WordUnderCursor);
    setTextCursor(c);
}
void Editor::paste_current_line(){
    QTextCursor c = textCursor();
    c.select(QTextCursor::LineUnderCursor);
    setTextCursor(c);
}
void Editor::change_(){
    available= false;
}
void Editor::contextMenuEvent(QContextMenuEvent *event )
{
    menu = new QMenu(this);
    menu1=menu->addAction(tr("Отменить"),this,SLOT(undo_1()));
    menu2=menu->addAction(tr("Повторить"),this,SLOT(redo_1()));
    menu3=menu->addAction(tr("Выделить строку"),this,SLOT(select_string()));
    menu4=menu->addAction(tr("Копировать"),this,SLOT(copy()));
    menu5=menu->addAction(tr("Вырезать"),this,SLOT(cut()));
    menu6=menu->addAction(tr("Вставить"),this,SLOT(paste()));
    menu7=menu->addAction(tr("Удалить"),this,SLOT(delete_()));
    menu8=menu->addAction(tr("Выделить все"),this,SLOT(selectAll()));
    menu1->setEnabled(true);
    menu2->setEnabled(true);
    menu3->setEnabled(available);
    menu4->setEnabled(!available);
    menu5->setEnabled(!available);
    menu6->setEnabled(!available);
    menu7->setEnabled(!available);
    menu8->setEnabled(!available);
    menu->exec(event->globalPos());
    available= true;
}
