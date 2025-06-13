#include "custom_text_edit.h"
#include <QDebug>
#include <QTextCursor>
#include <QTextBlock>
#include <iostream>

using namespace std;
CustomTextEdit::CustomTextEdit(QWidget *parent)
        : QTextEdit(parent), timer(new QTimer(this)), arrangeStrings(new arrange_strings()) {
    timer->setInterval(300);
    connect(timer, &QTimer::timeout, this, &CustomTextEdit::processPendingChanges);
    connect(this, &QTextEdit::textChanged, this, &CustomTextEdit::onTextChanged);
}

void CustomTextEdit::onTextChanged() {
    timer->start();
}
void CustomTextEdit::runText(){
    timer->stop();
    std::vector<string> lines;

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Start);

    QTextBlock block = cursor.block();
    while (block.isValid()) {
        lines.push_back(block.text().toStdString());
        block = block.next();
    }
    arrangeStrings->run(lines);
}

void CustomTextEdit::processPendingChanges() {
    timer->stop();
    QTextCursor cursor = textCursor();
    int savedPosition = cursor.position();

    QTextBlock currentBlock = cursor.block();
    int blockPosition = currentBlock.position();

    cursor.setPosition(blockPosition);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

    QString currentLineText = currentBlock.text();

    if (currentLineText != lastLineText) {
        processCurrentLineContent(currentLineText, cursor,savedPosition);
        lastLineText = currentLineText;
    }
}

void CustomTextEdit::processCurrentLineContent(QString &lineContent, QTextCursor &cursor,int savedPosition) {
    string stdStr = lineContent.toStdString();
    vector<string> strings = arrangeStrings->split_line(stdStr);
    arrangeStrings->arrange_split_line(strings);
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

    QTextCharFormat format;

    format.setForeground(Qt::white);
    cursor.setCharFormat(format);
    cursor.insertText(QString::fromStdString(strings[0] + strings[1]));

    format.setForeground(Qt::red);
    cursor.setCharFormat(format);
    cursor.insertText(QString::fromStdString(strings[2]));

    strings[3]+=arrangeStrings->play_lines(stdStr);
    vector<string> split_string=arrangeStrings->split_string(strings[3],'\\');

    format.setForeground(Qt::black);
    cursor.setCharFormat(format);
    cursor.insertText(QString::fromStdString(split_string[0]));

    format.setForeground(Qt::green);
    cursor.setCharFormat(format);
    cursor.insertText(QString::fromStdString(split_string[1]));

    cursor.setPosition(savedPosition);
    setTextCursor(cursor);
}
