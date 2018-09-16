#include <QPainter>
#include "QThumbnail.h"

const int QThumbnail::BORDER_SIZE = 2;
const QList<int> QThumbnail::IMAGE_SIZES = {64, 128, 196, 256, 320};

QThumbnail::QThumbnail(QString& file, QWidget* parent) :
    QLabel(parent),
    _isRejected(false),
    _isSelected(false),
    _pixmap(new QPixmap(file))
{
    setSizeId(3);
    setSelected(false);
}

QThumbnail::~QThumbnail()
{
    delete _pixmap;
}

/*
 * PUBLIC
 *  Accessors
 */
bool QThumbnail::isSelected()
{
    return _isSelected;
}

/*
 * PUBLIC
 *  Mutators
 */
void QThumbnail::setSizeId(int sizeId)
{
    int size = IMAGE_SIZES.at(qMax(1, qMin(5, sizeId)) - 1);
    setPixmap(_pixmap->scaled(size, size, Qt::KeepAspectRatio));
}

void QThumbnail::setSelected(bool isSelected)
{
    if (isSelected)
    {
        setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(0, 0, 0, 1);");
    }
    else
    {
        setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(0, 0, 0, 0);");
    }
    _isSelected = isSelected;
}

void QThumbnail::setIsRejected(bool isRejected)
{
    _isRejected = isRejected;
    repaint(); // Force update
}

/*
 * PROTECTED
 *  Operations
 */
void QThumbnail::paintEvent(QPaintEvent* event)
{
    if (_isRejected)
    {
        QPainter painter(this);
        painter.setOpacity(0.5);
        painter.drawPixmap(BORDER_SIZE, BORDER_SIZE, *pixmap());
    }
    else
    {
        QLabel::paintEvent(event);
    }
}

void QThumbnail::mousePressEvent(QMouseEvent* event)
{
    setSelected(!_isSelected);
    QLabel::mousePressEvent(event);
}
