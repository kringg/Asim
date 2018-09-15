#include "QThumbnail.h"

QThumbnail::QThumbnail(QString& file, QWidget* parent) :
    QLabel(parent),
    _pixmap(new QPixmap(file)),
    _sizes(QList<int>() << 32 << 64 << 128 << 256 << 512)
{
    setSizeId(3);
}

QThumbnail::~QThumbnail()
{
    delete _pixmap;
}

/*
 *
 */
void QThumbnail::setSizeId(int sizeId)
{
    int size = _sizes.at(qMax(1, qMin(5, sizeId)));
    setPixmap(_pixmap->scaled(size, size, Qt::KeepAspectRatio));
}
