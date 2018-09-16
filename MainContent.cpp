#include <QDir>
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

        // Load content
        QDir dir(path);
        QFileInfoList infos = dir.entryInfoList(nameFilters, QDir::Files);
        foreach (QFileInfo info, infos)
        {
            Image* image = new Image(info.absoluteFilePath(), this);
            _layout->addWidget(image->getThumbnail());
            _images.append(image);
        }
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
}
