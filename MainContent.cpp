#include <QDir>
#include <QImageReader>
#include "Qt/QFlowLayout.h"
#include "Qt/QThumbnail.h"
#include "MainContent.h"

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
            _layout->addWidget(new QThumbnail(info.absoluteFilePath(), this));
        }
    }
}

void MainContent::setSize(int size)
{
    for (int i = 0; i < _layout->count(); ++i)
    {
        QWidget* widget = _layout->itemAt(i)->widget();
        QThumbnail* thumb = dynamic_cast<QThumbnail*> (widget);
        if (thumb != nullptr)
        {
            thumb->setSizeId(size);
        }
    }
}
