#include <QTimer>
#include <QPainter>
#include "QThumbnail.h"

const int QThumbnail::BORDER_SIZE = 2;
const QList<int> QThumbnail::IMAGE_SIZES = {64, 128, 196, 256, 320};

QThumbnail::QThumbnail(ImagePath& imgPath, QWidget* parent) :
    QLabel(parent),
    _isRejected(imgPath.isHidden()),
    _isSelected(false),
    _pixmap(new QPixmap())
{
    QString pathThumb = imgPath.getPathThumbnail();

    // Does a thumbnail already exist?
    if (!QFileInfo(pathThumb).exists())
    {
        // No, create it
        QImage image(imgPath.getPath());
        image.scaled(512, 512, Qt::KeepAspectRatio).save(pathThumb);
    }

    // Load and init thumbnail
    _pixmap->load(pathThumb);
    setSelected(false);
    setSizeId(3);
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
    bool isSelected = _isSelected;
    QTimer::singleShot(1, [=](){setSelected(!isSelected);});
    QLabel::mousePressEvent(event);
}
