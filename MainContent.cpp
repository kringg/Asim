#include <QApplication>
#include <QDir>
#include <QTimer>
#include <QMessageBox>
#include <QProgressDialog>
#include <QImageReader>
#include "Qt/QFlowLayout.h"
#include "ImageThumb.h"
#include "MainContent.h"
#include "Image.h"

MainContent::MainContent() :
    _layout(new FlowLayout(this))
{
    setLayout(_layout);
}

MainContent::~MainContent()
{
    delete _layout;
}

/*
 * PUBLIC
 *  Mutators
 */
void MainContent::setPath(QString& path)
{
    if (_lastPath != path)
    {
        // Purge existing
        _lastPath = path;
        _layout->clear();
        foreach (Image* image, _images)
        {
            delete image;
        }
        _images.clear();

        // Deduce image formats
        static QStringList nameFilters;
        if (nameFilters.isEmpty())
        {
            QList<QByteArray> formats = QImageReader::supportedImageFormats();
            foreach (QByteArray format, formats)
            {
                nameFilters.append("*." + format);
            }
        }

        // Ensure system paths exist
        QDir().mkdir(path + "/" + ImagePath::DIR_HIDDEN);
        QDir().mkdir(path + "/" + ImagePath::DIR_THUMBS);

        // File dirs
        QDir dir0(path);
        QDir dir1(path + "/" + ImagePath::DIR_HIDDEN);

        // Image files
        QFileInfoList infos;
        infos.append(dir0.entryInfoList(nameFilters, QDir::Files));
        infos.append(dir1.entryInfoList(nameFilters, QDir::Files));

        // Build progress dialog
        QProgressDialog progress("Generating / reading thumbnail cache...", QString(), 0, infos.size());
        progress.setCancelButton(nullptr);
        progress.setWindowModality(Qt::ApplicationModal);

        // Load content from disk
        foreach (QFileInfo info, infos)
        {
            progress.setValue(progress.value() + 1);
            Image* image = new Image(ImagePath(info), this);
            _layout->addWidget(image->getThumbnail());
            _images.append(image);
            qApp->processEvents();
        }
        progress.setValue(infos.size());
        onViewMode(-1);
    }
}

void MainContent::setSize(int size)
{
    foreach (Image* image, _images)
    {
        image->getThumbnail()->setSizeId(size);
    }
}

/*
 * PUBLIC
 *  Operations
 */
void MainContent::onReset()
{
    // Validate paths
    QDir dir0(_lastPath);
    QDir dir1(_lastPath + "/" + ImagePath::DIR_THUMBS);

    // Recursively remove thumbs path
    if (dir0.exists() && dir1.exists())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Reset Cache?",
                                                                  "This will purge all (auto-generated) thumbnails for the current album. "
                                                                  "This action cannot be undone, but the thumbnails can always be rebuilt. "
                                                                  "Are you sure you want to continue?",
                                                                  QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            dir1.removeRecursively();
        }
    }
    else
    {
        QMessageBox::information(this, "Can't Reset Cache",
                                 "No albums are currently loaded, so there's no thumbnail cache to reset. "
                                 "You must first select an album (directory) from the tree on the left.",
                                 QMessageBox::Ok);
    }
}

void MainContent::onRotateL()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setRotation(-90);
        }
    }
}

void MainContent::onRotateR()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setRotation(+90);
        }
    }
}

void MainContent::onThumbsUp()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setThumbsUp();
        }
    }
    QTimer::singleShot(TIMEOUT, [=](){ onViewMode(-1); });
}

void MainContent::onThumbsDown()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setThumbsDown();
        }
    }
    QTimer::singleShot(TIMEOUT, [=](){ onViewMode(-1); });
}

void MainContent::onViewMode(int viewMode)
{
    static int lastViewMode = 1;
    viewMode = (viewMode < 0) ? lastViewMode : viewMode;
    lastViewMode = (viewMode < 0) ? lastViewMode : viewMode;

    foreach (Image* image, _images)
    {
        switch (viewMode)
        {
        case 0:
            image->getThumbnail()->setVisible(true);
            break;
        case 1:
            image->getThumbnail()->setVisible(image->isThumbsUp());
            break;
        case 2:
            image->getThumbnail()->setVisible(image->isThumbsDown());
            break;
        default:
            // NO-OP
            break;
        }
    }
}

/*
 * PROTECTED
 *  Operations
 */
void MainContent::mousePressEvent(QMouseEvent* event)
{
    // Enforce mutually-exclusive selection unless CTRL is active
    if (QApplication::keyboardModifiers() ^ Qt::ControlModifier)
    {
        foreach (Image* image, _images)
        {
            image->setSelected(false);
        }
    }
    QWidget::mousePressEvent(event);
}
