#include <QDir>
#include <QImageReader>
#include "MainContent.h"
#include <QPushButton>
#include <Qt/QFlowLayout.h>
#include "Qt/QThumbnail.h"

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
        QFileInfoList files = dir.entryInfoList(nameFilters, QDir::Files);
        foreach (QFileInfo info, files)
        {
            _layout->addWidget(new QThumbnail(info.absoluteFilePath(), this));
        }
    }
}
