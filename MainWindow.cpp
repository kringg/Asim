#include <iostream>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QStandardPaths>
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
    setRootPath(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));

    // Configure splitter stretch factor
    _gui->splitter->setStretchFactor(0, 0);
    _gui->splitter->setStretchFactor(1, 1);

    // Configure unicode emoji buttons
    _gui->btnEdit->setFixedWidth(_gui->btnEdit->height());
    _gui->btnThumbsUp->setFixedWidth(_gui->btnThumbsUp->height());
    _gui->btnThumbsDown->setFixedWidth(_gui->btnThumbsDown->height());
    _gui->btnRotateClockwise->setFixedWidth(_gui->btnRotateClockwise->height());
    _gui->btnRotateCounterClockwise->setFixedWidth(_gui->btnRotateCounterClockwise->height());

    // Connect signals and slots
    connect(_gui->treeView, &QTreeView::clicked, this, &MainWindow::setTreeIndex);
    connect(_gui->setRootPath, &QAction::triggered, this, &MainWindow::browseRootPath);

    connect(_gui->sliderSize, &QSlider::valueChanged, _content, &MainContent::setSize);
    connect(_gui->btnThumbsUp, &QPushButton::clicked, _content, &MainContent::onThumbsUp);
    connect(_gui->btnThumbsDown, &QPushButton::clicked, _content, &MainContent::onThumbsDown);
    connect(_gui->cbViewMode, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), _content, &MainContent::onViewMode);
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
void MainWindow::browseRootPath()
{
    QString rootPath = QFileDialog::getExistingDirectory(this,
                                                         tr("Open Directory"),
                                                         _treeModel->rootPath(),
                                                         QFileDialog::ShowDirsOnly);
    if (!rootPath.isEmpty())
    {
        setRootPath(rootPath);
    }
}

void MainWindow::setRootPath(QString rootPath)
{
    // Validate root path
    if (QFileInfo::exists(rootPath))
    {
        // Update tree model and view
        _treeModel->setRootPath(rootPath);
        _treeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
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
