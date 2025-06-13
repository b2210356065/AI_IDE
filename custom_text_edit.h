#ifndef CUSTOM_TEXT_EDIT_H
#define CUSTOM_TEXT_EDIT_H

#include <QTextEdit>
#include <QTimer>
#include "arrange_strings.h"

class CustomTextEdit : public QTextEdit {
Q_OBJECT

public:
    explicit CustomTextEdit(QWidget *parent = nullptr);
    void runText();

private slots:
    void onTextChanged();
    void processPendingChanges();


private:

    void processCurrentLineContent(QString &lineContent, QTextCursor &cursor,int savedPosition);
    arrange_strings *arrangeStrings= nullptr;
    QTimer *timer;
    QString lastLineText;
};

#endif // CUSTOM_TEXT_EDIT_H
