#include "window.h"
#include "ui_window.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QTextEdit>
#include <QToolBar> // Yeni

Window::Window(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::Window) {

    ui->setupUi(this);

    // Pencereyi tam ekran yap
    this->setWindowState(Qt::WindowMaximized);

    // Not defteri oluştur
    textEdit = new CustomTextEdit(this); // Özel QTextEdit sınıfını kullan
    textEdit->setStyleSheet("background-color: grey; color: white;");
    textEdit->setStyleSheet("QTextEdit { caret-color: black; }");
    setCentralWidget(textEdit);

    // Dosya sistemini görüntüleyen yapı oluştur
    setupFileSystemView();

    // Menüleri ayarla
    setupMenu();
}

Window::~Window() {
    delete ui;
}

void Window::setupMenu() {
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *newAction = fileMenu->addAction("New");
    connect(newAction, &QAction::triggered, this, &Window::newFile);

    QAction *openAction = fileMenu->addAction("Open");
    connect(openAction, &QAction::triggered, this, &Window::openFile);

    QAction *saveAction = fileMenu->addAction("Save");
    connect(saveAction, &QAction::triggered, this, &Window::saveFile);

    QAction *saveAsAction = fileMenu->addAction("Save As");
    connect(saveAsAction, &QAction::triggered, this, &Window::saveFileAs);

    QAction *openFolderAction = fileMenu->addAction("Open Folder");
    connect(openFolderAction, &QAction::triggered, this, &Window::openFolder);

    QAction *createFolderAction = fileMenu->addAction("Create Folder");
    connect(createFolderAction, &QAction::triggered, this, &Window::createFolder);

    QAction *runAction = new QAction("Run", this);
    connect(runAction, &QAction::triggered, this, &Window::runFile);
    menuBar()->addAction(runAction); // Menü çubuğuna doğrudan eklenir
}

void Window::setupFileSystemView() {
    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());

    treeView = new QTreeView(this);
    treeView->setModel(fileSystemModel);
    treeView->setRootIndex(fileSystemModel->index(QDir::homePath()));
    treeView->setColumnWidth(0, 250);
    treeView->setFixedWidth(300);

    QDockWidget *dockWidget = new QDockWidget("File Explorer", this);
    dockWidget->setWidget(treeView);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // QDockWidget'i ana pencereye ekleyin
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    connect(treeView, &QTreeView::clicked, [this](const QModelIndex &index) {
        QString path = fileSystemModel->filePath(index);
        if(QFileInfo(path).isFile()) {
            QFile file(path);
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                textEdit->setText(in.readAll());
                file.close();
                currentFile = path;
            }
        }
    });
}

void Window::newFile() {
    currentFile.clear();
    textEdit->setText("");
}

void Window::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
        currentFile = fileName;
    }
}

void Window::saveFile() {
    if(currentFile.isEmpty()) {
        saveFileAs();
        return;
    }

    QFile file(currentFile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    }
}

void Window::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File As");
    if(!fileName.isEmpty()) {
        currentFile = fileName;
        saveFile();
    }
}

void Window::openFolder() {
    QString folder = QFileDialog::getExistingDirectory(this, "Open Folder", QDir::homePath());
    if(!folder.isEmpty()) {
        treeView->setRootIndex(fileSystemModel->index(folder));
    }
}

void Window::createFolder() {
    QString folder = QFileDialog::getExistingDirectory(this, "Create Folder", QDir::homePath());
    if(!folder.isEmpty()) {
        QDir dir(folder);
        dir.mkdir("New Folder");
        treeView->setRootIndex(fileSystemModel->index(folder));
    }
}

void Window::runFile() {
    try {
        textEdit->runText();

        QMessageBox::information(this, "Information", "Process Completed.");
    } catch (const std::invalid_argument &e) {
        QMessageBox::critical(this, "Error", QString("Invalid argument: %1").arg(e.what()));
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("An error occurred: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Error", "An Error occurred.");
    }
}