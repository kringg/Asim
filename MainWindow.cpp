#include <iostream>
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
    // Initialize
    _gui->setupUi(this);
    _gui->scrollArea->setWidget(_content);

    // Configure tree view pane
    _gui->treeView->setModel(_treeModel);
    _gui->treeView->hideColumn(1); // Size
    _gui->treeView->hideColumn(2); // Type
    _gui->treeView->hideColumn(3); // Date
    setRootPath("C:/");

    // Connect signals and slots
    connect(_gui->actionConfigRootPath, SIGNAL(triggered()), this, SLOT(setRootPath()));
    connect(_gui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(setTreeIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete _gui;
    delete _content;
    delete _treeModel;
}

/*
 *
 */
void MainWindow::setRootPath(QString rootPath)
{
    // Conditional browse
    if (rootPath.isEmpty())
    {
        rootPath = QFileDialog::getExistingDirectory(this,
                                                     tr("Open Directory"),
                                                     _treeModel->rootPath(),
                                                     QFileDialog::ShowDirsOnly);
    }

    // Update components
    if (!rootPath.isEmpty())
    {
        // Update tree model and view
        _treeModel->setRootPath(rootPath);
        _gui->treeView->setRootIndex(_treeModel->index(rootPath));

        // Resize split-screen components
        int splitX0 = _gui->treeView->width() * 2;
        int splitX1 = QMainWindow::width() - splitX0;
        _gui->splitter->setSizes(QList<int>() << splitX0 << splitX1);
    }
}


void MainWindow::setTreeIndex(QModelIndex index)
{
    _content->setPath(_treeModel->filePath(index));
}
