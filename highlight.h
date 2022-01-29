#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H


#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

class Highlighter : public QSyntaxHighlighter
{
Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0, int n = 0);
    int number ;
    QBrush getKeywordColor();
    QBrush getClassColor();
    QBrush getQuotationColor();
    QBrush getFunctionColor();
    QBrush getMultiLineColor();
    void setKeywordColor( QBrush);
    void setClassColor( QBrush);
    void setQuotationColor( QBrush);
    void setFunctionColor( QBrush);
    void setMultiLineColor( QBrush);
    void setNumber(int n_);
    void clear();
protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QRegExp commentStartExpression;
    QRegExp commentEndExpression;
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QBrush colorKeyword = Qt::magenta;
    QBrush colorClassFormat = Qt::darkMagenta;
    QBrush colorQuotationFormat = Qt::darkGreen;
    QBrush colorFunctionFormat = Qt::blue;
    QBrush colorMultiLineFormat = Qt::red;
    HighlightingRule rule;
    QStringList regexpSPlus14;
    QStringList regexpSPlus17;
    QStringList regexpSPlus20;
    QStringList regexpS11;
    QStringList regexpS18;
};


#endif

