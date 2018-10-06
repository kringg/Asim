#include <QApplication>
#include <QDir>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QProgressDialog>
#include <QImageReader>

#include "Image/Image.h"
#include "Image/ImageThumb.h"
#include "Qt/QFlowLayout.h"
#include "ContentThumbs.h"

ContentThumbs::ContentThumbs(Content* parent) :
    _parent(parent),
    _layout(new FlowLayout(this))
{
    setLayout(_layout);
}

ContentThumbs::~ContentThumbs()
{
    delete _layout;
}

/*
 * PUBLIC
 *  Mutators
 */
void ContentThumbs::setPath(QString& path)
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
            Image* image = new Image(info, _parent);
            _layout->addWidget(image->getThumbnail());
            _images.append(image);
            qApp->processEvents();
        }
        progress.setValue(infos.size());
        setView(-1);
    }
}

void ContentThumbs::setSize(int size)
{
    foreach (Image* image, _images)
    {
        image->getThumbnail()->setSizeId(size);
    }
}

void ContentThumbs::setView(int view)
{
    static int lastView = 1;
    view = (view < 0) ? lastView : view;
    lastView = (view < 0) ? lastView : view;

    foreach (Image* image, _images)
    {
        switch (view)
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
 * PUBLIC
 *  Operations
 */
void ContentThumbs::onReset()
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

void ContentThumbs::onRotateL()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setRotation(-90);
        }
    }
}

void ContentThumbs::onRotateR()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setRotation(+90);
        }
    }
}

void ContentThumbs::onThumbsUp()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setThumbsUp();
        }
    }
    QTimer::singleShot(TIMEOUT, [=](){ setView(-1); });
}

void ContentThumbs::onThumbsDown()
{
    foreach (Image* image, _images)
    {
        if (image->isSelected())
        {
            image->setThumbsDown();
        }
    }
    QTimer::singleShot(TIMEOUT, [=](){ setView(-1); });
}

/*
 * PROTECTED
 *  Operations
 */
void ContentThumbs::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Enforce mutually-exclusive selection unless CTRL is active
        if (QApplication::keyboardModifiers() ^ Qt::ControlModifier)
        {
            // Deselect all, clicked image will self-select
            foreach (Image* image, _images)
            {
                image->setSelected(false);
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void ContentThumbs::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Deselect all, double-clicked image will self-select
        foreach (Image* image, _images)
        {
            image->setSelected(false);
        }
    }
    QWidget::mouseDoubleClickEvent(event);
}
