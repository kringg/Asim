#include <QApplication>
#include <QDir>
#include <QTimer>
#include <QImageReader>
#include "Qt/QFlowLayout.h"
#include "Qt/QThumbnail.h"
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

        // Build file list
        QDir dir0(path);
        QDir dir1(path + "/" + ImagePath::DIR_HIDDEN);
        QFileInfoList infos = dir0.entryInfoList(nameFilters, QDir::Files);
        infos.append(dir1.entryInfoList(nameFilters, QDir::Files));

        // Load content from disk
        foreach (QFileInfo info, infos)
        {
            Image* image = new Image(ImagePath(info), this);
            _layout->addWidget(image->getThumbnail());
            _images.append(image);
            qApp->processEvents();
        }
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
 *
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
