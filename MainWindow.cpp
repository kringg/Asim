#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QProcess>

#include "MainWindow.h"
#include "MainContent.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _gui(new Ui::MainWindow()),
    _content(new MainContent()),
    _settings(new QSettings("SimplAlbum", QSettings::IniFormat)),
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
    connect(_gui->resetSettings, &QAction::triggered, this, &MainWindow::resetSettings);

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
    delete _settings;
    delete _treeModel;
}

/*
 *
 */
void MainWindow::loadSettings()
{
    QVariant path = _settings->value("MainWindow/path");
    if (path.isValid())
    {
        setRootPath(path.toString());
    }

    QVariant size0 = _settings->value("MainWindow/size0");
    QVariant size1 = _settings->value("MainWindow/size1");
    if (size0.isValid() && size1.isValid())
    {
        _gui->splitter->setSizes(QList<int>() << size0.toInt() << size1.toInt());
    }

    QVariant winM = _settings->value("MainWindow/winM");
    QVariant winW = _settings->value("MainWindow/winW");
    QVariant winH = _settings->value("MainWindow/winH");
    QVariant winX = _settings->value("MainWindow/winX");
    QVariant winY = _settings->value("MainWindow/winY");
    if (winM.isValid())
    {
        if (winM.toBool())
        {
            setWindowState(Qt::WindowMaximized);
        }
        else
        {
            if (winX.isValid() && winY.isValid())
            {
                move(winX.toInt(), winY.toInt());
            }
            if (winW.isValid() && winH.isValid())
            {
                resize(winW.toInt(), winH.toInt());
            }
        }
    }

    // Control panel
    _gui->cbEditMode->setCurrentIndex(_settings->value("ControlPanel/editMode", _gui->cbEditMode->currentIndex()).toInt());
    _gui->cbViewMode->setCurrentIndex(_settings->value("ControlPanel/viewMode", _gui->cbViewMode->currentIndex()).toInt());
    _gui->sliderSize->setValue(_settings->value("ControlPanel/thumbSize", _gui->sliderSize->value()).toInt());
}

void MainWindow::saveSettings()
{
    if (_settings != nullptr)
    {
        _settings->beginGroup("MainWindow");
        _settings->setValue("path",  _treeModel->rootPath());
        _settings->setValue("size0", _gui->splitter->sizes()[0]);
        _settings->setValue("size1", _gui->splitter->sizes()[1]);
        _settings->setValue("winM", isMaximized());
        _settings->setValue("winW", width());
        _settings->setValue("winH", height());
        _settings->setValue("winX", x());
        _settings->setValue("winY", y());
        _settings->endGroup();

        _settings->beginGroup("ControlPanel");
        _settings->setValue("editMode", _gui->cbEditMode->currentIndex());
        _settings->setValue("viewMode", _gui->cbViewMode->currentIndex());
        _settings->setValue("thumbSize", _gui->sliderSize->value());
        _settings->endGroup();
    }
}

void MainWindow::resetSettings()
{
    // Delete configuration
    _settings->remove("");
    delete _settings;
    _settings = nullptr;

    // Restart
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
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
    // Disable interactive elements
    _gui->control->setEnabled(false);
    _gui->treeView->setEnabled(false);

    // Update root path (reloads content from disk)
    _content->setPath(_treeModel->filePath(index));

    // Re-Enable interactive elements
    _gui->treeView->setEnabled(true);
    _gui->control->setEnabled(true);
}
