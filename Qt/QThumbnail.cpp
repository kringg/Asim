#include <QtConcurrent/QtConcurrent>
#include <QImageReader>
#include <QTimer>
#include <QPainter>
#include "QThumbnail.h"

const int QThumbnail::BORDER_SIZE = 5;
const QList<int> QThumbnail::IMAGE_SIZES = {128, 160, 192, 224, 256};

QThumbnail::QThumbnail(ImagePath& imgPath, QWidget* parent) :
    QLabel(parent),
    _isRejected(imgPath.isHidden()),
    _isSelected(false),
    _pixmap(new QPixmap()),
    _pathThumb(imgPath.getPathThumbnail())
{
    QFuture<void> future = QtConcurrent::run([=]()
    {
        // Does a thumbnail already exist?
        if (!QFileInfo(_pathThumb).exists())
        {
            // No, configure fast image reader
            QImageReader reader(imgPath.getPath());
            QSize size = reader.size();
            int maxSize = IMAGE_SIZES.last();
            size.scale(maxSize, maxSize, Qt::KeepAspectRatio);
            reader.setScaledSize(size);

            // Load small image from disk
            QImage image = reader.read();
            image.save(_pathThumb);

            // Populate pixmap with image
            _pixmap->convertFromImage(image);
        }
        else
        {
            // Yes, just load thumbnail
            _pixmap->load(_pathThumb);
        }

        // Initialize thumbnail
        setIsSelected(false);
        setSizeId(3);
    });
    future.waitForFinished();
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
void QThumbnail::setRotation(QMatrix& matrix)
{
    QFile(_pathThumb).remove();
    *_pixmap = _pixmap->transformed(matrix);
    setPixmap(pixmap()->transformed(matrix));
}

void QThumbnail::setSizeId(int sizeId)
{
    int size = IMAGE_SIZES.at(qMax(1, qMin(5, sizeId)) - 1);
    setPixmap(_pixmap->scaled(size, size, Qt::KeepAspectRatio));
}

void QThumbnail::setIsRejected(bool isRejected)
{
    _isRejected = isRejected;
    repaint(); // Force update
}

void QThumbnail::setIsSelected(bool isSelected)
{
    if (isSelected)
    {
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(159, 246, 255, 255);");
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(121, 197, 255, 255);");
        setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba( 94, 149, 255, 255);");
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba( 67,  91, 255, 255);");
        //setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba( 59,  48, 255, 255);");
    }
    else
    {
        setStyleSheet("border: " + QString::number(BORDER_SIZE) + "px solid rgba(0, 0, 0, 0);");
    }
    _isSelected = isSelected;
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
    QTimer::singleShot(1, [=](){setIsSelected(!isSelected);});
    QLabel::mousePressEvent(event);
}
