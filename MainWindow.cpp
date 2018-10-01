#include <QFileDialog>
#include <QSettings>
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
    _gui->btnRotateL->setFixedWidth(_gui->btnRotateL->height());
    _gui->btnRotateR->setFixedWidth(_gui->btnRotateR->height());
    _gui->btnThumbsUp->setFixedWidth(_gui->btnThumbsUp->height());
    _gui->btnThumbsDown->setFixedWidth(_gui->btnThumbsDown->height());

    // Connect signals and slots
    connect(qApp, &QApplication::aboutToQuit, this, &MainWindow::saveSettings);

    connect(_gui->treeView, &QTreeView::clicked, this, &MainWindow::setTreeIndex);
    connect(_gui->setRootPath, &QAction::triggered, this, &MainWindow::browseRootPath);

    connect(_gui->sliderSize, &QSlider::valueChanged, _content, &MainContent::setSize);
    connect(_gui->btnRotateL, &QPushButton::clicked, _content, &MainContent::onRotateL);
    connect(_gui->btnRotateR, &QPushButton::clicked, _content, &MainContent::onRotateR);
    connect(_gui->btnThumbsUp, &QPushButton::clicked, _content, &MainContent::onThumbsUp);
    connect(_gui->btnThumbsDown, &QPushButton::clicked, _content, &MainContent::onThumbsDown);
    connect(_gui->cbViewMode, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), _content, &MainContent::onViewMode);

    // Configuration
    loadSettings();
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
void MainWindow::loadSettings()
{
    QSettings settings("KRingg", "Asim");

    QVariant path = settings.value("path");
    if (path.isValid())
    {
        setRootPath(path.toString());
    }

    QVariant size0 = settings.value("size0");
    QVariant size1 = settings.value("size1");
    if (size0.isValid() && size1.isValid())
    {
        _gui->splitter->setSizes(QList<int>() << size0.toInt() << size1.toInt());
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("KRingg", "Asim");
    settings.setValue("path",  _treeModel->rootPath());
    settings.setValue("size0", _gui->splitter->sizes()[0]);
    settings.setValue("size1", _gui->splitter->sizes()[1]);
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
    }
}

void MainWindow::setTreeIndex(QModelIndex index)
{
    _gui->control->setEnabled(false);
    _gui->treeView->setEnabled(false);
    _content->setPath(_treeModel->filePath(index));
    _gui->treeView->setEnabled(true);
    _gui->control->setEnabled(true);
}
