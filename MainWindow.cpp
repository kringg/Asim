#include <QFileDialog>
#include <QFileSystemModel>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _gui(new Ui::MainWindow()),
    _treeModel(new QFileSystemModel())
{
    _gui->setupUi(this);

    QString rootPath = "C:/";
    _treeModel->setRootPath(rootPath);
    _gui->treeView->setModel(_treeModel);
    _gui->treeView->setRootIndex(_treeModel->index(rootPath));

    _gui->treeView->hideColumn(1); // Size
    _gui->treeView->hideColumn(2); // Type
    _gui->treeView->hideColumn(3); // Date

    _gui->splitter->setStretchFactor(0, 1);
    _gui->splitter->setStretchFactor(1, 2);
    _gui->splitter->setStretchFactor(2, 3);

    //
    connect(_gui->actionConfigRootPath, SIGNAL(triggered()), this, SLOT(onConfigRootPath()));
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
                                                    QString(),
                                                    QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty())
    {
        _gui->treeView->setRootIndex(_treeModel->index(dir));
    }
}
