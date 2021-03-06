#include <QtWidgets>

#include "codeeditor.h"


CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(textChanged()), this, SLOT(plainTextChanged()));
    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}



int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}



void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}



void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}



void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}



void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
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

// Set the indent
void CodeEditor::keyPressEvent ( QKeyEvent * event )
{

  if( event->key() == Qt::Key_Return ) {
    /* do your stuff here */
      auto cur = textCursor();
//      qDebug() << "position::" << cur.position();
      int flagl = 0;
      int flagr = 0;
    event->accept();
    QString text = toPlainText();
    QString ntext = "";
    ntext = ntext + "\n";
    int n = text.size();
    int m = -1;
    int nos = 0;
//    qDebug() << ntext;
    if(n == 0) {
        insertPlainText(ntext);

        moveCursor(QTextCursor::NextRow,QTextCursor::MoveAnchor);
    }
    if(n > 0) {
        for (int i = n-1; i >= 0; i--) {
            if(text[i] == '\n' || i == 0) {
                m = i;
                break;
            }
        }

//        qDebug() << m;
        // Dectect '{' and '}'
        if (text[n-1] == '{') {
            flagl = 1;
            nos = nos + 4;
        } else if (text[0] == '}') {
            flagr = 1;

        } else if (text[n-1] == '}') {
            flagr = 1;
            if (text[n-2] == '\n' || n-2 == 0) {
                nos = nos + 4;
            } else {
                nos = nos - 4;
            }
        }


        // calculating number of space
        if (m != -1) {
            int k;
            if (m != 0) {
                k = m+1;
            } else {
                k = m;
            }

            while (text[k] == '\t'||text[k] == ' ') {
                if (text[k] == '\t') {
                    nos = nos + 4;
                } else if (text[k] == ' ') {
                    nos = nos + 1;
                } else {
                    break;
                }
                k++;
            }


        }
        if (flagl == 1) {
            if(nos != 0) {
              for (int i = 0; i < nos; i++) {
                  ntext = ntext + " ";
              }
              ntext = ntext + '\n';
              for (int i = 0; i < nos - 4; i++) {
                  ntext = ntext + " ";
              }
              ntext = ntext + '}';

            }
        } else if (flagr == 1) {
            if(nos != 0) {
                if (nos >= 4) {
                    for (int i = 0; i < nos; i++) {
                        ntext = ntext + " ";
                    }
                }
            }
        } else if (flagl != 1 && flagr != 1) {
            if(nos != 0) {
                 for (int i = 0; i < nos; i++) {
                     ntext = ntext + " ";
                 }
             }
        }
        insertPlainText(ntext);

        moveCursor(QTextCursor::NextRow,QTextCursor::MoveAnchor);
    }
  }
  else
    QPlainTextEdit::keyPressEvent( event );
}
