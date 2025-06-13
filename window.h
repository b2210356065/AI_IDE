#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include "custom_text_edit.h" // Özel QTextEdit sınıfı

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow {
Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void openFolder();
    void createFolder();
    void runFile(); // "Run" butonu için slot

private:
    Ui::Window *ui;
    CustomTextEdit *textEdit;
    QFileSystemModel *fileSystemModel;
    QTreeView *treeView;
    QString currentFile;

    void setupMenu();
    void setupFileSystemView();
};

#endif // WINDOW_H
