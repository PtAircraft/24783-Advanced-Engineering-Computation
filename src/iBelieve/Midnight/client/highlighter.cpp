#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::red);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\babstract\\b" << "\\bassert\\b"
                    << "\\bcase\\b" << "\\bcatch\\b" << "\\bcontinue\\b"
                    << "\\bdefault\\b" << "\\benum\\b"
                    << "\\bextends\\b" << "\\bfor\\b"
                    << "\\bgoto\\b" << "\\binstanceof\\b"
                    << "\\bnew\\b"
                    << "\\bpackage\\b" << "\\breturn\\b"
                    << "\\bstrictfp\\b"
                    << "\\bswitch\\b" << "\\bsynchronized\\b"
                    << "\\btransient\\b"
                    << "\\btry\\b" << "\\bdo\\b" << "\\bfinal\\b"
                    << "\\bif\\b" << "\\binterface\\b"
                    << "\\bprivate\\b"
                    << "\\bthis\\b" << "\\bvoid\\b"
                    << "\\bbreak\\b" << "\\bclass\\b"
                    << "\\bfinally\\b" << "\\bimplements\\b"
                    << "\\bprotected\\b" << "\\bstatic\\b"
                    << "\\bthrow\\b" << "\\bvolatile\\b"
                    << "\\belse\\b" << "\\bconst\\b"
                    << "\\bthis\\b" << "\\bvoid\\b"
                    << "\\bimport\\b" << "\\bnative\\b"
                    << "\\bpublic\\b" << "\\bsuper\\b"
                    << "\\bthrows\\b" << "\\bwhile\\b"
                    << "\\btrue\\b" << "\\bfalse\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    varFormat.setForeground(Qt::blue);
    varFormat.setFontWeight(QFont::Bold);
    QStringList varPatterns;
    varPatterns << "\\bbyte\\b" << "\\bboolean\\b"
                << "\\bchar\\b"
                    << "\\bfloat\\b" << "\\bdouble\\b"
                    << "\\bshort\\b"
                    << "\\bint\\b" << "\\bCharacter\\b"
                    << "\\bInteger\\b"
                    << "\\bDouble\\b" << "\\bBoolean\\b"
                    << "\\bString\\b";
    foreach (const QString &pattern, varPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = varFormat;
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkYellow);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkGreen);

    quotationFormat.setForeground(Qt::magenta);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
