#include <QFileDialog>
#include <QFileSystemModel>
#include "MainWindow.h"
#include "MainContent.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _gui(new Ui::MainWindow()),
    _content(new MainContent()),
    _treeModel(new QFileSystemModel())
{
    _gui->setupUi(this);
    _gui->scrollArea->setWidget(_content);

    QString rootPath = "C:/";
    _treeModel->setFilter(QDir::Dirs | QDir::Drives | QDir::NoDotAndDotDot);
    _treeModel->setRootPath(rootPath);
    _gui->treeView->setModel(_treeModel);
    _gui->treeView->setRootIndex(_treeModel->index(rootPath));

    _gui->treeView->hideColumn(1); // Size
    _gui->treeView->hideColumn(2); // Type
    _gui->treeView->hideColumn(3); // Date

    _gui->splitter->setStretchFactor(0, 1);
    _gui->splitter->setStretchFactor(1, 10);

    //
    connect(_gui->actionConfigRootPath, SIGNAL(triggered()), this, SLOT(onConfigRootPath()));
    connect(_gui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onTreeIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete _gui;
    delete _treeModel;
}

/*
 *
 */
void MainWindow::onConfigRootPath()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    tr("Open Directory"),
                                                    _treeModel->rootPath(),
                                                    QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty())
    {
        _gui->treeView->setRootIndex(_treeModel->index(dir));
    }
}


void MainWindow::onTreeIndex(QModelIndex index)
{
    _content->setPath(_treeModel->filePath(index));
}
