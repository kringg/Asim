#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QProcess>

#include "MainWindow.h"
#include "MainContent.h"
#include "ui_MainWindow.h"

const QString MainWindow::SETTINGS_FILE_NAME = "SimpliAlbum.ini";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _doSave(true),
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
    connect(qApp, &QApplication::aboutToQuit, [=](){ saveSettings(SETTINGS_FILE_NAME); });

    connect(_gui->actionExit, &QAction::triggered, qApp, &QApplication::quit);
    connect(_gui->actionLoad, &QAction::triggered, [=](){ loadSettings(); });
    connect(_gui->actionSave, &QAction::triggered, [=](){ saveSettings(); });
    connect(_gui->actionSetRootPath, &QAction::triggered, [=](){ setRootPath(); });
    connect(_gui->actionResetConfig, &QAction::triggered, [=](){ resetSettings(SETTINGS_FILE_NAME); });
    connect(_gui->treeView, &QTreeView::clicked, this, &MainWindow::setTreeIndex);

    connect(_gui->actionResetCache, &QAction::triggered, _content, &MainContent::onReset);
    connect(_gui->btnRotateL, &QPushButton::clicked, _content, &MainContent::onRotateL);
    connect(_gui->btnRotateR, &QPushButton::clicked, _content, &MainContent::onRotateR);
    connect(_gui->btnThumbsUp, &QPushButton::clicked, _content, &MainContent::onThumbsUp);
    connect(_gui->btnThumbsDown, &QPushButton::clicked, _content, &MainContent::onThumbsDown);
    connect(_gui->cbViewMode, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), _content, &MainContent::onViewMode);
    connect(_gui->sliderSize, &QSlider::valueChanged, _content, &MainContent::setSize);
    connect(_gui->treeView, &QTreeView::clicked, this, &MainWindow::setTreeIndex);

    // Configuration
    loadSettings(SETTINGS_FILE_NAME);
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
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load Configuration from File"),
                                                    QStandardPaths::writableLocation(QStandardPaths::HomeLocation), "Configuration Files (*.ini)");
    if (!fileName.isEmpty())
    {
        loadSettings(fileName);
    }
}

void MainWindow::loadSettings(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    // Main Window Settings
    QVariant path = settings.value("MainWindow/path");
    if (path.isValid())
    {
        setRootPath(path.toString());
    }

    QVariant size0 = settings.value("MainWindow/size0");
    QVariant size1 = settings.value("MainWindow/size1");
    if (size0.isValid() && size1.isValid())
    {
        _gui->splitter->setSizes(QList<int>() << size0.toInt() << size1.toInt());
    }
    else
    {
        static const int defaultSize = 150;
        _gui->splitter->setSizes(QList<int>() << defaultSize << width() - defaultSize);
    }

    QVariant winM = settings.value("MainWindow/winM");
    QVariant winW = settings.value("MainWindow/winW");
    QVariant winH = settings.value("MainWindow/winH");
    QVariant winX = settings.value("MainWindow/winX");
    QVariant winY = settings.value("MainWindow/winY");
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

    // Control Panel Settings
    _gui->cbEditMode->setCurrentIndex(settings.value("ControlPanel/editMode", _gui->cbEditMode->currentIndex()).toInt());
    _gui->cbViewMode->setCurrentIndex(settings.value("ControlPanel/viewMode", _gui->cbViewMode->currentIndex()).toInt());
    _gui->sliderSize->setValue(settings.value("ControlPanel/thumbSize", _gui->sliderSize->value()).toInt());
}

void MainWindow::saveSettings()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Configuration to File"),
                                                    QStandardPaths::writableLocation(QStandardPaths::HomeLocation), "Configuration Files (*.ini)");
    if (!fileName.isEmpty())
    {
        saveSettings(fileName);
    }
}

void MainWindow::saveSettings(QString fileName)
{
    if (_doSave)
    {
        QSettings settings(fileName, QSettings::IniFormat);

        // Main Window Settings
        settings.beginGroup("MainWindow");
        settings.setValue("path",  _treeModel->rootPath());
        settings.setValue("size0", _gui->splitter->sizes()[0]);
        settings.setValue("size1", _gui->splitter->sizes()[1]);
        settings.setValue("winM", isMaximized());
        settings.setValue("winW", width());
        settings.setValue("winH", height());
        settings.setValue("winX", x());
        settings.setValue("winY", y());
        settings.endGroup();

        // Control Panel Settings
        settings.beginGroup("ControlPanel");
        settings.setValue("editMode", _gui->cbEditMode->currentIndex());
        settings.setValue("viewMode", _gui->cbViewMode->currentIndex());
        settings.setValue("thumbSize", _gui->sliderSize->value());
        settings.endGroup();
    }
}

void MainWindow::resetSettings(QString fileName)
{
    // Delete configuration
    QSettings settings(fileName, QSettings::IniFormat);
    settings.remove("");
    _doSave = false;

    // Restart
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

/*
 *
 */
void MainWindow::setRootPath()
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
